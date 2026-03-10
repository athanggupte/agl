#include "agl_gfx.h"
#include "agl_plugin.h"

#pragma comment(lib, "agl")

#include <stdio.h>
#include <string.h>

int fps_plugin_init(agl_plugin_t *plugin, agl_gfx_context_t context) {
	(void)plugin;
	(void)context;
	printf("FPS Plugin initialized!\n");
	return 1;
}

static float fps = 0.0f;

int fps_plugin_update(agl_plugin_t *plugin, agl_gfx_context_t context, float deltaTime) {
	fps = 1.0f / deltaTime;
	return 1;
}

int fps_plugin_draw(agl_plugin_t *plugin, agl_gfx_context_t context, agl_gfx_canvas_t canvas) {
	(void)plugin;
	char buffer[64];
	snprintf(buffer, sizeof(buffer), "FPS: %d", (int)fps);
	agl_gfx_draw_text(canvas, (agl_float2){-0.92f, 0.9f}, 0.07f, 0xFF00FF00, buffer);
	return 1;
}

int fps_plugin_cleanup(agl_plugin_t *plugin, agl_gfx_context_t context) {
	(void)plugin;
	(void)context;
	printf("FPS Plugin cleaned up!\n");
	return 1;
}

AGL_PLUGIN_API int fps_counter_register() {
	static agl_plugin_t plugin = (agl_plugin_t) {
		.name = "FPS Counter Plugin",
		.description = "Displays the current FPS on the screen.",
		.version = "1.0",
		.author = "Athang Gupte",
		.init = fps_plugin_init,
		.update = fps_plugin_update,
		.draw = fps_plugin_draw,
		.cleanup = fps_plugin_cleanup
	};
	return agl_register_plugin(&plugin);
}