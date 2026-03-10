#ifndef AGL_PLUGIN_H
#define AGL_PLUGIN_H

#ifndef	AGL_API
#	if defined(_WIN32)
#		if defined(AGL_EXPORTS)
#			define AGL_API __declspec(dllexport)
#		elif defined(AGL_IMPORTS)
#			define AGL_API __declspec(dllimport)
#		else
#			define AGL_API extern
#		endif
#	else
#		define AGL_API extern
#	endif
#endif // AGL_API

#ifndef	AGL_PLUGIN_API
#	if defined(_WIN32)
#		if defined(AGL_PLUGIN_EXPORTS)
#			define AGL_PLUGIN_API __declspec(dllexport)
#		else
#			define AGL_PLUGIN_API __declspec(dllimport)
#		endif
#	else
#		define AGL_PLUGIN_API extern
#	endif
#endif // AGL_PLUGIN_API


typedef struct agl_plugin_t agl_plugin_t;
typedef struct agl__gfx_context_t *agl_gfx_context_t;
typedef struct agl__gfx_canvas_t *agl_gfx_canvas_t;

typedef int (*agl_plugin_init_func)(agl_plugin_t *plugin, agl_gfx_context_t context);
typedef int (*agl_plugin_update_func)(agl_plugin_t *plugin, agl_gfx_context_t context, float deltaTime);
typedef int (*agl_plugin_draw_func)(agl_plugin_t *plugin, agl_gfx_context_t context, agl_gfx_canvas_t canvas);
typedef int (*agl_plugin_cleanup_func)(agl_plugin_t *plugin, agl_gfx_context_t context);

struct agl_plugin_t {
	const char* name;
	const char* description;
	const char* version;
	const char* author;
	agl_plugin_init_func init;
	agl_plugin_update_func update;
	agl_plugin_draw_func draw;
	agl_plugin_cleanup_func cleanup;
	unsigned char reserved[8];
};

// Should be called after creating the graphics context to initialize plugins and set up the update loop
AGL_API int agl_gfx_context_init_plugins(agl_gfx_context_t context);

AGL_API int agl_load_plugin(const char* path);

AGL_API int agl_register_plugin(agl_plugin_t *plugin);

#endif // AGL_PLUGIN_H

#ifdef AGL_PLUGIN_IMPLEMENTATION

#ifndef AGL_PLUGIN_IMPLEMENTED
#define AGL_PLUGIN_IMPLEMENTED

#define _CRT_SECURE_NO_WARNINGS

typedef struct agl__plugin_t {
	const char* name;
	const char* description;
	const char* version;
	const char* author;
	agl_plugin_init_func init;
	agl_plugin_update_func update;
	agl_plugin_draw_func draw;
	agl_plugin_cleanup_func cleanup;
	struct agl__plugin_t *next;
} agl__plugin_t;

static agl__plugin_t *agl__plugin_list = NULL;

static agl_gfx_update_func agl__plugin_prev_update_func = NULL;

static void agl__plugin_update_func(agl_gfx_context_t context, agl_gfx_time_t deltaTime) {
	if (agl__plugin_prev_update_func) {
		agl__plugin_prev_update_func(context, deltaTime);
	}
	agl__plugin_t *plugin = agl__plugin_list;
	while (plugin) {
		if (plugin->update) {
			plugin->update((agl_plugin_t*)plugin, context, deltaTime);
		}
		plugin = plugin->next;
	}
	plugin = agl__plugin_list;
	while (plugin) {
		if (plugin->draw) {
			agl_gfx_canvas_t canvas = agl_gfx_get_default_canvas(context);
			plugin->draw((agl_plugin_t*)plugin, context, canvas);
		}
		plugin = plugin->next;
	}
}

int agl_gfx_context_init_plugins(agl_gfx_context_t context) {
	printf("Initializing plugins...\n");
	agl__plugin_t *plugin = agl__plugin_list;
	while (plugin) {
		if (plugin->init) {
			plugin->init((agl_plugin_t*)plugin, context);
		}
		printf("Initialized plugin: %s\n", plugin->name);
		plugin = plugin->next;
	}
	agl__plugin_prev_update_func = agl_gfx_set_update_func(context, agl__plugin_update_func);
	printf("Plugin system initialized. Update function set to: %p (old: %p)\n", agl__plugin_update_func, agl__plugin_prev_update_func);
	return 1;
}

int agl_load_plugin(const char *path) {
#if defined(_WIN32)
	HMODULE handle = LoadLibraryA(path);
	if (!handle) {
		printf("Failed to load plugin: %s\n", path);
		return 0;
	}
	// extract filename
	const char *filename = strrchr(path, '\\');
	if (!filename) {
		filename = strrchr(path, '/');
	}
	if (filename) {
		filename++;
	} else {
		filename = path;
	}
	// remove extension
	char pluginName[256];
	strncpy(pluginName, filename, sizeof(pluginName));
	char *dot = strrchr(pluginName, '.');
	if (dot) {
		*dot = '\0';
	}
	// append _register
	strncat(pluginName, "_register", sizeof(pluginName) - strlen(pluginName) - 1);

	FARPROC register_func = GetProcAddress(handle, pluginName);
	if (!register_func) {
		printf("Failed to find plugin register function: %s\n", pluginName);
		FreeLibrary(handle);
		return 0;
	}
	register_func();
	printf("Successfully loaded plugin: %s\n", path);
	return 1;
#else
#error "Plugin loading not implemented for this platform"
#endif
}

int agl_register_plugin(agl_plugin_t *plugin) {
	agl__plugin_t* plugin_node = (agl__plugin_t*)plugin;
	plugin_node->next = agl__plugin_list;
	agl__plugin_list = plugin_node;
	return 1;
}

#endif // AGL_PLUGIN_IMPLEMENTED

#endif // AGL_PLUGIN_IMPLEMENTATION