#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION
#include "tiny_gltf.h"
#include <cstring>

extern "C" {
#include "agl_gfx.h"
}

static int LoadGltf(agl_gfx_context_t context, const char *path, agl_gfx_load_params_t *params) {
	agl_gfx_mesh_params_t meshParams;
	tinygltf::Model model;
	tinygltf::TinyGLTF loader;
	std::string err, warn;

	if (path == nullptr) {
		printf("Invalid arguments to load_gltf. File path cannot be null!\n");
		return 0;
	}
	if (params == nullptr) {
		printf("Invalid arguments to load_gltf. Load params cannot be null!\n");
		return 0;
	}
	if (params->meshCallback == nullptr) {
		printf("Invalid arguments to load_gltf. Mesh callback cannot be null!\n");
		return 0;
	}
	if (params->imageCallback != nullptr) {
		printf("Warning: Image callback is not supported in this loader plugin. Ignoring it.\n");
	}
	const char *ext = strrchr(path, '.');
	bool isBinary = false;
	if (_stricmp(ext, ".gltf") == 0) {
		isBinary = false;
	} else if (_stricmp(ext, ".glb") == 0) {
		isBinary = true;
	} else {
		printf("Unsupported file extension: %s\n", ext);
		return 0;
	}
	bool ret;
	if (isBinary) {
		ret = loader.LoadBinaryFromFile(&model, &err, &warn, path);
	} else {
		ret = loader.LoadASCIIFromFile(&model, &err, &warn, path);
	}
	if (!warn.empty()) {
		printf("Warn: %s\n", warn.c_str());
	}
	if (!err.empty()) {
		printf("Err: %s\n", err.c_str());
	}
	if (!ret) {
		printf("Failed to load GLTF: %s\n", path);
		return 0;
	}
	if (model.meshes.empty()) {
		printf("No meshes found in GLTF: %s\n", path);
		return 0;
	}
	// For simplicity, we only load the first mesh
	const tinygltf::Mesh &mesh = model.meshes[0];
	if (mesh.primitives.empty()) {
		printf("No primitives found in mesh: %s\n", mesh.name.c_str());
		return 0;
	}
	const tinygltf::Primitive &prim = mesh.primitives[0];
	// POSITION
	const tinygltf::Accessor &posAccessor = model.accessors[prim.attributes.find("POSITION")->second];
	const tinygltf::BufferView &posView = model.bufferViews[posAccessor.bufferView];
	const tinygltf::Buffer &posBuffer = model.buffers[posView.buffer];
	meshParams.vertexCount = static_cast<agl_uint>(posAccessor.count);
	meshParams.positionData = (agl_float*)(posBuffer.data.data() + posView.byteOffset + posAccessor.byteOffset);
	// NORMAL
	if (prim.attributes.count("NORMAL")) {
		const tinygltf::Accessor &normAccessor = model.accessors[prim.attributes.find("NORMAL")->second];
		const tinygltf::BufferView &normView = model.bufferViews[normAccessor.bufferView];
		const tinygltf::Buffer &normBuffer = model.buffers[normView.buffer];
		meshParams.normalData = (agl_float*)(normBuffer.data.data() + normView.byteOffset + normAccessor.byteOffset);
	} else {
		meshParams.normalData = nullptr;
	}
	// TEXCOORD_0
	if (prim.attributes.count("TEXCOORD_0")) {
		const tinygltf::Accessor &uvAccessor = model.accessors[prim.attributes.find("TEXCOORD_0")->second];
		const tinygltf::BufferView &uvView = model.bufferViews[uvAccessor.bufferView];
		const tinygltf::Buffer &uvBuffer = model.buffers[uvView.buffer];
		meshParams.uvData = (agl_float*)(uvBuffer.data.data() + uvView.byteOffset + uvAccessor.byteOffset);
	} else {
		meshParams.uvData = nullptr;
	}
	// COLOR_0
	if (prim.attributes.count("COLOR_0")) {
		const tinygltf::Accessor &colorAccessor = model.accessors[prim.attributes.find("COLOR_0")->second];
		const tinygltf::BufferView &colorView = model.bufferViews[colorAccessor.bufferView];
		const tinygltf::Buffer &colorBuffer = model.buffers[colorView.buffer];
		meshParams.colorData = (agl_float*)(colorBuffer.data.data() + colorView.byteOffset + colorAccessor.byteOffset);
	} else {
		meshParams.colorData = nullptr;
	}
	// INDICES
	if (prim.indices >= 0) {
		const tinygltf::Accessor &idxAccessor = model.accessors[prim.indices];
		const tinygltf::BufferView &idxView = model.bufferViews[idxAccessor.bufferView];
		const tinygltf::Buffer &idxBuffer = model.buffers[idxView.buffer];
		meshParams.indexCount = static_cast<agl_uint>(idxAccessor.count);
		if (idxAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) {
			meshParams.indexData = (agl_uint*)(idxBuffer.data.data() + idxView.byteOffset + idxAccessor.byteOffset);
		} else if (idxAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
			// Need to convert to uint
			const uint16_t *src = (const uint16_t*)(idxBuffer.data.data() + idxView.byteOffset + idxAccessor.byteOffset);
			agl_uint *dst = new agl_uint[idxAccessor.count];
			for (size_t i = 0; i < idxAccessor.count; ++i) {
				dst[i] = static_cast<agl_uint>(src[i]);
			}
			// TODO: We should free this memory when the mesh is destroyed
			meshParams.indexData = dst;
		} else {
			printf("Unsupported index component type: %d\n", idxAccessor.componentType);
			meshParams.indexCount = 0;
			meshParams.indexData = nullptr;
			return 0;
		}
	} else {
		meshParams.indexCount = 0;
		meshParams.indexData = nullptr;
	}

	params->meshCallback(context, &meshParams, mesh.name.c_str());
	printf("Successfully loaded GLTF mesh: %s\n", mesh.name.c_str());

	return 1;
}

extern "C" {
	
#include "agl_plugin.h"

static int load_gltf(agl_gfx_context_t context, const char *path, agl_gfx_load_params_t *params) {
	return LoadGltf(context, path, params);
}

static int gltf_loader_init(agl_plugin_t *plugin, agl_gfx_context_t context) {
	(void)plugin;
	static agl_gfx_loader_t loader_plugin = {
		.exts = ".gltf;.glb",
		.load = load_gltf
	};
	agl_gfx_register_loader(context, &loader_plugin);
	return 1;
}

AGL_PLUGIN_API int gltf_loader_register() {
	static agl_plugin_t plugin = (agl_plugin_t) {
		.name = "GLTF Loader Plugin",
		.description = "Loads and renders GLTF models.",
		.version = "1.0",
		.author = "Athang Gupte",
		.init = gltf_loader_init,
		.update = nullptr,
		.draw = nullptr,
		.cleanup = nullptr
	};
	return agl_register_plugin(&plugin);
}

}
