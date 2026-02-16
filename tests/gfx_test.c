#include "../agl_gfx.h"

#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define RADIANS(deg) ((deg) * (M_PI / 180.0))
#define NELEM(arr) (sizeof(arr) / sizeof(0[arr]))

agl_gfx_mesh_t cube;
agl_gfx_image_t image;

void update(agl_gfx_context_t context, agl_gfx_time_t deltaTime) {
	agl_gfx_canvas_t canvas = agl_gfx_get_default_canvas(context);
	agl_uint cw, ch;
	agl_gfx_get_canvas_size(canvas, &cw, &ch);
	static float angle = 0;
	angle += deltaTime * 100.f;
	angle = angle > 360.0f ? angle - 360.0f : angle;
	agl_float2 pos = {(400.f / cw) * 2.f - 1.f, (1.f - 200.f / ch) * 2.f - 1.f};
	agl_float2 size = {200.f / cw, 200.f / ch};
	agl_gfx_draw_screen_quad(canvas, pos, size, RADIANS(angle), 0xFFFFFFFF, image);

	agl_float4 rot = {sinf(RADIANS(angle / 2.0f)), 0, 0, cosf(RADIANS(angle / 2.0f))};
	agl_gfx_draw_mesh(canvas, cube, (agl_float3){0.f, 0.f, -5.f}, rot, 1.0f, (agl_float4){1.f, 1.f, 1.f, 1.f});

	agl_gfx_draw_text(canvas, (agl_float2){ 0, 0 }, 0.05, 0xFFFFFFFF, "agl_gfx");
	agl_gfx_draw_text(canvas, (agl_float2){ 0.05 * 6, 0 }, 0.05, 0xFFFFFFFF, "v0.1.23-dev");

	agl_gfxh_show_font_texture(canvas, (agl_float2){ -0.0f, 0.7f });
}

int main() {
	void *scratchMemory = malloc(200 * 1024); // 200 KB of scratch memory

	agl_gfx_create_params_t createParams = {
		.appname = "AGL GFX Test",
		.width = 800,
		.height = 600,
		.imagePoolSize = 10,
		.bufferPoolSize = 10,
		.meshPoolSize = 10,
		.quadPoolSize = 10,
		.scratchMemory = {
			.allocationBase = scratchMemory,
			.allocationSize = 200 * 1024,
		},
	};

	agl_gfx_context_t context = agl_gfx_create_context(&createParams);
	if (!context) {
		printf("Failed to create graphics context\n");
		return -1;
	}

	image = agl_gfx_create_image(context, &(agl_gfx_image_params_t){
		.width = 2,
		.height = 2,
		.format = AGL_GFX_IMAGE_FORMAT_R8G8B8A8_UNORM,
		.pixelData = (agl_color[]){
			0xFFFFFFFF, 0xFF000000,
			0xFF000000, 0xFFFFFFFF,
		},
	});

	// Cube
    {
        #define V0 { -0.5f, -0.5f,  0.5f, }
        #define V1 {  0.5f, -0.5f,  0.5f, }
        #define V2 {  0.5f,  0.5f,  0.5f, }
        #define V3 { -0.5f,  0.5f,  0.5f, }
        #define V4 {  0.5f, -0.5f, -0.5f, }
        #define V5 { -0.5f, -0.5f, -0.5f, }
        #define V6 { -0.5f,  0.5f, -0.5f, }
        #define V7 {  0.5f,  0.5f, -0.5f, }

        #define CF { 0.f, 0.f, 1.f, 1.f } // +Z
        #define CR { 1.f, 0.f, 0.f, 1.f } // +X
        #define CB { 1.f, 1.f, 0.f, 1.f } // -Z
        #define CL { 0.f, 1.f, 1.f, 1.f } // -X
        #define CT { 0.f, 1.f, 0.f, 1.f } // +Y
        #define CD { 1.f, 0.f, 1.f, 1.f } // -Y

        agl_float3 positions[] = {
            V0, V1, V2, V2, V3, V0, // front
            V1, V4, V7, V7, V2, V1, // right
            V4, V5, V6, V6, V7, V4, // back
            V5, V0, V3, V3, V6, V5, // left
            V3, V2, V7, V7, V6, V3, // top
            V5, V4, V1, V1, V0, V5, // bottom
        };
        agl_float4 colors[] = {
            CF, CF, CF, CF, CF, CF,
            CR, CR, CR, CR, CR, CR,
            CB, CB, CB, CB, CB, CB,
            CL, CL, CL, CL, CL, CL,
            CT, CT, CT, CT, CT, CT,
            CD, CD, CD, CD, CD, CD,
        };
        agl_gfx_mesh_params_t meshParams = {};
        meshParams.vertexCount = NELEM(positions);
        meshParams.positionData = &positions[0][0];
        meshParams.colorData = &colors[0][0];
        // meshParams.indexCount = NELEM(indices);
        // meshParams.indexData = indices;
        cube = agl_gfx_create_mesh(context, &meshParams);

        #undef V0
        #undef V1
        #undef V2
        #undef V3
        #undef V4
        #undef V5
        #undef V6
        #undef V7

        #undef CF
        #undef CR
        #undef CB
        #undef CL
        #undef CT
        #undef CD
    }

	agl_gfx_set_update_func(context, update);

	agl_gfx_canvas_t canvas = agl_gfx_get_default_canvas(context);
	agl_gfx_set_camera_position(canvas, (agl_float3){0,2,10});
    agl_gfx_set_camera_look_at(canvas, (agl_float3){0,2,0}, (agl_float3){0,1,0});
    agl_gfx_set_camera_perspective(canvas, RADIANS(60), 0.1f, 1000.f);

	agl_gfx_main_loop(context);

	agl_gfx_destroy_image(context, image);
	agl_gfx_destroy_mesh(context, cube);
	agl_gfx_destroy_context(context);

	free(scratchMemory);
	return 0;
}

#define AGL_GFX_IMPLEMENTATION
#define AGL_GFX_ENABLE_ASSERTS 1
#include "../agl_gfx.h"