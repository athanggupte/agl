jit.off(true, true)

local ffi = require "ffi"

ffi.cdef[[
	// agl_gfx.h
	typedef struct agl__gfx_context_t *agl_gfx_context_t;
	typedef struct agl__gfx_canvas_t *agl_gfx_canvas_t;
	typedef uint32_t agl_gfx_image_t;
	typedef uint32_t agl_gfx_buffer_t;
	typedef uint32_t agl_gfx_mesh_t;

	typedef struct agl_gfx_context_wrapper_t {
		agl_gfx_context_t unwrapped;
	} agl_gfx_context_wrapper_t;

	typedef struct agl_gfx_canvas_wrapper_t {
		agl_gfx_canvas_t unwrapped;
	} agl_gfx_canvas_wrapper_t;

	typedef struct agl_gfx_image_wrapper_t {
		agl_gfx_image_t unwrapped;
	} agl_gfx_image_wrapper_t;

	typedef struct agl_gfx_buffer_wrapper_t {
		agl_gfx_buffer_t unwrapped;
	} agl_gfx_buffer_wrapper_t;

	typedef struct agl_gfx_mesh_wrapper_t {
		agl_gfx_mesh_t unwrapped;
	} agl_gfx_mesh_wrapper_t;

	typedef struct agl_gfx_create_params_t {
		const char *appname;
		uint32_t width;
		uint32_t height;
		uint32_t imagePoolSize;
		uint32_t bufferPoolSize;
		uint32_t meshPoolSize;
		uint32_t quadPoolSize;
		struct {
			void *allocationBase;
			uint64_t allocationSize;
		} scratchMemory;
	} agl_gfx_create_params_t;

	typedef struct agl_gfx_image_params_t {
		uint32_t width;
		uint32_t height;
		// agl_gfx_image_format_t format;
		uint32_t format;
		void *pixelData;
	} agl_gfx_image_params_t;

	typedef struct agl_gfx_buffer_params_t {
		uint32_t size;
		void *data;
		uint32_t flags;
	} agl_gfx_buffer_params_t;

	typedef struct agl_gfx_mesh_params_t {
		uint32_t vertexCount;
		uint32_t indexCount;
		float *positionData;
		float *uvData;
		float *normalData;
		float *colorData;
		uint32_t *indexData;
	} agl_gfx_mesh_params_t;

	typedef struct agl_gfx_loader_t agl_gfx_loader_t;
	typedef struct agl_gfx_load_params_t agl_gfx_load_params_t;
	typedef void (*agl_gfx_loader_mesh_callback_func)(agl_gfx_context_t context, const agl_gfx_mesh_params_t *params, const char *name);
	typedef void (*agl_gfx_loader_image_callback_func)(agl_gfx_context_t context, const agl_gfx_image_params_t *params, const char *name);

	struct agl_gfx_load_params_t {
		agl_gfx_loader_mesh_callback_func meshCallback;
		agl_gfx_loader_image_callback_func imageCallback;
	};

	typedef enum agl_gfx_key_t {
		AGL_GFX_KEY_NONE,
		AGL_GFX_KEY_SPACE,
		AGL_GFX_KEY_ENTER,
		AGL_GFX_KEY_ESCAPE,
		AGL_GFX_KEY_LSHIFT,
		AGL_GFX_KEY_RSHIFT,
		AGL_GFX_KEY_LCTRL,
		AGL_GFX_KEY_RCTRL,
		AGL_GFX_KEY_TAB,
		AGL_GFX_KEY_LEFT,
		AGL_GFX_KEY_UP,
		AGL_GFX_KEY_RIGHT,
		AGL_GFX_KEY_DOWN,
		AGL_GFX_KEY_0,
		AGL_GFX_KEY_1,
		AGL_GFX_KEY_2,
		AGL_GFX_KEY_3,
		AGL_GFX_KEY_4,
		AGL_GFX_KEY_5,
		AGL_GFX_KEY_6,
		AGL_GFX_KEY_7,
		AGL_GFX_KEY_8,
		AGL_GFX_KEY_9,
		AGL_GFX_KEY_AT,
		AGL_GFX_KEY_A,
		AGL_GFX_KEY_B,
		AGL_GFX_KEY_C,
		AGL_GFX_KEY_D,
		AGL_GFX_KEY_E,
		AGL_GFX_KEY_F,
		AGL_GFX_KEY_G,
		AGL_GFX_KEY_H,
		AGL_GFX_KEY_I,
		AGL_GFX_KEY_J,
		AGL_GFX_KEY_K,
		AGL_GFX_KEY_L,
		AGL_GFX_KEY_M,
		AGL_GFX_KEY_N,
		AGL_GFX_KEY_O,
		AGL_GFX_KEY_P,
		AGL_GFX_KEY_Q,
		AGL_GFX_KEY_R,
		AGL_GFX_KEY_S,
		AGL_GFX_KEY_T,
		AGL_GFX_KEY_U,
		AGL_GFX_KEY_V,
		AGL_GFX_KEY_W,
		AGL_GFX_KEY_X,
		AGL_GFX_KEY_Y,
		AGL_GFX_KEY_Z,
		AGL_GFX_KEY_NUMPAD0,
		AGL_GFX_KEY_NUMPAD1,
		AGL_GFX_KEY_NUMPAD2,
		AGL_GFX_KEY_NUMPAD3,
		AGL_GFX_KEY_NUMPAD4,
		AGL_GFX_KEY_NUMPAD5,
		AGL_GFX_KEY_NUMPAD6,
		AGL_GFX_KEY_NUMPAD7,
		AGL_GFX_KEY_NUMPAD8,
		AGL_GFX_KEY_NUMPAD9,
		AGL_GFX_KEY_COUNT,
	} agl_gfx_key_t;

	typedef void (*agl_gfx_update_func)(agl_gfx_context_t context, float deltaTime);
	typedef void (*agl_gfx_user_pointer_delete_func)(void *udata);
	typedef void (*agl_gfx_key_func)(int key, int down, int repeat, int scancode);
	typedef void (*agl_gfx_mouse_button_func)(int btnmask, float mx, float my, int down, int mods);
	typedef void (*agl_gfx_mouse_move_func)(int btnmask, float mx, float my, int mods);
	typedef void (*agl_gfx_scroll_func)(float sx, float sy);

	int agl_load_plugin(const char *path);

	agl_gfx_context_t agl_gfx_create_context(const agl_gfx_create_params_t *params);
	void agl_gfx_destroy_context(agl_gfx_context_t context);

	void agl_gfx_main_loop(agl_gfx_context_t context);
	agl_gfx_canvas_t agl_gfx_get_default_canvas(agl_gfx_context_t context);
	void agl_gfx_get_canvas_size(agl_gfx_canvas_t canvas, uint32_t *width, uint32_t *height);

	agl_gfx_update_func agl_gfx_set_update_func(agl_gfx_context_t context, agl_gfx_update_func updatefn);
	agl_gfx_key_func agl_gfx_set_key_func(agl_gfx_context_t context, agl_gfx_key_func keyfn);
	agl_gfx_mouse_button_func agl_gfx_set_mouse_button_func(agl_gfx_context_t context, agl_gfx_mouse_button_func mousefn);
	agl_gfx_mouse_move_func agl_gfx_set_mouse_move_func(agl_gfx_context_t context, agl_gfx_mouse_move_func movefn);
	agl_gfx_scroll_func agl_gfx_set_scroll_func(agl_gfx_context_t context, agl_gfx_scroll_func scrollfn);
	agl_gfx_user_pointer_delete_func agl_gfx_set_user_pointer_delete_func(agl_gfx_context_t context, agl_gfx_user_pointer_delete_func deletefn);

	bool agl_gfx_is_key_down(agl_gfx_context_t context, agl_gfx_key_t key);

	agl_gfx_image_t agl_gfx_create_image(agl_gfx_context_t context, const agl_gfx_image_params_t *params);
	agl_gfx_buffer_t agl_gfx_create_buffer(agl_gfx_context_t context, const agl_gfx_buffer_params_t *params);
	agl_gfx_mesh_t agl_gfx_create_mesh(agl_gfx_context_t context, const agl_gfx_mesh_params_t *params);

	void agl_gfx_set_camera_position(agl_gfx_canvas_t canvas, const float pos[3]);
	void agl_gfx_set_camera_look_at(agl_gfx_canvas_t canvas, const float tgt[3], const float worldUp[3]);
	void agl_gfx_set_camera_perspective(agl_gfx_canvas_t canvas, float fovY, float nearZ, float farZ);
	
	void agl_gfx_draw_screen_quad(agl_gfx_canvas_t canvas, const float pos[2], const float size[2], float angle, uint32_t color, agl_gfx_image_t texture);
	void agl_gfx_draw_mesh(agl_gfx_canvas_t canvas, agl_gfx_mesh_t mesh, const float pos[3], const float rot[4], float scale, const float color[4]);
	void agl_gfx_draw_text(agl_gfx_canvas_t canvas, const float startpos[2], float height, uint32_t color, const char *text);

	int agl_gfx_context_init_plugins(agl_gfx_context_t context);
	int agl_gfx_load_file(agl_gfx_context_t context, const char *path, agl_gfx_load_params_t *params);

	// agl_math.h
	typedef struct vec3f_t { float x, y, z, w; } vec3f_t;
	typedef struct vec4f_t { float x, y, z, w; } vec4f_t;
	typedef struct quatf_t { float x, y, z, w; } quatf_t;
	typedef struct mat3f_t { float _m[4][3]; } mat3f_t;

	void quatf_inv(quatf_t *q);
	void quatf_add(quatf_t *q, const quatf_t *b);
	void quatf_addscaled(quatf_t *q, const quatf_t *b, float s);
	void quatf_sub(quatf_t *q, const quatf_t *b);
	void quatf_mul2(quatf_t *q, const quatf_t *a, const quatf_t *b);
	void quatf_fromaxisangle(quatf_t *q, const vec3f_t *axis, float angle);
	void quatf_fromvectors(quatf_t *q, const vec3f_t *a, const vec3f_t *b);
]]

local agl = ffi.load("agl")

local config = {
	IMAGE_POOL_SIZE = 1024, -- Max number of images that can be loaded at once
	BUFFER_POOL_SIZE = 1024, -- Max number of buffers that can be allocated at once
	MESH_POOL_SIZE = 1024, -- Max number of meshes that can be loaded at once
	QUAD_POOL_SIZE = 1024, -- Max number of quads that can be rendered at once
	SCRATCH_MEMORY_SIZE = 512 * 1024, -- 512 KiB of scratch memory
}

local pluginsLoaded = false

local context_mt = {
	__index = {
		getDefaultCanvas = function(self)
			return ffi.new("agl_gfx_canvas_wrapper_t", agl.agl_gfx_get_default_canvas(self.unwrapped))
		end,
		_setUpdateFunc = function(self, updatefn)
			local c_updatefn = ffi.cast("agl_gfx_update_func", function(context, deltaTime)
				updatefn(self, deltaTime)
			end)
			agl.agl_gfx_set_update_func(self.unwrapped, c_updatefn)
		end,
		_setKeyFunc = function(self, keyfn)
			local c_keyfn = ffi.cast("agl_gfx_key_func", function(key, down, repeat_, scancode)
				keyfn(self, key, down, repeat_, scancode)
			end)
			agl.agl_gfx_set_key_func(self.unwrapped, c_keyfn)
		end,
		_setMouseButtonFunc = function(self, mousefn)
			local c_mousefn = ffi.cast("agl_gfx_mouse_button_func", function(btnmask, mx, my, down, mods)
				mousefn(self, btnmask, mx, my, down, mods)
			end)
			agl.agl_gfx_set_mouse_button_func(self.unwrapped, c_mousefn)
		end,
		_setMouseMoveFunc = function(self, movefn)
			local c_movefn = ffi.cast("agl_gfx_mouse_move_func", function(btnmask, mx, my, mods)
				movefn(self, btnmask, mx, my, mods)
			end)
			agl.agl_gfx_set_mouse_move_func(self.unwrapped, c_movefn)
		end,
		_setScrollFunc = function(self, scrollfn)
			local c_scrollfn = ffi.cast("agl_gfx_scroll_func", function(sx, sy)
				scrollfn(self, sx, sy)
			end)
			agl.agl_gfx_set_scroll_func(self.unwrapped, c_scrollfn)
		end,
		isKeyDown = function(self, key)
			return agl.agl_gfx_is_key_down(self.unwrapped, key)
		end,
		createImage = function(self, width, height, data)
			return ffi.new("agl_gfx_image_wrapper_t", agl.agl_gfx_create_image(self.unwrapped, ffi.new("agl_gfx_image_params_t", {
				width = width,
				height = height,
				format = 0, -- TODO: support different formats
				pixelData = data,
			})))
		end,
		createBuffer = function(self, size, data, flags)
			return ffi.new("agl_gfx_buffer_wrapper_t", agl.agl_gfx_create_buffer(self.unwrapped, ffi.new("agl_gfx_buffer_params_t", {
				size = size,
				data = data,
				flags = flags,
			})))
		end,
		createMesh = function(self, vertexCount, indexCount, positionData, uvData, normalData, colorData, indexData)
			return ffi.new("agl_gfx_mesh_wrapper_t", agl.agl_gfx_create_mesh(self.unwrapped, ffi.new("agl_gfx_mesh_params_t", {
				vertexCount = vertexCount,
				indexCount = indexCount,
				positionData = positionData,
				uvData = uvData,
				normalData = normalData,
				colorData = colorData,
				indexData = indexData,
			})))
		end,
		loadMeshes = function(self, path)
			local meshes = {}
			local loadParams = ffi.new("agl_gfx_load_params_t", {
				meshCallback = function(context, params, name)
					-- This callback is called by the plugin when a mesh is loaded. We can create the mesh here and store it in a table for later retrieval.
					local meshWrapper = ffi.new("agl_gfx_mesh_wrapper_t", agl.agl_gfx_create_mesh(context, params))
					meshes[#meshes+1] = meshWrapper -- Store in array part for iteration
					meshes[name] = meshWrapper
				end,
				imageCallback = nil,
			})
			local result = agl.agl_gfx_load_file(self.unwrapped, path, loadParams)
			if result ~= 1 then
				return nil, "Failed to load mesh: " .. path
			end
			return meshes
		end,
	},
	__gc = function(self)
		agl.agl_gfx_destroy_context(self.unwrapped)
	end,
}
ffi.metatype("agl_gfx_context_wrapper_t", context_mt)

local canvas_mt = {
	__index = {
		getSize = function(self)
			local width = ffi.new("uint32_t[1]")
			local height = ffi.new("uint32_t[1]")
			agl.agl_gfx_canvas_get_size(self.unwrapped, width, height)
			return width[0], height[0]
		end,
		setCameraPosition = function(self, x, y, z)
			agl.agl_gfx_set_camera_position(self.unwrapped, ffi.new("float[3]", {x, y, z}))
		end,
		setCameraLookAt = function(self, tgtX, tgtY, tgtZ, upX, upY, upZ)
			agl.agl_gfx_set_camera_look_at(self.unwrapped, ffi.new("float[3]", {tgtX, tgtY, tgtZ}), ffi.new("float[3]", {upX, upY, upZ}))
		end,
		setCameraPerspective = function(self, fovY, nearZ, farZ)
			agl.agl_gfx_set_camera_perspective(self.unwrapped, fovY, nearZ, farZ)
		end,
		drawScreenQuad = function(self, x, y, width, height, angle, color, texture)
			agl.agl_gfx_draw_screen_quad(self.unwrapped, ffi.new("float[2]", {x, y}), ffi.new("float[2]", {width, height}), angle, color, texture and texture.unwrapped or 0)
		end,
		drawMesh = function(self, mesh, pos, rot, scale, r, g, b, a)
			agl.agl_gfx_draw_mesh(self.unwrapped, mesh.unwrapped, ffi.cast("float*", pos), ffi.cast("float*", rot), scale, ffi.new("float[4]", {r, g, b, a}))
		end,
		drawText = function(self, text, x, y, height, color)
			agl.agl_gfx_canvas_draw_text(self.unwrapped, text, x, y, height, color)
		end,
	},
}
ffi.metatype("agl_gfx_canvas_wrapper_t", canvas_mt)

local vec3f_mt = {
	__index = {
		new = function(x, y, z)
			return ffi.new("vec3f_t", x, y, z, 0)
		end,
	},
}
ffi.metatype("vec3f_t", vec3f_mt)

local quatf_mt = {
	__index = {
		inv = function(self)
			agl.quatf_inv(self)
		end,
		add = function(self, b)
			agl.quatf_add(self, b)
		end,
		addScaled = function(self, b, s)
			agl.quatf_addscaled(self, b, s)
		end,
		sub = function(self, b)
			agl.quatf_sub(self, b)
		end,
		mul2 = function(a, b)
			local result = ffi.new("quatf_t")
			agl.quatf_mul2(result, a, b)
			return result
		end,
		fromAxisAngle = function(axis, angle)
			local result = ffi.new("quatf_t")
			agl.quatf_fromaxisangle(result, axis, angle)
			return result
		end,
		fromVectors = function(a, b)
			local result = ffi.new("quatf_t")
			agl.quatf_fromvectors(result, a, b)
			return result
		end,
		new = function(x, y, z, w)
			return ffi.new("quatf_t", x, y, z, w)
		end,
	},
}
ffi.metatype("quatf_t", quatf_mt)

local math = {
	quatf = quatf_mt.__index,
	vec3f = vec3f_mt.__index,
}

return {
	-- Application configuration
	title = "AGL LuaJIT Demo",
	width = 800,
	height = 600,
	resizable = false,
	plugins = {},
	load = function(context) end,
	update = function(context, deltaTime) end,
	onkey = function(context, key, down, repeat_, scancode) end,
	onmousebutton = function(context, btnmask, mx, my, down, mods) end,
	onmousemove = function(context, btnmask, mx, my, mods) end,
	onscroll = function(context, sx, sy) end,
	run = function(self)
		for _, pluginPath in ipairs(self.plugins) do
			local result = agl.agl_load_plugin(pluginPath)
			if result ~= 1 then
				error("Failed to load plugin: " .. pluginPath)
			end
		end
		local params = ffi.new("agl_gfx_create_params_t", {
			appname = self.title,
			width = self.width,
			height = self.height,
			imagePoolSize = config.IMAGE_POOL_SIZE,
			bufferPoolSize = config.BUFFER_POOL_SIZE,
			meshPoolSize = config.MESH_POOL_SIZE,
			quadPoolSize = config.QUAD_POOL_SIZE,
			scratchMemory = {
				allocationBase = nil,
				allocationSize = config.SCRATCH_MEMORY_SIZE,
			},
		})
		local context = ffi.new("agl_gfx_context_wrapper_t", agl.agl_gfx_create_context(params))
		context:_setUpdateFunc(self.update)
		context:_setKeyFunc(self.onkey)
		context:_setMouseButtonFunc(self.onmousebutton)
		context:_setMouseMoveFunc(self.onmousemove)
		context:_setScrollFunc(self.onscroll)
		agl.agl_gfx_context_init_plugins(context.unwrapped)
		self.load(context)
		agl.agl_gfx_main_loop(context.unwrapped)
	end,
	memconfig = config,
	-- AGL libraries
	math = math,
	-- Constants
	KEY_SPACE = agl.AGL_GFX_KEY_SPACE,
	KEY_LEFT = agl.AGL_GFX_KEY_LEFT,
	KEY_RIGHT = agl.AGL_GFX_KEY_RIGHT,
	KEY_UP = agl.AGL_GFX_KEY_UP,
	KEY_DOWN = agl.AGL_GFX_KEY_DOWN,
	KEY_W = agl.AGL_GFX_KEY_W,
	KEY_A = agl.AGL_GFX_KEY_A,
	KEY_S = agl.AGL_GFX_KEY_S,
	KEY_D = agl.AGL_GFX_KEY_D,
	-- Utility functions
	screenToNdc = function(x, y, screenWidth, screenHeight)
		return (x / screenWidth) * 2 - 1, 1 - (y / screenHeight) * 2
	end,
}
