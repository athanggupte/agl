// agl_gfx - v0.1.0 - AGL Graphics Library
// 
// PURPOSE
//   AGL Graphics Library is a simple, cross-platform graphics library designed for 
//   2D and 3D rendering in C and C++. It provides a minimalistic API for creating windows,
//   handling input, and rendering graphics using a simple immediate mode style. This library
//   is intended for use in game development, multimedia applications, and other projects that
//   require basic graphics functionality without the overhead of a full-featured engine.
//
// USAGE
//  To use AGL Graphics Library, include this header file in your project and define AGL_GFX_IMPLEMENTATION
//  in *one* source file before including it to create the implementation.
//  Example:
//    #include ...
//    #define AGL_GFX_IMPLEMENTATION
//    #include "agl_gfx.h"
//
//  
// 
// MIT License
//   Copyright (c) 2026 Athang Gupte
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//   The above copyright notice and this permission notice shall be included in all
//   copies or substantial portions of the Software.
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//   SOFTWARE.

#ifndef AGL_GFX_H
#define AGL_GFX_H

enum { AGL_GFX_SUCCESS = 0, AGL_GFX_ERROR = -1 };

typedef struct agl__gfx_context_t *agl_gfx_context_t;
typedef struct agl__gfx_canvas_t *agl_gfx_canvas_t;

typedef float agl_float;
typedef agl_float agl_float2[2];
typedef agl_float agl_float3[3];
typedef agl_float agl_float4[4];
typedef unsigned agl_uint;
typedef unsigned long long agl_uint64;
typedef agl_uint agl_color;

#define AGL_COLOR(r,g,b,a) (agl_uint)((agl_uint)((r)&0xFF) | ((agl_uint)((g)&0xFF)<<8) | ((agl_uint)((b)&0xFF)<<16) | ((agl_uint)((a)&0xFF)<<24))
#define AGL_COLORF(r,g,b,a) (agl_uint)((((agl_uint)((r)*255.f))&0xFF) | ((((agl_uint)((g)*255.f))&0xFF)<<8) | ((((agl_uint)((b)*255.f))&0xFF)<<16) | ((((agl_uint)((a)*255.f))&0xFF)<<24))

typedef struct agl_id {
    union {
        agl_uint id;
        struct {
            agl_uint index : 24;
            agl_uint generation : 8;
        };
    };
} agl_id;

#define AGL_GFX_INVALID_ID ((agl_id){ .id = 0 })

typedef agl_id agl_gfx_image_t;
typedef agl_id agl_gfx_buffer_t;
typedef agl_id agl_gfx_mesh_t;
typedef agl_id agl_gfx_material_t;

typedef enum agl_gfx_image_format_t {
    AGL_GFX_IMAGE_FORMAT_NONE,
    AGL_GFX_IMAGE_FORMAT_R8_UNORM,
    AGL_GFX_IMAGE_FORMAT_R8G8_UNORM,
    AGL_GFX_IMAGE_FORMAT_R8G8B8_UNORM,
    AGL_GFX_IMAGE_FORMAT_R8G8B8A8_UNORM,
    AGL_GFX_IMAGE_FORMAT_R8_SNORM,
    AGL_GFX_IMAGE_FORMAT_R8G8_SNORM,
    AGL_GFX_IMAGE_FORMAT_R8G8B8_SNORM,
    AGL_GFX_IMAGE_FORMAT_R8G8B8A8_SNORM,
    AGL_GFX_IMAGE_FORMAT_R16F,
    AGL_GFX_IMAGE_FORMAT_R16G16F,
    AGL_GFX_IMAGE_FORMAT_R16G16B16F,
    AGL_GFX_IMAGE_FORMAT_R16G16B16A16F,
} agl_gfx_image_format_t;

enum agl_gfx_buffer_flag_bits {
    AGL_GFX_BUFFER_FLAG_DYNAMIC_BIT = 0x0001,
    AGL_GFX_BUFFER_FLAG_MAP_PERSISTENT_BIT = 0x0002,
    AGL_GFX_BUFFER_FLAG_MAP_COHERENT_BIT = 0x0004,
};

typedef struct agl_gfx_create_params_t {
    const char *appname;
    agl_uint width;
    agl_uint height;
    agl_uint imagePoolSize;
    agl_uint bufferPoolSize;
    agl_uint meshPoolSize;
    agl_uint quadPoolSize;
    struct {
        void *allocationBase;
        agl_uint64 allocationSize;
    } scratchMemory;
} agl_gfx_create_params_t;

typedef struct agl_gfx_image_params_t {
    agl_uint width;
    agl_uint height;
    agl_gfx_image_format_t format;
    void *pixelData;
} agl_gfx_image_params_t;

typedef struct agl_gfx_buffer_params_t {
    agl_uint size;
    void *data;
    agl_uint flags;
} agl_gfx_buffer_params_t;

typedef struct agl_gfx_mesh_params_t {
    agl_uint vertexCount;
    agl_uint indexCount;
    agl_float *positionData;
    agl_float *uvData;
    agl_float *normalData;
    agl_float *colorData;
    agl_uint *indexData;
} agl_gfx_mesh_params_t;

typedef struct agl_gfx_mesh_buffer_info_t {
    agl_uint PositionStart;
    agl_uint UVStart;
    agl_uint NormalStart;
    agl_uint ColorStart;
} agl_gfx_mesh_buffer_info_t;

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
} agl_gfx_key_t;

typedef enum agl_gfx_mouse_button_t {
    AGL_GFX_MOUSE_BUTTON_0 = 0x01,
    AGL_GFX_MOUSE_BUTTON_1 = 0x02,
    AGL_GFX_MOUSE_BUTTON_2 = 0x04,
    AGL_GFX_MOUSE_BUTTON_3 = 0x08,
    AGL_GFX_MOUSE_BUTTON_4 = 0x10,
    AGL_GFX_MOUSE_BUTTON_5 = 0x20,
    AGL_GFX_MOUSE_BUTTON_6 = 0x40,
    AGL_GFX_MOUSE_BUTTON_7 = 0x80,
    AGL_GFX_MOUSE_BUTTON_LEFT = AGL_GFX_MOUSE_BUTTON_0,
    AGL_GFX_MOUSE_BUTTON_RIGHT = AGL_GFX_MOUSE_BUTTON_1,
    AGL_GFX_MOUSE_BUTTON_MIDDLE = AGL_GFX_MOUSE_BUTTON_2,
} agl_gfx_mouse_button_t;

typedef enum agl_gfx_mod_key_t {
    AGL_GFX_MOD_SHIFT = 0x01,
    AGL_GFX_MOD_CONTROL = 0x02,
} agl_gfx_mod_key_t;

typedef agl_float agl_gfx_time_t;
typedef void (*agl_gfx_update_func)(agl_gfx_context_t context, agl_gfx_time_t deltaTime);
typedef void (*agl_gfx_user_pointer_delete_func)(void *udata);
typedef void (*agl_gfx_key_func)(agl_gfx_key_t key, int down, int repeat, int scancode);
typedef void (*agl_gfx_mouse_button_func)(int btnmask, agl_float mx, agl_float my, int down, int mods);
typedef void (*agl_gfx_mouse_move_func)(int btnmask, agl_float mx, agl_float my, int mods);
typedef void (*agl_gfx_scroll_func)(agl_float sx, agl_float sy);

// Context management

/// @brief Creates a new graphics context with the specified parameters
/// @param params Pointer to a structure containing the parameters for creating the graphics context
/// @return A handle to the created graphics context, or NULL on failure
agl_gfx_context_t agl_gfx_create_context(const agl_gfx_create_params_t *params);
/// @brief Destroys a graphics context
/// @param context The graphics context to destroy
void agl_gfx_destroy_context(agl_gfx_context_t context);
/// @brief Enters the main rendering loop for the graphics context, which will continue until the context is destroyed
/// @param context The graphics context to enter the main loop for
void agl_gfx_main_loop(agl_gfx_context_t context);
/// @brief Retrieves the default canvas associated with the graphics context, which can be used for rendering operations
///   This is the backbuffer of the window for native applicatioins, and the framebuffer for web applications.
/// @param context The graphics context to retrieve the default canvas from
/// @return The default canvas associated with the graphics context, or NULL if the context is invalid
agl_gfx_canvas_t agl_gfx_get_default_canvas(agl_gfx_context_t context);
/// @brief Retrieves the size of the canvas in pixels
/// @param canvas The canvas to retrieve the size of
/// @param width Pointer to a variable that will receive the width of the canvas in pixels
/// @param height Pointer to a variable that will receive the height of the canvas in pixels
void agl_gfx_get_canvas_size(agl_gfx_canvas_t canvas, agl_uint *width, agl_uint *height);

// Input handling

/// @brief Sets the update function that will be called every frame with the time delta since the last frame
/// @return The old update function or NULL
agl_gfx_update_func agl_gfx_set_update_func(agl_gfx_context_t context, agl_gfx_update_func updatefn);
/// @brief Sets the function that will be called when a key event occurs
/// @return The old keyboard handling function or NULL
agl_gfx_key_func agl_gfx_set_key_func(agl_gfx_context_t context, agl_gfx_key_func keyfn);
/// @brief Sets the function that will be called when a mouse button event occurs
/// @return The old mouse button handling function or NULL
agl_gfx_mouse_button_func agl_gfx_set_mouse_button_func(agl_gfx_context_t context, agl_gfx_mouse_button_func mousefn);
/// @brief Sets the function that will be called when a mouse move event occurs
/// @return The old mouse move handling function or NULL
agl_gfx_mouse_move_func agl_gfx_set_mouse_move_func(agl_gfx_context_t context, agl_gfx_mouse_move_func movefn);
/// @brief Sets the function that will be called when a mouse scroll event occurs
/// @return The old mouse scroll handling function or NULL 
agl_gfx_scroll_func agl_gfx_set_scroll_func(agl_gfx_context_t context, agl_gfx_scroll_func scrollfn);
/// @brief Sets the function that will be called to delete user pointers associated with graphics resources
/// @return The old user pointer deletion function or NULL
agl_gfx_user_pointer_delete_func agl_gfx_set_user_pointer_delete_func(agl_gfx_context_t context, agl_gfx_user_pointer_delete_func deletefn);

// Resource management

/// @brief Sets a user pointer that will be associated with the graphics context and can be retrieved later.
///   This is useful for associating custom data with the graphics context, such as application state or resource management information.
/// @note The user pointer will be automatically deleted using the user pointer deletion function set by `agl_gfx_set_user_pointer_delete_func`
///   when the graphics context is destroyed or when a new user pointer is set.
/// @param context The graphics context to associate the user pointer with
/// @param udata The user pointer to associate with the graphics context
void agl_gfx_set_user_pointer(agl_gfx_context_t context, void *udata);
/// @brief Retrieves the user pointer associated with the graphics context
/// @param context The graphics context to retrieve the user pointer from
/// @return The user pointer associated with the graphics context, or NULL if no user pointer is set
void* agl_gfx_get_user_pointer(agl_gfx_context_t context);

/// @brief Creates a new image in the specified graphics context with the given parameters
/// @param context The graphics context in which to create the image
/// @param params Pointer to a structure containing the parameters for creating the image
/// @return A handle to the created image, or NULL on failure
agl_gfx_image_t agl_gfx_create_image(agl_gfx_context_t context, const agl_gfx_image_params_t *params);
/// @brief Destroys an image in the specified graphics context
/// @param context The graphics context in which the image was created
/// @param image The image to destroy
void agl_gfx_destroy_image(agl_gfx_context_t context, agl_gfx_image_t image);

/// @brief Creates a new buffer in the specified graphics context with the given parameters
/// @param context The graphics context in which to create the buffer
/// @param params Pointer to a structure containing the parameters for creating the buffer
/// @return A handle to the created buffer, or NULL on failure
agl_gfx_buffer_t agl_gfx_create_buffer(agl_gfx_context_t context, const agl_gfx_buffer_params_t *params);
/// @brief Destroys a buffer in the specified graphics context
/// @param context The graphics context in which the buffer was created
/// @param buffer The buffer to destroy
void agl_gfx_destroy_buffer(agl_gfx_context_t context, agl_gfx_buffer_t buffer);

/// @brief Creates a new mesh in the specified graphics context with the given parameters
/// @param context The graphics context in which to create the mesh
/// @param params Pointer to a structure containing the parameters for creating the mesh
/// @return A handle to the created mesh, or NULL on failure
agl_gfx_mesh_t agl_gfx_create_mesh(agl_gfx_context_t context, const agl_gfx_mesh_params_t *params);
/// @brief Destroys a mesh in the specified graphics context
/// @param context The graphics context in which the mesh was created
/// @param mesh The mesh to destroy
void agl_gfx_destroy_mesh(agl_gfx_context_t context, agl_gfx_mesh_t mesh);

// Camera control

/// @brief Sets the position of the camera in the graphics context
/// @param context The graphics context to set the camera position for
/// @param pos The position of the camera as a 3D vector (x, y, z)
void agl_gfx_set_camera_position(agl_gfx_canvas_t canvas, const agl_float3 pos);
/// @brief Sets the camera to look at a target point in the world
/// @param context The graphics context to set the camera orientation for
/// @param tgt The target point in the world that the camera should look at, as a 3D vector (x, y, z)
/// @param worldUp The camera's up direction in the world, as a 3D vector (x, y, z). This is used to determine the roll of the camera when looking at the target.
void agl_gfx_set_camera_look_at(agl_gfx_canvas_t canvas, const agl_float3 tgt, const agl_float3 worldUp);
/// @brief Sets the orientation of the camera using a quaternion
/// @param context The graphics context to set the camera orientation for
/// @param quat The orientation of the camera as a quaternion (x, y, z, w)
void agl_gfx_set_camera_orient_quat(agl_gfx_canvas_t canvas, const agl_float4 quat);
/// @brief Sets the orientation of the camera using a rotation matrix
/// @param context The graphics context to set the camera orientation for
/// @param rot The orientation of the camera as a 3x3 rotation matrix, represented as an array of 3 agl_float3 vectors (right, up, forward)
void agl_gfx_set_camera_orient_matrix(agl_gfx_canvas_t canvas, const agl_float3 rot[3]);
/// @brief Sets the projection of the camera to a perspective projection with the specified parameters
/// @param context The graphics context to set the camera projection for
/// @param fovY The vertical field of view of the camera in radians
/// @param nearZ The distance to the near clipping plane
/// @param farZ The distance to the far clipping plane
void agl_gfx_set_camera_perspective(agl_gfx_canvas_t canvas, agl_float fovY, agl_float nearZ, agl_float farZ);

// Rendering

void agl_gfx_clear(agl_gfx_canvas_t canvas, agl_float r, agl_float g, agl_float b, agl_float a);
void agl_gfx_draw_screen_quad(agl_gfx_canvas_t canvas, const agl_float2 pos, const agl_float2 size, agl_float angle, agl_color color, agl_gfx_image_t texture);
void agl_gfx_draw_mesh(agl_gfx_canvas_t canvas, agl_gfx_mesh_t mesh, const agl_float3 pos, const agl_float4 rot, agl_float scale, const agl_float4 color);
void agl_gfx_draw_text(agl_gfx_canvas_t canvas, const agl_float2 startpos, agl_float height, agl_color color, const char *text);

// Debug utilities
void agl_gfxh_show_font_texture(agl_gfx_canvas_t canvas, const agl_float2 position);

#endif // AGL_GFX_H

#ifdef AGL_GFX_IMPLEMENTATION

#ifndef AGL_GFX_IMPLEMENTED
#define AGL_GFX_IMPLEMENTED

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#if AGL_GFX_ENABLE_ASSERTS
#include <stdio.h>
#define agl__gfx_errorf(fmt,...) (printf("[Error] %s:%d : " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define agl__gfx_assertf(cond,fmt,...) do { if (!(cond)) { agl__gfx_errorf("Assertion Failed: %s. " fmt, #cond, ##__VA_ARGS__); __debugbreak(); } } while (0)
#else
#define agl__gfx_errorf(fmt,...) do {} while (0)
#define agl__gfx_assertf(cond,fmt,...) do {} while (0)
#endif

#define XSTR(x) #x
#define STR(x) XSTR(x)

#define KiB(x) ((x) * 1024ULL)
#define MiB(x) (KiB(x) * 1024ULL)
#define GiB(x) (MiB(x) * 1024ULL)

// TODO: Make this thread local and add support for multiple temp allocators if needed. For now we can just use a single global one since the library is not thread safe anyway.
typedef struct agl__ScratchAllocator {
    char *beg;
    char *end;
    char *cur;
} agl__ScratchAllocator;
static void* agl__ScratchAlloc(agl__ScratchAllocator *allocator, agl_uint size) {
    agl__gfx_assertf(allocator->cur > allocator->beg + size, "Insuffient temp memory! Required %u remaining %u", size, (agl_uint)(allocator->cur - allocator->beg));
    allocator->cur -= size;
    return allocator->cur;
}
static void agl__ScratchFree(agl__ScratchAllocator *allocator) {
    allocator->cur = allocator->end;
}

#if !defined(AGL_GFX_USE_EXTERNAL_GL_LOADER)
#endif

#if defined(_WIN32)
#   define GL_GLEXT_PROTOTYPES
#   define WIN32_LEAN_AND_MEAN 1
#   include <windows.h>
#   include <windowsx.h>
#   ifndef APIENTRY
#   define APIENTRY
#   endif
#   ifndef GLAPI
#   define GLAPI extern
#   endif
#elif defined(__linux__) || defined(__unix__)
#   define GL_GLEXT_PROTOTYPES
#   include <GL/gl.h>
#endif

#if defined(_WIN32)
// OpenGL types
typedef void GLvoid;
typedef unsigned int GLenum;
typedef float GLfloat;
typedef int GLint;
typedef int GLsizei;
typedef unsigned int GLbitfield;
typedef double GLdouble;
typedef unsigned int GLuint;
typedef unsigned char GLboolean;
typedef char GLchar;
typedef uint8_t GLubyte;
typedef uint64_t GLuint64;
typedef int64_t GLsizeiptr;
typedef int64_t GLintptr;
// OpenGL function forward declarations
GLAPI void APIENTRY glDisable (GLenum cap);
GLAPI void APIENTRY glEnable (GLenum cap);
GLAPI void APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GLAPI void APIENTRY glDepthFunc (GLenum func);
GLAPI void APIENTRY glCullFace (GLenum mode);
GLAPI void APIENTRY glFrontFace (GLenum mode);
GLAPI void APIENTRY glDeleteTextures (GLsizei n, const GLuint *textures);
GLAPI void APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei count);
GLAPI void APIENTRY glDrawElements (GLenum mode, GLsizei count, GLenum type, const void *indices);
GLAPI void APIENTRY glClear (GLbitfield mask);
GLAPI void APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GLAPI void APIENTRY glClearStencil (GLint s);
GLAPI void APIENTRY glClearDepth (GLdouble depth);
GLAPI void APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
// OpenGL function pointer types
typedef void (APIENTRY  *GLDEBUGPROC) (GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void (APIENTRY *PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC callback, const void *userParam);
typedef GLuint (APIENTRY *PFNGLCREATESHADERPROC) (GLenum type);
typedef void (APIENTRY *PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void (APIENTRY *PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef void (APIENTRY *PFNGLDELETESHADERPROC) (GLuint shader);
typedef GLuint (APIENTRY *PFNGLCREATEPROGRAMPROC) (void);
typedef void (APIENTRY *PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef void (APIENTRY *PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRY *PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRY *PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (APIENTRY *PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (APIENTRY *PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
typedef void (APIENTRY *PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRY *PFNGLCREATEVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef void (APIENTRY *PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (APIENTRY *PFNGLCREATEBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRY *PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRY *PFNGLNAMEDBUFFERSTORAGEPROC) (GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags);
typedef void (APIENTRY *PFNGLNAMEDBUFFERSUBDATAPROC) (GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data);
typedef void (APIENTRY *PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY *PFNGLBINDBUFFERBASEPROC) (GLenum target, GLuint index, GLuint buffer);
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM2FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM4FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRY *PFNGLCREATETEXTURESPROC) (GLenum target, GLsizei n, GLuint *textures);
typedef void (APIENTRY *PFNGLTEXTURESTORAGE2DPROC) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRY *PFNGLTEXTURESUBIMAGE2DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRY *PFNGLTEXTUREPARAMETERIPROC) (GLuint texture, GLenum pname, GLint param);
typedef GLuint64 (APIENTRY *PFNGLGETTEXTUREHANDLEARBPROC) (GLuint texture);
typedef void (APIENTRY *PFNGLMAKETEXTUREHANDLERESIDENTARBPROC) (GLuint64 handle);
typedef void (APIENTRY *PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC) (GLuint64 handle);
typedef void (APIENTRY *PFNGLBINDTEXTUREUNITPROC) (GLuint unit, GLuint texture);
typedef void (APIENTRY *PFNGLOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
// OpenGL constants
#define GL_FALSE                          0
#define GL_TRUE                           1
#define GL_NONE                           0
#define GL_ZERO                           0
#define GL_ONE                            1

#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000

#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define GL_QUADS                          0x0007

#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207

#define GL_BLEND                          0x0BE2
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308

#define GL_CULL_FACE                      0x0B44
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_FRONT_AND_BACK                 0x0408
#define GL_CW                             0x0900
#define GL_CCW                            0x0901

#define GL_DEPTH_TEST                     0x0B71
#define GL_STENCIL_TEST                   0x0B90

#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82

#define GL_MAP_PERSISTENT_BIT             0x0040
#define GL_MAP_COHERENT_BIT               0x0080
#define GL_DYNAMIC_STORAGE_BIT            0x0100
#define GL_CLIENT_STORAGE_BIT             0x0200

#define GL_R8                             0x8229
#define GL_RG8                            0x822B
#define GL_RGB8                           0x8051
#define GL_RGBA8                          0x8058
#define GL_R8_SNORM                       0x8F94
#define GL_RG8_SNORM                      0x8F95
#define GL_RGB8_SNORM                     0x8F96
#define GL_RGBA8_SNORM                    0x8F97
#define GL_R16F                           0x822D
#define GL_RG16F                          0x822F
#define GL_RGB16F                         0x881B
#define GL_RGBA16F                        0x881A

#define GL_RED                            0x1903
#define GL_RG                             0x8227
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908

#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406

#define GL_TEXTURE                        0x1702
#define GL_TEXTURE_2D                     0x0DE1
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
#define GL_REPEAT                         0x2901
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703

#define GL_SHADER_STORAGE_BUFFER          0x90D2
#define GL_ELEMENT_ARRAY_BUFFER           0x8893

#define GL_DEBUG_OUTPUT_SYNCHRONOUS       0x8242
#define GL_DEBUG_TYPE_ERROR               0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR  0x824E
#define GL_DEBUG_TYPE_PORTABILITY         0x824F
#define GL_DEBUG_TYPE_PERFORMANCE         0x8250
#define GL_DEBUG_TYPE_OTHER               0x8251
#define GL_DEBUG_TYPE_MARKER              0x8268
#define GL_DEBUG_TYPE_PUSH_GROUP          0x8269
#define GL_DEBUG_TYPE_POP_GROUP           0x826A
#define GL_DEBUG_SEVERITY_NOTIFICATION    0x826B
#define GL_DEBUG_OUTPUT                   0x92E0
// WGL types
typedef BOOL (WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
typedef HGLRC (WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);
// WGL constants
#define WGL_DRAW_TO_WINDOW_ARB            0x2001
#define WGL_ACCELERATION_ARB              0x2003
#define WGL_SWAP_METHOD_ARB               0x2007
#define WGL_SUPPORT_OPENGL_ARB            0x2010
#define WGL_DOUBLE_BUFFER_ARB             0x2011
#define WGL_PIXEL_TYPE_ARB                0x2013
#define WGL_COLOR_BITS_ARB                0x2014
#define WGL_RED_BITS_ARB                  0x2015
#define WGL_GREEN_BITS_ARB                0x2017
#define WGL_BLUE_BITS_ARB                 0x2019
#define WGL_ALPHA_BITS_ARB                0x201B
#define WGL_DEPTH_BITS_ARB                0x2022
#define WGL_STENCIL_BITS_ARB              0x2023
#define WGL_FULL_ACCELERATION_ARB         0x2027
#define WGL_SWAP_COPY_ARB                 0x2029
#define WGL_TYPE_RGBA_ARB                 0x202B
#define WGL_SAMPLE_BUFFERS_ARB            0x2041
#define WGL_SAMPLES_ARB                   0x2042
#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define WGL_CONTEXT_FLAGS_ARB             0x2094
#define WGL_CONTEXT_DEBUG_BIT_ARB         0x00000001
#define WGL_CONTEXT_PROFILE_MASK_ARB      0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB  0x00000001
#endif // _WIN32

typedef struct agl__FreeListNode {
    agl_id prevId;
    agl_uint isAlive; // 0 if the resource is dead, tex/buf handle if alive, used for freelist management
    agl_uint next;
} agl__FreeListNodeT;

#define DECLARE_POOL_TYPE(T, ClassName)                         \
    typedef struct ClassName ClassName;                         \
    void ClassName##Init(ClassName *pool, agl_uint maxElems);   \
    void ClassName##Shutdown(ClassName *pool);                  \
    T* ClassName##Alloc(ClassName *pool);                       \
    void ClassName##Free(ClassName *pool, T *elem);             \
    T* ClassName##Get(ClassName *pool, agl_id id);              \
    struct ClassName {                                          \
        T *elems;                                               \
        agl_uint total;                                         \
        agl_uint used;                                          \
        agl_uint freeListStart;                                 \
    }

#define DEFINE_POOL_FUNCTIONS(T, ClassName)                                 \
    void ClassName##Init(ClassName *pool, agl_uint maxCount) {              \
        pool->elems = (T*)malloc(maxCount * sizeof(T));                     \
        pool->total = maxCount;                                             \
        pool->used = 0;                                                     \
        pool->freeListStart = -1;                                           \
    }                                                                       \
    void ClassName##Shutdown(ClassName *pool) {                             \
        free(pool->elems);                                                  \
        pool->elems = NULL;                                                 \
        pool->total = 0;                                                    \
        pool->used = 0;                                                     \
        pool->freeListStart = -1;                                           \
    }                                                                       \
    T* ClassName##Alloc(ClassName *pool) {                                  \
        agl__gfx_assertf(pool->used < pool->total, STR(T) " pool full!");   \
        if (pool->used >= pool->total)                                      \
            return NULL;                                                    \
        T *elem = NULL;                                                     \
        if (pool->freeListStart != -1) {                                    \
            elem = &pool->elems[pool->freeListStart];                       \
            elem->id.generation++;                                          \
            agl__gfx_assertf(((agl__FreeListNodeT*)elem)->isAlive == 0, "Overwriting alive pool element! Something must have gone seriously wrong!"); \
            pool->freeListStart = ((agl__FreeListNodeT*)elem)->next;        \
            pool->used++;                                                   \
        } else {                                                            \
            agl_uint index = pool->used++;                                  \
            elem = &pool->elems[index];                                     \
            elem->id.index = index + 1;                                     \
            elem->id.generation = 0;                                        \
        }                                                                   \
        return elem;                                                        \
    }                                                                       \
    void ClassName##Free(ClassName *pool, T *elem) {                        \
        ((agl__FreeListNodeT*)elem)->next = pool->freeListStart;            \
        pool->freeListStart = (agl_uint)(elem - pool->elems);               \
        pool->used--;                                                       \
    }                                                                       \
    T* ClassName##Get(ClassName *pool, agl_id id) {                         \
        if (id.id == 0)                                                     \
            return NULL;                                                    \
        agl__gfx_assertf(id.index <= pool->total, "Invalid id : %u! Resource index (%u) is out of range (range: 1 to %u).", id.id, id.index, pool->total); \
        T *elem = &pool->elems[id.index - 1];                               \
        if (elem->id.id == id.id)                                           \
            return elem;                                                    \
        agl__gfx_assertf(false, "Invalid id : %u! Resource id does not match : expected %u[%u:%u], got %u[%u:%u].", id.id, id.id, id.generation, id.index, elem->id.id, elem->id.generation, elem->id.index); \
        return NULL;                                                        \
    }

#define DEFINE_POOL(T, ClassName) DECLARE_POOL_TYPE(T, ClassName); DEFINE_POOL_FUNCTIONS(T, ClassName);

typedef struct agl__gfx_image_t {
    agl_id id;
    GLuint tex;
    agl_uint width;
    agl_uint height;
    agl_gfx_image_format_t format;
    agl_uint64 handle;
    bool isResident;
} agl__gfx_image_t;

typedef struct agl__gfx_buffer_t {
    agl_id id;
    GLuint buf;
    agl_uint size;
} agl__gfx_buffer_t;

typedef struct agl__gfx_mesh_t {
    agl_id id;
    agl_id vertexBufId;
    GLuint ibo;
    agl_uint vertexCount;
    agl_uint indexCount;
} agl__gfx_mesh_t;

DEFINE_POOL(agl__gfx_image_t, agl__ImagePool);
DEFINE_POOL(agl__gfx_buffer_t, agl__BufferPool);
DEFINE_POOL(agl__gfx_mesh_t, agl__MeshPool);

typedef struct agl__gfx_canvas_t agl__gfx_canvas_t;

typedef struct agl__gfx_context_t {
    // State
    bool wantsQuit;
    bool running;
    // Platform
#if defined(_WIN32)
    HINSTANCE hinstance;
    HWND hwnd;
#endif // _WIN32
    // User API
    agl_gfx_update_func updatefn;
    agl_gfx_user_pointer_delete_func deletefn;
    agl_gfx_key_func keyfn;
    agl_gfx_mouse_button_func mousefn;
    agl_gfx_mouse_move_func movefn;
    agl_gfx_scroll_func scrollfn;
    void *udata;
    // Drawing
    agl__gfx_canvas_t *canvas;
    // Resources
    agl__ImagePool imagePool;
    agl__BufferPool bufferPool;
    agl__MeshPool meshPool;
    agl__ScratchAllocator scratchAllocator;
} agl__gfx_context_t;

typedef struct agl__gfx_quad_t {
    agl_float2 pos;
    agl_float2 size;
    agl_float angle;
    agl_uint glyph;
    agl_color color;
    GLuint64 texture;
    agl_uint flags;
} agl__gfx_quad_t;

typedef struct agl__gfx_camera_t {
    agl_float fovY;
    agl_float nearZ;
    agl_float farZ;
    agl_float aspect;
    agl_float3 pos;
    agl_float3 rot[3];
} agl__gfx_camera_t;

typedef struct agl__gfx_canvas_t {
    agl__gfx_context_t *context;
    agl_uint width;
    agl_uint height;
    // 2D Renderer
    GLuint quadProg;
    GLuint quadVao;
    GLuint quadBuf;
    agl__gfx_quad_t *quads;
    agl_uint quadsTotal;
    agl_uint quadsUsed;
    agl_id fontImage;
    agl_uint fontGlyphWidth;
    agl_uint fontGlyphHeight;
    agl_uint fontTexCols;
    agl_uint fontTexRows;
    // 3D Renderer
    agl__gfx_camera_t camera;
    GLuint meshProg;
    GLuint meshVao;
    // Global State
    GLuint activeProg;
    GLuint activeVao;
    agl_gfx_mesh_t activeMesh;
    // agl_gfx_material_t activeMaterial;
} agl__gfx_canvas_t;

typedef enum agl__fontglyph_t {
    AGL_FONT_GLYPH_SPACE,
    AGL_FONT_GLYPH_0,
    AGL_FONT_GLYPH_1,
    AGL_FONT_GLYPH_2,
    AGL_FONT_GLYPH_3,
    AGL_FONT_GLYPH_4,
    AGL_FONT_GLYPH_5,
    AGL_FONT_GLYPH_6,
    AGL_FONT_GLYPH_7,
    AGL_FONT_GLYPH_8,
    AGL_FONT_GLYPH_9,
    AGL_FONT_GLYPH_A,
    AGL_FONT_GLYPH_B,
    AGL_FONT_GLYPH_C,
    AGL_FONT_GLYPH_D,
    AGL_FONT_GLYPH_E,
    AGL_FONT_GLYPH_F,
    AGL_FONT_GLYPH_G,
    AGL_FONT_GLYPH_H,
    AGL_FONT_GLYPH_I,
    AGL_FONT_GLYPH_J,
    AGL_FONT_GLYPH_K,
    AGL_FONT_GLYPH_L,
    AGL_FONT_GLYPH_M,
    AGL_FONT_GLYPH_N,
    AGL_FONT_GLYPH_O,
    AGL_FONT_GLYPH_P,
    AGL_FONT_GLYPH_Q,
    AGL_FONT_GLYPH_R,
    AGL_FONT_GLYPH_S,
    AGL_FONT_GLYPH_T,
    AGL_FONT_GLYPH_U,
    AGL_FONT_GLYPH_V,
    AGL_FONT_GLYPH_W,
    AGL_FONT_GLYPH_X,
    AGL_FONT_GLYPH_Y,
    AGL_FONT_GLYPH_Z,
    AGL_FONT_GLYPH_a,
    AGL_FONT_GLYPH_b,
    AGL_FONT_GLYPH_c,
    AGL_FONT_GLYPH_d,
    AGL_FONT_GLYPH_e,
    AGL_FONT_GLYPH_f,
    AGL_FONT_GLYPH_g,
    AGL_FONT_GLYPH_h,
    AGL_FONT_GLYPH_i,
    AGL_FONT_GLYPH_j,
    AGL_FONT_GLYPH_k,
    AGL_FONT_GLYPH_l,
    AGL_FONT_GLYPH_m,
    AGL_FONT_GLYPH_n,
    AGL_FONT_GLYPH_o,
    AGL_FONT_GLYPH_p,
    AGL_FONT_GLYPH_q,
    AGL_FONT_GLYPH_r,
    AGL_FONT_GLYPH_s,
    AGL_FONT_GLYPH_t,
    AGL_FONT_GLYPH_u,
    AGL_FONT_GLYPH_v,
    AGL_FONT_GLYPH_w,
    AGL_FONT_GLYPH_x,
    AGL_FONT_GLYPH_y,
    AGL_FONT_GLYPH_z,
	AGL_FONT_GLYPH_UNDERSCORE,
    AGL_FONT_GLYPH_COLON,
    AGL_FONT_GLYPH_DOT,
    AGL_FONT_GLYPH_EQUAL,
    AGL_FONT_GLYPH_PLUS,
    AGL_FONT_GLYPH_MINUS,
    AGL_FONT_GLYPH_STAR,
    AGL_FONT_GLYPH_SLASH,
    AGL_FONT_GLYPH_PERCENT,

    AGL_FONT_GLYPH_COUNT,
} agl__fontglyph_t;

#define AGL_GFX_FLAG_TEXTURED 0x1
#define AGL_GFX_FLAG_FONTGLYPH 0x8

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                Win32 Platform Functions
///////////////////////////////////////////////////////////////////////////////////////////////////
#if _WIN32
struct Win32 {
    HMODULE kernel; // kernel32.dll
    HMODULE ntdll; // ntdll.dll
    HMODULE opengl; // opengl32.dll
    HMODULE user; // user32.dll
} static win32;

static void* agl__loadProc(const char *procname) {
#if _WIN32
    PROC proc = wglGetProcAddress(procname);
    if (!proc) {
        proc = GetProcAddress(win32.opengl, procname);
    }
#endif
    agl__gfx_assertf(proc, "Failed to load `%s`\n", procname);
    return (void*)proc;
}

static agl_gfx_key_t win32ConvertKey(WPARAM wparam, int extended) {
    switch (wparam) {
    case VK_SPACE : return AGL_GFX_KEY_SPACE;
    case VK_RETURN : return AGL_GFX_KEY_ENTER;
    case VK_ESCAPE : return AGL_GFX_KEY_ESCAPE;
    case VK_SHIFT : return extended ? AGL_GFX_KEY_RSHIFT : AGL_GFX_KEY_LSHIFT;
    case VK_CONTROL : return extended ? AGL_GFX_KEY_RCTRL : AGL_GFX_KEY_LCTRL;
    case VK_TAB : return AGL_GFX_KEY_TAB;
    case VK_LEFT : return AGL_GFX_KEY_LEFT;
    case VK_UP : return AGL_GFX_KEY_UP;
    case VK_RIGHT : return AGL_GFX_KEY_RIGHT;
    case VK_DOWN : return AGL_GFX_KEY_DOWN;
    case '0' : return AGL_GFX_KEY_0;
    case '1' : return AGL_GFX_KEY_1;
    case '2' : return AGL_GFX_KEY_2;
    case '3' : return AGL_GFX_KEY_3;
    case '4' : return AGL_GFX_KEY_4;
    case '5' : return AGL_GFX_KEY_5;
    case '6' : return AGL_GFX_KEY_6;
    case '7' : return AGL_GFX_KEY_7;
    case '8' : return AGL_GFX_KEY_8;
    case '9' : return AGL_GFX_KEY_9;
    case 'A' : return AGL_GFX_KEY_A;
    case 'B' : return AGL_GFX_KEY_B;
    case 'C' : return AGL_GFX_KEY_C;
    case 'D' : return AGL_GFX_KEY_D;
    case 'E' : return AGL_GFX_KEY_E;
    case 'F' : return AGL_GFX_KEY_F;
    case 'G' : return AGL_GFX_KEY_G;
    case 'H' : return AGL_GFX_KEY_H;
    case 'I' : return AGL_GFX_KEY_I;
    case 'J' : return AGL_GFX_KEY_J;
    case 'K' : return AGL_GFX_KEY_K;
    case 'L' : return AGL_GFX_KEY_L;
    case 'M' : return AGL_GFX_KEY_M;
    case 'N' : return AGL_GFX_KEY_N;
    case 'O' : return AGL_GFX_KEY_O;
    case 'P' : return AGL_GFX_KEY_P;
    case 'Q' : return AGL_GFX_KEY_Q;
    case 'R' : return AGL_GFX_KEY_R;
    case 'S' : return AGL_GFX_KEY_S;
    case 'T' : return AGL_GFX_KEY_T;
    case 'U' : return AGL_GFX_KEY_U;
    case 'V' : return AGL_GFX_KEY_V;
    case 'W' : return AGL_GFX_KEY_W;
    case 'X' : return AGL_GFX_KEY_X;
    case 'Y' : return AGL_GFX_KEY_Y;
    case 'Z' : return AGL_GFX_KEY_Z;
    case VK_NUMPAD0 : return AGL_GFX_KEY_NUMPAD0;
    case VK_NUMPAD1 : return AGL_GFX_KEY_NUMPAD1;
    case VK_NUMPAD2 : return AGL_GFX_KEY_NUMPAD2;
    case VK_NUMPAD3 : return AGL_GFX_KEY_NUMPAD3;
    case VK_NUMPAD4 : return AGL_GFX_KEY_NUMPAD4;
    case VK_NUMPAD5 : return AGL_GFX_KEY_NUMPAD5;
    case VK_NUMPAD6 : return AGL_GFX_KEY_NUMPAD6;
    case VK_NUMPAD7 : return AGL_GFX_KEY_NUMPAD7;
    case VK_NUMPAD8 : return AGL_GFX_KEY_NUMPAD8;
    case VK_NUMPAD9 : return AGL_GFX_KEY_NUMPAD9;
    default: ;
    }
    return AGL_GFX_KEY_NONE;
}

static LRESULT CALLBACK win32WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    agl__gfx_context_t *context;
    if (msg == WM_CREATE) {
        CREATESTRUCTA *cs = (CREATESTRUCTA*)lparam;
        context = (agl__gfx_context_t*)cs->lpCreateParams;
        if (context) {
            SetWindowLongPtrA(hwnd, GWLP_USERDATA, (LONG_PTR)context);
        }
    } else if (msg == WM_CLOSE) {
        context = (agl__gfx_context_t*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);
        if (context) {
            context->wantsQuit = true;
        }
            DestroyWindow(hwnd);
        return 0;
    } else if (msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    } else {
        context = (agl__gfx_context_t*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);
    }

    int sys = 0;
    int down = 0;
    switch (msg) {
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN: down = 1; // fallthrough
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MOUSEMOVE: {
        int btnmask = 0;
        btnmask |= (wparam & MK_LBUTTON) ? AGL_GFX_MOUSE_BUTTON_LEFT : 0;
        btnmask |= (wparam & MK_RBUTTON) ? AGL_GFX_MOUSE_BUTTON_RIGHT : 0;
        btnmask |= (wparam & MK_MBUTTON) ? AGL_GFX_MOUSE_BUTTON_MIDDLE : 0;
        int mods = 0;
        mods |= (wparam & MK_SHIFT) ? AGL_GFX_MOD_SHIFT : 0;
        mods |= (wparam & MK_CONTROL) ? AGL_GFX_MOD_CONTROL : 0;
        int mxi = GET_X_LPARAM(lparam);
        int myi = GET_Y_LPARAM(lparam);
        agl_float mx = (agl_float)mxi / (agl_float)context->canvas->width;
        agl_float my = (agl_float)myi / (agl_float)context->canvas->height;
        mx = mx * 2.f - 1.f;
        my = (1.f - my) * 2.f - 1.f;
        mx *= (agl_float)context->canvas->width / (agl_float)context->canvas->height;
        if (msg == WM_MOUSEMOVE) {
            if (context->movefn)
                context->movefn(btnmask, mx, my, mods);
        } else {
            if (context->mousefn)
                context->mousefn(btnmask, mx, my, down, mods);
        }
        break;
    }
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP: sys = 1; // fallthrough
    case WM_KEYDOWN:
    case WM_KEYUP: {
        int prevState = ((lparam >> 30) & 0x1);
        int currState = 1 - ((lparam >> 31) & 0x1); // 1: down, 0: up
        int scancode = ((lparam >> 16) & 0xFF);
        int repeatCount = lparam & 0xFFFF;
        int extended = ((lparam >> 24) & 0x1);
        if (context->keyfn)
            context->keyfn(win32ConvertKey(wparam, extended), currState, prevState ? repeatCount : 0, scancode);
        break;
    }
    default: ;
    }
    return DefWindowProcA(hwnd, msg, wparam, lparam);
}

static int win32CreateContext(agl__gfx_context_t *context, const agl_gfx_create_params_t *params) {
    // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    win32.kernel = LoadLibraryA("kernel32.dll");
    win32.ntdll = LoadLibraryA("ntdll.dll");
    win32.opengl = LoadLibraryA("opengl32.dll");
    win32.user = LoadLibraryA("user32.dll");

    HINSTANCE hInstance = (HINSTANCE)GetModuleHandleA(NULL);
    GetModuleHandleEx(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
        GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        (LPVOID)&agl_gfx_create_context,
        &hInstance
    );
    agl__gfx_assertf(hInstance, "Failed to get HINSTANCE");

    HICON hIcon = LoadIconA(NULL, IDI_APPLICATION);
    HCURSOR hCursor = LoadCursorA(NULL, IDC_ARROW);
    HICON hIconSmall = LoadImage(
                        hInstance,
                        MAKEINTRESOURCE(5),
                        IMAGE_ICON,
                        GetSystemMetrics(SM_CXSMICON),
                        GetSystemMetrics(SM_CYSMICON),
                        LR_DEFAULTCOLOR);

    WNDCLASSEX wcx = {};
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW | CS_PARENTDC;
    wcx.lpfnWndProc = &win32WindowProc;
    wcx.cbClsExtra = 0;
    wcx.cbWndExtra = 0;
    wcx.hInstance = hInstance;
    wcx.hIcon = hIcon;
    wcx.hCursor = hCursor;
    wcx.lpszMenuName = "GluaMainMenu";
    wcx.lpszClassName = "GluaWindow";
    wcx.hIconSm = hIconSmall;

    if (!RegisterClassExA(&wcx)) {
        agl__gfx_assertf(false, "Failed to register Win32 window class");
    }

    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
    // Fake OpenGL initialization for retrieving wgl context params
    {
        HWND hwnd = CreateWindowExA(
            WS_EX_OVERLAPPEDWINDOW | WS_EX_ACCEPTFILES,
            "GluaWindow",
            params->appname,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            NULL,
            NULL,
            hInstance,
            context
        );
        if (hwnd == NULL) {
            agl__gfx_assertf(hwnd != NULL, "Failed to create Win32 window");
            free(context);
            return 1;
        }

        HDC fakeDC = GetDC(hwnd);
        agl__gfx_assertf(fakeDC, "Failed to get DC");

        PIXELFORMATDESCRIPTOR pfd = {};
        pfd.nSize = sizeof(pfd);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cAlphaBits = 8;
        pfd.cDepthBits = 24;
        int pixelFormat = ChoosePixelFormat(fakeDC, &pfd);
        agl__gfx_assertf(pixelFormat, "Failed to choose pixel format (gdi)");

        if (!SetPixelFormat(fakeDC, pixelFormat, &pfd)) {
            agl__gfx_assertf(false, "Failed to set pixel format (gdi)");
        }

        HGLRC fakeRC = wglCreateContext(fakeDC);
        agl__gfx_assertf(fakeRC, "Failed to create render context");
        if (!wglMakeCurrent(fakeDC, fakeRC)) {
            agl__gfx_assertf(false, "Failed to make current");
        }

        wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)agl__loadProc("wglChoosePixelFormatARB");
        wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)agl__loadProc("wglCreateContextAttribsARB");

        agl__gfx_assertf(wglChoosePixelFormatARB && wglCreateContextAttribsARB, "Failed to load WGL functions");

        wglMakeCurrent(fakeDC, 0);
        wglDeleteContext(fakeRC);
        ReleaseDC(hwnd, fakeDC);
        DestroyWindow(hwnd);
    }

    // Actual OpenGL intiialization
    {
        RECT borderRect = {};
        AdjustWindowRectEx(
            &borderRect,
            WS_OVERLAPPEDWINDOW,
            0, 
            WS_EX_OVERLAPPEDWINDOW | WS_EX_ACCEPTFILES
        );

        int width = ((int)params->width) + borderRect.right - borderRect.left;
        int height = ((int)params->height) + borderRect.bottom - borderRect.top;

        HWND hwnd = CreateWindowExA(
            WS_EX_OVERLAPPEDWINDOW | WS_EX_ACCEPTFILES,
            "GluaWindow",
            params->appname,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            width, height,
            NULL,
            NULL,
            hInstance,
            context
        );
        if (hwnd == NULL) {
            agl__gfx_assertf(hwnd != NULL, "Failed to create Win32 window");
            free(context);
            return 1;
        }

        HDC dc = GetDC(hwnd);
        agl__gfx_assertf(dc, "Failed to get DC");

        const int pixelAttribs[] = {
            WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
            WGL_SWAP_METHOD_ARB,        WGL_SWAP_COPY_ARB,
            WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
            WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
            WGL_COLOR_BITS_ARB,         32,
            WGL_RED_BITS_ARB,           8,
            WGL_GREEN_BITS_ARB,         8,
            WGL_BLUE_BITS_ARB,          8,
            WGL_ALPHA_BITS_ARB,         8,
            WGL_DEPTH_BITS_ARB,         24,
            WGL_STENCIL_BITS_ARB,       8,
            WGL_SAMPLE_BUFFERS_ARB,     GL_TRUE,
            WGL_SAMPLES_ARB,            16,
            0,                          0
        };
        UINT nPixelFormats;
        int pixelFormat = 0;
        if (!wglChoosePixelFormatARB(dc, pixelAttribs, NULL, 1, &pixelFormat, &nPixelFormats)) {
            agl__gfx_assertf(false, "Failed to choose pixel format");
        }

        PIXELFORMATDESCRIPTOR pfd = {};
        DescribePixelFormat(dc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

        if (!SetPixelFormat(dc, pixelFormat, &pfd)) {
            agl__gfx_assertf(false, "Failed to set pixel format");
        }

        const int contextAttribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB,  4,
            WGL_CONTEXT_MINOR_VERSION_ARB,  5,
            WGL_CONTEXT_PROFILE_MASK_ARB,   WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            WGL_CONTEXT_FLAGS_ARB,          WGL_CONTEXT_DEBUG_BIT_ARB,
            0,
        };

        HGLRC rc = wglCreateContextAttribsARB(dc, 0, contextAttribs);
        agl__gfx_assertf(rc, "Failed to create OpenGL render context");

        if (!wglMakeCurrent(dc, rc)) {
            agl__gfx_assertf(false, "Failed to make current");
        }

        context->hinstance = hInstance;
        context->hwnd = hwnd;
    }
    ShowWindow(context->hwnd, SW_SHOW);
    return 0;
}
#endif // _WIN32


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                OpenGL Functions
///////////////////////////////////////////////////////////////////////////////////////////////////
static PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallbackProc;
static PFNGLCREATESHADERPROC glCreateShaderProc;
static PFNGLSHADERSOURCEPROC glShaderSourceProc;
static PFNGLCOMPILESHADERPROC glCompileShaderProc;
static PFNGLDELETESHADERPROC glDeleteShaderProc;
static PFNGLCREATEPROGRAMPROC glCreateProgramProc;
static PFNGLDELETEPROGRAMPROC glDeleteProgramProc;
static PFNGLATTACHSHADERPROC glAttachShaderProc;
static PFNGLDETACHSHADERPROC glDetachShaderProc;
static PFNGLLINKPROGRAMPROC glLinkProgramProc;
static PFNGLUSEPROGRAMPROC glUseProgramProc;
static PFNGLGETSHADERIVPROC glGetShaderivProc;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLogProc;
static PFNGLCREATEVERTEXARRAYSPROC glCreateVertexArraysProc;
static PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArraysProc;
static PFNGLBINDVERTEXARRAYPROC glBindVertexArrayProc;
static PFNGLCREATEBUFFERSPROC glCreateBuffersProc;
static PFNGLDELETEBUFFERSPROC glDeleteBuffersProc;
static PFNGLNAMEDBUFFERSTORAGEPROC glNamedBufferStorageProc;
static PFNGLNAMEDBUFFERSUBDATAPROC glNamedBufferSubDataProc;
static PFNGLBINDBUFFERPROC glBindBufferProc;
static PFNGLBINDBUFFERBASEPROC glBindBufferBaseProc;
static PFNGLPROGRAMUNIFORM2FPROC glProgramUniform2fProc;
static PFNGLPROGRAMUNIFORM4FVPROC glProgramUniform4fvProc;
static PFNGLPROGRAMUNIFORM4UIVPROC glProgramUniform4uivProc;
static PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fvProc;
static PFNGLCREATETEXTURESPROC glCreateTexturesProc;
static PFNGLTEXTURESTORAGE2DPROC glTextureStorage2DProc;
static PFNGLTEXTURESUBIMAGE2DPROC glTextureSubImage2DProc;
static PFNGLTEXTUREPARAMETERIPROC glTextureParameteriProc;
static PFNGLGETTEXTUREHANDLEARBPROC glGetTextureHandleARBProc;
static PFNGLMAKETEXTUREHANDLERESIDENTARBPROC glMakeTextureHandleResidentARBProc;
static PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC glMakeTextureHandleNonResidentARBProc;
static PFNGLBINDTEXTUREUNITPROC glBindTextureUnitProc;
static PFNGLOBJECTLABELPROC glObjectLabelProc;

GLAPI void APIENTRY glDebugMessageCallback(GLDEBUGPROC callback, const void *userParam) {
    return glDebugMessageCallbackProc(callback, userParam);
}

GLAPI GLuint APIENTRY glCreateShader(GLenum type) {
    return glCreateShaderProc(type);
}

GLAPI void APIENTRY glShaderSource(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length) {
    return glShaderSourceProc(shader, count, string, length);
}

GLAPI void APIENTRY glCompileShader(GLuint shader) {
    return glCompileShaderProc(shader);
}

GLAPI void APIENTRY glDeleteShader(GLuint shader) {
    return glDeleteShaderProc(shader);
}

GLAPI GLuint APIENTRY glCreateProgram(void) {
    return glCreateProgramProc();
}

GLAPI void APIENTRY glDeleteProgram(GLuint program) {
    return glDeleteProgramProc(program);
}

GLAPI void APIENTRY glAttachShader(GLuint program, GLuint shader) {
    return glAttachShaderProc(program, shader);
}

GLAPI void APIENTRY glDetachShader(GLuint program, GLuint shader) {
    return glDetachShaderProc(program, shader);
}

GLAPI void APIENTRY glLinkProgram(GLuint program) {
    return glLinkProgramProc(program);
}

GLAPI void APIENTRY glUseProgram(GLuint program) {
    return glUseProgramProc(program);
}

GLAPI void APIENTRY glGetShaderiv(GLuint shader, GLenum pname, GLint *params) {
    return glGetShaderivProc(shader, pname, params);
}

GLAPI void APIENTRY glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {
    return glGetShaderInfoLogProc(shader, bufSize, length, infoLog);
}

GLAPI void APIENTRY glCreateVertexArrays(GLsizei n, GLuint *arrays) {
    return glCreateVertexArraysProc(n, arrays);
}

GLAPI void APIENTRY glDeleteVertexArrays(GLsizei n, const GLuint *arrays) {
    return glDeleteVertexArraysProc(n, arrays);
}

GLAPI void APIENTRY glBindVertexArray(GLuint array) {
    return glBindVertexArrayProc(array);
}

GLAPI void APIENTRY glCreateBuffers(GLsizei n, GLuint *buffers) {
    return glCreateBuffersProc(n, buffers);
}

GLAPI void APIENTRY glDeleteBuffers(GLsizei n, const GLuint *buffers) {
    return glDeleteBuffersProc(n, buffers);
}

GLAPI void APIENTRY glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags) {
    return glNamedBufferStorageProc(buffer, size, data, flags);
}

GLAPI void APIENTRY glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data) {
    return glNamedBufferSubDataProc(buffer, offset, size, data);
}

GLAPI void APIENTRY glBindBuffer(GLenum target, GLuint buffer) {
    return glBindBufferProc(target, buffer);
}

GLAPI void APIENTRY glBindBufferBase(GLenum target, GLuint index, GLuint buffer) {
    return glBindBufferBaseProc(target, index, buffer);
}

GLAPI void APIENTRY glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1) {
    return glProgramUniform2fProc(program, location, v0, v1);
}

GLAPI void APIENTRY glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat *value) {
    return glProgramUniform4fvProc(program, location, count, value);
}

GLAPI void APIENTRY glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint *value) {
    return glProgramUniform4uivProc(program, location, count, value);
}

GLAPI void APIENTRY glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    return glProgramUniformMatrix4fvProc(program, location, count, transpose, value);
}

GLAPI void APIENTRY glCreateTextures(GLenum target, GLsizei n, GLuint *textures) {
    return glCreateTexturesProc(target, n, textures);
}

GLAPI void APIENTRY glTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) {
    return glTextureStorage2DProc(texture, levels, internalformat, width, height);
}

GLAPI void APIENTRY glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels) {
    return glTextureSubImage2DProc(texture, level, xoffset, yoffset, width, height, format, type, pixels);
}

GLAPI void APIENTRY glTextureParameteri(GLuint texture, GLenum pname, GLint param) {
    return glTextureParameteriProc(texture, pname, param);
}

GLAPI GLuint64 APIENTRY glGetTextureHandleARB(GLuint texture) {
    return glGetTextureHandleARBProc(texture);
}

GLAPI void APIENTRY glMakeTextureHandleResidentARB(GLuint64 handle) {
    return glMakeTextureHandleResidentARBProc(handle);
}

GLAPI void APIENTRY glMakeTextureHandleNonResidentARB(GLuint64 handle) {
    return glMakeTextureHandleNonResidentARBProc(handle);
}

GLAPI void APIENTRY glBindTextureUnit(GLuint unit, GLuint texture) {
    return glBindTextureUnitProc(unit, texture);
}

GLAPI void APIENTRY glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar *label) {
    return glObjectLabelProc(identifier, name, length, label);
}

#define AGL_LOAD_PROC(proctype, procname) \
    procname##Proc = (proctype)agl__loadProc(#procname)

int agl__loadGLFunctions() {
    AGL_LOAD_PROC(PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallback);
    AGL_LOAD_PROC(PFNGLCREATESHADERPROC, glCreateShader);
    AGL_LOAD_PROC(PFNGLSHADERSOURCEPROC, glShaderSource);
    AGL_LOAD_PROC(PFNGLCOMPILESHADERPROC, glCompileShader);
    AGL_LOAD_PROC(PFNGLDELETESHADERPROC, glDeleteShader);
    AGL_LOAD_PROC(PFNGLCREATEPROGRAMPROC, glCreateProgram);
    AGL_LOAD_PROC(PFNGLDELETEPROGRAMPROC, glDeleteProgram);
    AGL_LOAD_PROC(PFNGLATTACHSHADERPROC, glAttachShader);
    AGL_LOAD_PROC(PFNGLDETACHSHADERPROC, glDetachShader);
    AGL_LOAD_PROC(PFNGLLINKPROGRAMPROC, glLinkProgram);
    AGL_LOAD_PROC(PFNGLUSEPROGRAMPROC, glUseProgram);
    AGL_LOAD_PROC(PFNGLGETSHADERIVPROC, glGetShaderiv);
    AGL_LOAD_PROC(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog);
    AGL_LOAD_PROC(PFNGLCREATEVERTEXARRAYSPROC, glCreateVertexArrays);
    AGL_LOAD_PROC(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays);
    AGL_LOAD_PROC(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray);
    AGL_LOAD_PROC(PFNGLCREATEBUFFERSPROC, glCreateBuffers);
    AGL_LOAD_PROC(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
    AGL_LOAD_PROC(PFNGLNAMEDBUFFERSTORAGEPROC, glNamedBufferStorage);
    AGL_LOAD_PROC(PFNGLNAMEDBUFFERSUBDATAPROC, glNamedBufferSubData);
    AGL_LOAD_PROC(PFNGLBINDBUFFERPROC, glBindBuffer);
    AGL_LOAD_PROC(PFNGLBINDBUFFERBASEPROC, glBindBufferBase);
    AGL_LOAD_PROC(PFNGLPROGRAMUNIFORM2FPROC, glProgramUniform2f);
    AGL_LOAD_PROC(PFNGLPROGRAMUNIFORM4FVPROC, glProgramUniform4fv);
    AGL_LOAD_PROC(PFNGLPROGRAMUNIFORM4UIVPROC, glProgramUniform4uiv);
    AGL_LOAD_PROC(PFNGLPROGRAMUNIFORMMATRIX4FVPROC, glProgramUniformMatrix4fv);
    AGL_LOAD_PROC(PFNGLCREATETEXTURESPROC, glCreateTextures);
    AGL_LOAD_PROC(PFNGLTEXTURESTORAGE2DPROC, glTextureStorage2D);
    AGL_LOAD_PROC(PFNGLTEXTURESUBIMAGE2DPROC, glTextureSubImage2D);
    AGL_LOAD_PROC(PFNGLTEXTUREPARAMETERIPROC, glTextureParameteri);
    AGL_LOAD_PROC(PFNGLGETTEXTUREHANDLEARBPROC, glGetTextureHandleARB);
    AGL_LOAD_PROC(PFNGLMAKETEXTUREHANDLERESIDENTARBPROC, glMakeTextureHandleResidentARB);
    AGL_LOAD_PROC(PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC, glMakeTextureHandleNonResidentARB);
    AGL_LOAD_PROC(PFNGLBINDTEXTUREUNITPROC, glBindTextureUnit);
    AGL_LOAD_PROC(PFNGLOBJECTLABELPROC, glObjectLabel);
    return AGL_GFX_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                AGL GFX API
///////////////////////////////////////////////////////////////////////////////////////////////////
static void APIENTRY agl__GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                    GLsizei length, const GLchar *message, const void *udata) {
    const char *typestr;
    switch (type) {
    case GL_DEBUG_TYPE_ERROR: typestr = "ERROR";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typestr = "DEPRECATED_BEHAVIOR";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: typestr = "UNDEFINED_BEHAVIOR";
    case GL_DEBUG_TYPE_PORTABILITY: typestr = "PORTABILITY";
    case GL_DEBUG_TYPE_PERFORMANCE: typestr = "PERFORMANCE";
    case GL_DEBUG_TYPE_OTHER: typestr = "OTHER";
    case GL_DEBUG_TYPE_MARKER: typestr = "MARKER";
    case GL_DEBUG_TYPE_PUSH_GROUP: typestr = "PUSH_GROUP";
    case GL_DEBUG_TYPE_POP_GROUP: typestr = "POP_GROUP";
    default: ;
    }
    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
        agl__gfx_assertf(false, "[%s] GL-%u: %s", typestr, id, message);
    } else {
        // agl__gfx_tracef("GL-%u: %s\n", id, message);
    }
}

static GLuint agl__CreateShader(GLenum type, const char *source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);
    int success;
    char shaderLog[2048];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 2048, 0, shaderLog);
        agl__gfx_assertf(success, "Failed to compile shader: %s", shaderLog);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

static const char *quad_shader_source_vert = "#version 450 core""\n"
    "#define AGL_GFX_FLAG_TEXTURED 0x1""\n"
    "#define AGL_GFX_FLAG_FONTGLYPH 0x8""\n"
    "layout (location = 0) out VS_OUT {"
        "flat uvec2 tex;"
        "flat uint flags;"
        "vec4 color;"
        "vec4 uv;"
    "} vs_out;"
    "struct Quad {"
        "vec2 pos;"
        "vec2 size;"
        "float angle;"
        "uint glyph;"
        "uint color;"
        "uvec2 texture;"
        "uint flags;"
    "};"
    "layout (location = 0) uniform vec2 screen;"
    "layout (location = 1) uniform uvec4 fontInfo;"
    "layout (binding = 1, std430) readonly buffer Quads { Quad quads[]; };"
    "vec4 UnpackColor(uint color) {"
        "float r = (float(color & 0xFF)) / 255.0;"
        "float g = (float((color >> 8) & 0xFF)) / 255.0;"
        "float b = (float((color >> 16) & 0xFF)) / 255.0;"
        "float a = (float((color >> 24) & 0xFF)) / 255.0;"
        "return vec4(r,g,b,a);"
    "}"
    "void main() {"
        "vec2 vertices[6] = {"
            "vec2(-0.5,  0.5),"
            "vec2(-0.5, -0.5),"
            "vec2( 0.5,  0.5),"
            "vec2( 0.5,  0.5),"
            "vec2(-0.5, -0.5),"
            "vec2( 0.5, -0.5),"
        "};"
        "vec2 uvs[6] = {"
            "vec2(0, 0),"
            "vec2(0, 1),"
            "vec2(1, 0),"
            "vec2(1, 0),"
            "vec2(0, 1),"
            "vec2(1, 1),"
        "};"
        "uint vertIdx = gl_VertexID % 6;"
        "uint quadIdx = gl_VertexID / 6;"
        "Quad quad = quads[quadIdx];"
        "float s = sin(quad.angle);"
        "float c = cos(quad.angle);"
        "float aspect = screen.y / screen.x;"
        "vec2 scl = quad.size;"
        "mat2 rot = mat2(vec2(c, -s), vec2(s, c));"
        "vec2 position = ((vertices[vertIdx] * scl) * rot + quad.pos) * vec2(aspect, 1.0);"
        "gl_Position = vec4(position, 0.0, 1.0);"
        "vs_out.flags = quad.flags;"
        "if ((quad.flags & AGL_GFX_FLAG_TEXTURED) != 0) {"
            "vs_out.tex = quad.texture;"
            "vec2 uv = uvs[vertIdx];"
            "if ((quad.flags & AGL_GFX_FLAG_FONTGLYPH) != 0) {"
                "uint W = fontInfo.x;"
                "uint H = fontInfo.y;"
                "uint C = fontInfo.z;"
                "uint R = fontInfo.w;"
                "uint r = quad.glyph / C;"
                "uint c = quad.glyph \% C;"
                "uv = (uv + vec2(c, r)) * vec2(1.0/C, 1.0/R);"
                "uv -= 0.5 * vec2(1.0/C/W, 1.0/R/H);"
            "}"
            "vs_out.uv = vec4(uv, 0, 0);"
        "}"
        "vs_out.color = UnpackColor(quad.color);"
    "}";

static const char *quad_shader_source_frag =  "#version 450 core""\n"
    "#define AGL_GFX_FLAG_TEXTURED 0x1""\n"
    "#extension GL_ARB_bindless_texture : enable""\n"
    "layout (location = 0) in VS_OUT {"
        "flat uvec2 tex;"
        "flat uint flags;"
        "vec4 color;"
        "vec4 uv;"
    "} fs_in;"
    "layout (location = 0) out vec4 FragColor;"
    "void main() {"
        "if ((fs_in.flags & AGL_GFX_FLAG_TEXTURED) != 0) {"
            "FragColor = texture(sampler2D(fs_in.tex), fs_in.uv.xy);"
        "} else {"
            "FragColor = vec4(1.0);"
        "}"
        "FragColor *= fs_in.color;"
    "}";

static const char *mesh_shader_source_vert = "#version 450 core""\n"
    "layout (location = 0) out VS_OUT {"
        "vec4 color;"
    "} vs_out;"
    // "layout (location = 0) uniform vec2 Screen;"
    "layout (location = 1) uniform mat4 CameraView;"
    "layout (location = 2) uniform mat4 CameraProj;"
    "layout (location = 3) uniform mat4 Transform;"
    "layout (binding = 2, std430) readonly buffer VertexData {"
        "uint PositionStart;"
        "uint UVStart;"
        "uint NormalStart;"
        "uint ColorStart;"
        "float vs_data[];"
    "};"
    "vec3 ExtractPosition(uint index) {"
        "uint i = PositionStart + 3 * index;"
        "return vec3(vs_data[i], vs_data[i+1], vs_data[i+2]);"
    "}"
    "vec2 ExtractUV(uint index) {"
        "if (UVStart == -1)"
            "return vec2(0);"
        "uint i = UVStart + 2 * index;"
        "return vec2(vs_data[i], vs_data[i+1]);"
    "}"
    "vec3 ExtractNormal(uint index) {"
        "if (NormalStart == -1)"
            "return vec3(0);"
        "uint i = NormalStart + 3 * index;"
        "return vec3(vs_data[i], vs_data[i+1], vs_data[i+2]);"
    "}"
    "vec4 ExtractColor(uint index) {"
        "if (ColorStart == -1)"
            "return vec4(0);"
        "uint i = ColorStart + 4 * index;"
        "return vec4(vs_data[i], vs_data[i+1], vs_data[i+2], vs_data[i+3]);"
    "}"
    "void main() {"
        "gl_Position = CameraProj * CameraView * Transform * vec4(ExtractPosition(gl_VertexID), 1.0);"
        "vs_out.color = ExtractColor(gl_VertexID);"
    "}";

static const char *mesh_shader_source_frag = "#version 450 core""\n"
    "#extension GL_ARB_bindless_texture : enable""\n"
    "layout (location = 0) in VS_OUT {"
        "vec4 color;"
    "} fs_in;"
    "layout (location = 4) uniform vec4 TintColor;"
    "layout (location = 0) out vec4 FragColor;"
    "void main() {"
        "FragColor = TintColor * vec4(fs_in.color);"
    "}";

static GLuint agl__CreateShaderProgram(const char *vertSource, const char *fragSource) {
    GLuint vert = agl__CreateShader(GL_VERTEX_SHADER, vertSource);
    GLuint frag = agl__CreateShader(GL_FRAGMENT_SHADER, fragSource);
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    glDetachShader(prog, vert);
    glDetachShader(prog, frag);
    glDeleteShader(vert);
    glDeleteShader(frag);
    return prog;
}

void agl__CreateFontImage(agl_gfx_context_t context);

static void agl__CreateGraphicsResources(agl__gfx_context_t *context) {
    GLuint quadProg = agl__CreateShaderProgram(quad_shader_source_vert, quad_shader_source_frag);
    GLuint meshProg = agl__CreateShaderProgram(mesh_shader_source_vert, mesh_shader_source_frag);

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint quadBuf;
    glCreateBuffers(1, &quadBuf);
    glNamedBufferStorage(quadBuf, sizeof(agl__gfx_quad_t) * context->canvas->quadsTotal, NULL, GL_DYNAMIC_STORAGE_BIT);

    agl__CreateFontImage(context);

    context->canvas->quadProg = quadProg;
    context->canvas->quadVao = vao;
    context->canvas->quadBuf = quadBuf;
    context->canvas->meshProg = meshProg;
    context->canvas->meshVao = vao;
    context->canvas->activeVao = vao;
    context->canvas->activeMesh = AGL_GFX_INVALID_ID;
    context->canvas->activeProg = 0;
}

static void agl__DestroyGraphicsResources(agl__gfx_context_t *context) {
    agl_gfx_destroy_image(context, context->canvas->fontImage);
    glDeleteProgram(context->canvas->quadProg);
    glDeleteBuffers(1, &context->canvas->quadBuf);
    glDeleteVertexArrays(1, &context->canvas->quadVao);
}

agl_gfx_context_t agl_gfx_create_context(const agl_gfx_create_params_t *params) {
    agl__gfx_context_t *context = (agl__gfx_context_t*)calloc(1, sizeof(agl__gfx_context_t) + sizeof(agl__gfx_canvas_t));
    context->canvas = (agl__gfx_canvas_t*)(context+1);
    context->canvas->context = context;
    context->canvas->width = params->width;
    context->canvas->height = params->height;
    context->wantsQuit = false;
    context->running = false;
    #if _WIN32
    if (win32CreateContext(context, params)) {
        free(context);
        return NULL;
    }
    #endif // _WIN32
    // initialize temp allocator
    context->scratchAllocator.beg = params->scratchMemory.allocationBase;
    context->scratchAllocator.end = context->scratchAllocator.beg + params->scratchMemory.allocationSize;
    context->scratchAllocator.cur = context->scratchAllocator.end;

    agl_uint imagePoolSize = params->imagePoolSize == 0 ? 1024 : params->imagePoolSize;
    agl_uint meshPoolSize = params->meshPoolSize == 0 ? 256 : params->meshPoolSize;
    agl_uint bufferPoolSize = params->bufferPoolSize + meshPoolSize; // mesh pool buffers are allocated from the buffer pool, so we need to add the mesh pool size to the buffer pool size to get the total number of buffers needed
    agl__ImagePoolInit(&context->imagePool, imagePoolSize);
    agl__BufferPoolInit(&context->bufferPool, bufferPoolSize);
    agl__MeshPoolInit(&context->meshPool, meshPoolSize);

    agl_uint quadPoolSize = params->quadPoolSize == 0 ? 2048 : params->quadPoolSize;
    agl__gfx_canvas_t *canvas = context->canvas;
    canvas->quads = (agl__gfx_quad_t*)malloc(quadPoolSize * sizeof(agl__gfx_quad_t));
    canvas->quadsTotal = quadPoolSize;
    canvas->quadsUsed = 0;

    agl__loadGLFunctions();
    
#if _DEBUG
    glDebugMessageCallback(&agl__GLDebugMessageCallback, NULL);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glEnable(GL_DEBUG_OUTPUT);
#endif
    
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    agl__CreateGraphicsResources(context);

    return context;
}

void agl_gfx_destroy_context(agl_gfx_context_t context) {
    if (context->deletefn) context->deletefn(context->udata);
    agl__DestroyGraphicsResources(context);
    agl__MeshPoolShutdown(&context->meshPool);
    agl__ImagePoolShutdown(&context->imagePool);
    agl__BufferPoolShutdown(&context->bufferPool);
    free(context->canvas->quads);
    free(context);
}

agl_gfx_update_func agl_gfx_set_update_func(agl_gfx_context_t context, agl_gfx_update_func updatefn) {
    agl_gfx_update_func old = context->updatefn;
    context->updatefn = updatefn;
    return old;
}

agl_gfx_key_func agl_gfx_set_key_func(agl_gfx_context_t context, agl_gfx_key_func keyfn) {
    agl_gfx_key_func old = context->keyfn;
    context->keyfn = keyfn;
    return old;
}

agl_gfx_mouse_button_func agl_gfx_set_mouse_button_func(agl_gfx_context_t context, agl_gfx_mouse_button_func mousefn) {
    agl_gfx_mouse_button_func old = context->mousefn;
    context->mousefn = mousefn;
    return old;
}

agl_gfx_mouse_move_func agl_gfx_set_mouse_move_func(agl_gfx_context_t context, agl_gfx_mouse_move_func movefn) {
    agl_gfx_mouse_move_func old = context->movefn;
    context->movefn = movefn;
    return old;
}

agl_gfx_scroll_func agl_gfx_set_scroll_func(agl_gfx_context_t context, agl_gfx_scroll_func scrollfn) {
    agl_gfx_scroll_func old = context->scrollfn;
    context->scrollfn = scrollfn;
    return old;
}

agl_gfx_user_pointer_delete_func agl_gfx_set_user_pointer_delete_func(agl_gfx_context_t context, agl_gfx_user_pointer_delete_func deletefn) {
    agl_gfx_user_pointer_delete_func old = context->deletefn;
    context->deletefn = deletefn;
    return old;
}

agl_gfx_canvas_t agl_gfx_get_default_canvas(agl_gfx_context_t context) {
    return context->canvas;
}

void agl_gfx_get_canvas_size(agl_gfx_canvas_t canvas, agl_uint *width, agl_uint *height) {
    *width = canvas->width;
    *height = canvas->height;
}

void agl_gfx_set_user_pointer(agl_gfx_context_t context, void *udata) {
    context->udata = udata;
}

void* agl_gfx_get_user_pointer(agl_gfx_context_t context) {
    return context->udata;
}

static GLenum agl__GetImageInternalFormat(agl_gfx_image_format_t format) {
    switch (format) {
    case AGL_GFX_IMAGE_FORMAT_R8_UNORM:        return GL_R8;
    case AGL_GFX_IMAGE_FORMAT_R8G8_UNORM:      return GL_RG8;
    case AGL_GFX_IMAGE_FORMAT_R8G8B8_UNORM:    return GL_RGB8;
    case AGL_GFX_IMAGE_FORMAT_R8G8B8A8_UNORM:  return GL_RGBA8;
    case AGL_GFX_IMAGE_FORMAT_R8_SNORM:        return GL_R8_SNORM;
    case AGL_GFX_IMAGE_FORMAT_R8G8_SNORM:      return GL_RG8_SNORM;
    case AGL_GFX_IMAGE_FORMAT_R8G8B8_SNORM:    return GL_RGB8_SNORM;
    case AGL_GFX_IMAGE_FORMAT_R8G8B8A8_SNORM:  return GL_RGBA8_SNORM;
    case AGL_GFX_IMAGE_FORMAT_R16F:            return GL_R16F;
    case AGL_GFX_IMAGE_FORMAT_R16G16F:         return GL_RG16F;
    case AGL_GFX_IMAGE_FORMAT_R16G16B16F:      return GL_RGB16F;
    case AGL_GFX_IMAGE_FORMAT_R16G16B16A16F:   return GL_RGBA16F;
    default: ;
    }
    return GL_NONE;
}

static GLenum agl__GetImageFormat(agl_gfx_image_format_t format) {
    switch (format) {
    case AGL_GFX_IMAGE_FORMAT_R8_UNORM:        return GL_RED;
    case AGL_GFX_IMAGE_FORMAT_R8G8_UNORM:      return GL_RG;
    case AGL_GFX_IMAGE_FORMAT_R8G8B8_UNORM:    return GL_RGB;
    case AGL_GFX_IMAGE_FORMAT_R8G8B8A8_UNORM:  return GL_RGBA;
    case AGL_GFX_IMAGE_FORMAT_R8_SNORM:        return GL_RED;
    case AGL_GFX_IMAGE_FORMAT_R8G8_SNORM:      return GL_RG;
    case AGL_GFX_IMAGE_FORMAT_R8G8B8_SNORM:    return GL_RGB;
    case AGL_GFX_IMAGE_FORMAT_R8G8B8A8_SNORM:  return GL_RGBA;
    case AGL_GFX_IMAGE_FORMAT_R16F:            return GL_RED;
    case AGL_GFX_IMAGE_FORMAT_R16G16F:         return GL_RG;
    case AGL_GFX_IMAGE_FORMAT_R16G16B16F:      return GL_RGB;
    case AGL_GFX_IMAGE_FORMAT_R16G16B16A16F:   return GL_RGBA;
    default: ;
    }
    return GL_NONE;
}

static GLenum agl__GetImageDataType(agl_gfx_image_format_t format) {
    switch (format) {
    case AGL_GFX_IMAGE_FORMAT_R8_UNORM:        return GL_UNSIGNED_BYTE;
    case AGL_GFX_IMAGE_FORMAT_R8G8_UNORM:      return GL_UNSIGNED_BYTE;
    case AGL_GFX_IMAGE_FORMAT_R8G8B8_UNORM:    return GL_UNSIGNED_BYTE;
    case AGL_GFX_IMAGE_FORMAT_R8G8B8A8_UNORM:  return GL_UNSIGNED_BYTE;
    case AGL_GFX_IMAGE_FORMAT_R8_SNORM:        return GL_BYTE;
    case AGL_GFX_IMAGE_FORMAT_R8G8_SNORM:      return GL_BYTE;
    case AGL_GFX_IMAGE_FORMAT_R8G8B8_SNORM:    return GL_BYTE;
    case AGL_GFX_IMAGE_FORMAT_R8G8B8A8_SNORM:  return GL_BYTE;
    case AGL_GFX_IMAGE_FORMAT_R16F:            return GL_FLOAT;
    case AGL_GFX_IMAGE_FORMAT_R16G16F:         return GL_FLOAT;
    case AGL_GFX_IMAGE_FORMAT_R16G16B16F:      return GL_FLOAT;
    case AGL_GFX_IMAGE_FORMAT_R16G16B16A16F:   return GL_FLOAT;
    default: ;
    }
    return GL_NONE;
}

agl_gfx_image_t agl_gfx_create_image(agl_gfx_context_t context, const agl_gfx_image_params_t *params) {
    agl__gfx_image_t *image = agl__ImagePoolAlloc(&context->imagePool);
    if (!image)
        return AGL_GFX_INVALID_ID;
    GLenum internalFormat = agl__GetImageInternalFormat(params->format);
    GLenum format = agl__GetImageFormat(params->format);
    GLenum type = agl__GetImageDataType(params->format);
    GLuint tex;
    glCreateTextures(GL_TEXTURE_2D, 1, &tex);
    glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(tex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureStorage2D(tex, 1, internalFormat, params->width, params->height);
    glTextureSubImage2D(tex, 0, 0, 0, params->width, params->height, format, type, params->pixelData);
    image->tex = tex;
    image->width = params->width;
    image->height = params->height;
    image->format = params->format;
    image->handle = glGetTextureHandleARB(tex);
    glMakeTextureHandleResidentARB(image->handle);
    image->isResident = true;
    return image->id;
}

void agl_gfx_destroy_image(agl_gfx_context_t context, agl_gfx_image_t id) {
    agl__gfx_image_t *image = agl__ImagePoolGet(&context->imagePool, id);
    if (!image)
        return;
    glMakeTextureHandleNonResidentARB(image->handle);
    image->isResident = false;
    glDeleteTextures(1, &image->tex);
    image->tex = 0;
    agl__ImagePoolFree(&context->imagePool, image);
}

static GLuint agl__ConvertBufferFlags(agl_uint flags) {
    GLuint glflags = 0;
    glflags |= (flags & AGL_GFX_BUFFER_FLAG_DYNAMIC_BIT) ? GL_DYNAMIC_STORAGE_BIT : 0;
    glflags |= (flags & AGL_GFX_BUFFER_FLAG_MAP_PERSISTENT_BIT) ? GL_MAP_PERSISTENT_BIT : 0;
    glflags |= (flags & AGL_GFX_BUFFER_FLAG_MAP_COHERENT_BIT) ? GL_MAP_COHERENT_BIT : 0;
    return glflags;
}

agl_gfx_buffer_t agl_gfx_create_buffer(agl_gfx_context_t context, const agl_gfx_buffer_params_t *params) {
    agl__gfx_buffer_t *buffer = agl__BufferPoolAlloc(&context->bufferPool);
    if (!buffer)
        return AGL_GFX_INVALID_ID;
    GLuint ssbo;
    glCreateBuffers(1, &ssbo);
    glNamedBufferStorage(ssbo, params->size, params->data, agl__ConvertBufferFlags(params->flags));
    buffer->buf = ssbo;
    buffer->size = params->size;
    return buffer->id;
}

void agl_gfx_destroy_buffer(agl_gfx_context_t context, agl_gfx_buffer_t id) {
    agl__gfx_buffer_t *buffer = agl__BufferPoolGet(&context->bufferPool, id);
    if (!buffer)
        return;
    glDeleteBuffers(1, &buffer->buf);
    agl__BufferPoolFree(&context->bufferPool, buffer);
}

agl_gfx_mesh_t agl_gfx_create_mesh(agl_gfx_context_t context, const agl_gfx_mesh_params_t *params) {
    agl__gfx_mesh_t *mesh = agl__MeshPoolAlloc(&context->meshPool);
    if (!mesh)
        return AGL_GFX_INVALID_ID;
    agl_gfx_buffer_params_t bufferParams;
    agl_uint maxBufSize = sizeof(agl_gfx_mesh_buffer_info_t)
                      + sizeof(agl_float3) * params->vertexCount /* position */
                      + sizeof(agl_float2) * params->vertexCount /* uv       */
                      + sizeof(agl_float3) * params->vertexCount /* normal   */
                      + sizeof(agl_float4) * params->vertexCount /* color    */;
    agl_gfx_mesh_buffer_info_t * const bufferInfo = (agl_gfx_mesh_buffer_info_t*)agl__ScratchAlloc(&context->scratchAllocator, maxBufSize);
    agl_float * const data = (agl_float*)(bufferInfo + 1);
    agl_uint offset = 0;
    // Positions
    agl__gfx_assertf(params->positionData, "Mesh positions array cannot but NULL!");
    bufferInfo->PositionStart = offset;
    memcpy(data + offset, params->positionData, sizeof(agl_float3) * params->vertexCount);
    offset += 3 * params->vertexCount;
    // UVs
    if (params->uvData) {
        bufferInfo->UVStart = offset;
        memcpy(data + offset, params->uvData, sizeof(agl_float2) * params->vertexCount);
        offset += 2 * params->vertexCount;
    } else {
        bufferInfo->UVStart = -1;
    }
    // Normals
    if (params->normalData) {
        bufferInfo->NormalStart = offset;
        memcpy(data + offset, params->normalData, sizeof(agl_float3) * params->vertexCount);
        offset += 3 * params->vertexCount;
    } else {
        bufferInfo->NormalStart = -1;
    }
    // Colors
    if (params->colorData) {
        bufferInfo->ColorStart = offset;
        memcpy(data + offset, params->colorData, sizeof(agl_float4) * params->vertexCount);
        offset += 4 * params->vertexCount;
    } else {
        bufferInfo->ColorStart = -1;
    }
    agl_uint bufSize = (agl_uint)((uintptr_t)(data + offset) - (uintptr_t)bufferInfo);
    agl__gfx_assertf(bufSize <= maxBufSize, "Mesh buffer overflow!");
    bufferParams.size = bufSize;
    bufferParams.data = bufferInfo;
    bufferParams.flags = 0;
    mesh->vertexBufId = agl_gfx_create_buffer(context, &bufferParams);
    mesh->vertexCount = params->vertexCount;
    agl__ScratchFree(&context->scratchAllocator);
    // Index Buffer
    if (params->indexData) {
        GLuint ibo;
        glCreateBuffers(1, &ibo);
        glNamedBufferStorage(ibo, sizeof(GLuint) * params->indexCount, params->indexData, 0);
        mesh->ibo = ibo;
        mesh->indexCount = params->indexCount;
    } else {
        mesh->ibo = 0;
        mesh->indexCount = 0;
    }
    return mesh->id;
}

void agl_gfx_destroy_mesh(agl_gfx_context_t context, agl_gfx_mesh_t id) {
    agl__gfx_mesh_t *mesh = agl__MeshPoolGet(&context->meshPool, id);
    if (!mesh)
        return;
    glDeleteBuffers(1, &mesh->ibo);
    agl_gfx_destroy_buffer(context, mesh->vertexBufId);
    agl__MeshPoolFree(&context->meshPool, mesh);
}

static GLuint agl__SwitchProgram(agl__gfx_canvas_t *canvas, GLuint prog) {
    GLuint prev = canvas->activeProg;
    if (prev != prog) {
        glUseProgram(prog);
        canvas->activeProg = prog;
        // agl__gfx_debugf("Switched shaders : [%d] => [%d]", prev, prog);
    }
    return prev;
}

static void agl__FlushQuads(agl__gfx_canvas_t *canvas) {
    glDisable(GL_DEPTH_TEST);
    glNamedBufferSubData(canvas->quadBuf, 0, canvas->quadsUsed * sizeof(agl__gfx_quad_t), canvas->quads);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, canvas->quadBuf);
    agl__SwitchProgram(canvas, canvas->quadProg);
    glDrawArrays(GL_TRIANGLES, 0, canvas->quadsUsed * 6);
    // agl__gfx_debugf("Flushed %u quads", canvas->quadsUsed);
    canvas->quadsUsed = 0;
    // glEnable(GL_DEPTH_TEST);
}

void agl_gfx_main_loop(agl_gfx_context_t context) {
#if _WIN32
    LARGE_INTEGER StartTime, EndTime, ElapsedMicros;
    LARGE_INTEGER Frequency;
    
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&EndTime);
#endif // _WIN32

    context->running = true;

    while (context->running) {
        MSG msg;
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }

        if (context->wantsQuit) {
            context->running = false;
        }

#if _WIN32
        StartTime.QuadPart = EndTime.QuadPart;
        QueryPerformanceCounter(&EndTime);
        ElapsedMicros.QuadPart = EndTime.QuadPart - StartTime.QuadPart;
        ElapsedMicros.QuadPart *= 1000000;
        ElapsedMicros.QuadPart /= Frequency.QuadPart;
        float dt = (float)ElapsedMicros.QuadPart / (float)1000000;
#endif // _WIN32

        glClearColor(0.3, 0.3, 0.3, 1.0);
        glClearDepth(0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, context->canvas->width, context->canvas->height);
        glProgramUniform2f(context->canvas->quadProg, 0, context->canvas->width, context->canvas->height);
        glProgramUniform4uiv(context->canvas->quadProg, 1, 1, &context->canvas->fontGlyphWidth);
        
        context->updatefn(context, dt);
        agl__FlushQuads(context->canvas);

        SwapBuffers(GetDC(context->hwnd));
    }
}

void agl_gfx_draw_screen_quad(agl_gfx_canvas_t canvas, const agl_float2 pos, const agl_float2 size, agl_float angle, agl_color color, agl_gfx_image_t texture) {
    agl__gfx_image_t *image = agl__ImagePoolGet(&canvas->context->imagePool, texture);
    // agl__gfx_debugf("Draw quad: (x: %0.3f, y: %0.3f, w: %0.3f, h: %0.3f) (%0.3f) (%u)", rect.x, rect.y, rect.w, rect.h, angle, image->handle);
    if (canvas->quadsUsed == canvas->quadsTotal) {
        agl__FlushQuads(canvas);
    }
    agl__gfx_quad_t *quad = &canvas->quads[canvas->quadsUsed++];
    quad->pos[0] = pos[0];
    quad->pos[1] = pos[1];
    quad->size[0] = size[0];
    quad->size[1] = size[1];
    quad->angle = angle;
    quad->color = color;
    quad->texture = image ? image->handle : 0;
    quad->flags = image ? AGL_GFX_FLAG_TEXTURED : 0;
}


void agl_gfx_set_camera_position(agl_gfx_canvas_t canvas, const agl_float3 pos) {
    canvas->camera.pos[0] = pos[0];
    canvas->camera.pos[1] = pos[1];
    canvas->camera.pos[2] = pos[2];
}

void agl_gfx_set_camera_look_at(agl_gfx_canvas_t canvas, const agl_float3 tgt, const agl_float3 worldUp) {
    agl_float pos[3] = { canvas->camera.pos[0], canvas->camera.pos[1], canvas->camera.pos[2] };
    agl_float rt[3] = { 0, 0, 0 };
    agl_float up[3] = { worldUp[0], worldUp[1], worldUp[2] };
    agl_float fw[3] = { 0, 0, 0 };
    // fw = sub(pos, tgt);
    fw[0] = pos[0] - tgt[0];
    fw[1] = pos[1] - tgt[1];
    fw[2] = pos[2] - tgt[2];
    // fw = normalize(fw);
    agl_float fwnorm = sqrtf(fw[0]*fw[0] + fw[1]*fw[1] + fw[2]*fw[2]);
    fw[0] = fw[0] / fwnorm;
    fw[1] = fw[1] / fwnorm;
    fw[2] = fw[2] / fwnorm;
    // rt = cross(up, fw);
    rt[0] = up[1] * fw[2] - up[2] * fw[1];
    rt[1] = up[2] * fw[0] - up[0] * fw[2];
    rt[2] = up[0] * fw[1] - up[1] * fw[0];
    // rt = normalize(rt);
    agl_float rtnorm = sqrtf(rt[0]*rt[0] + rt[1]*rt[1] + rt[2]*rt[2]);
    rt[0] = rt[0] / rtnorm;
    rt[1] = rt[1] / rtnorm;
    rt[2] = rt[2] / rtnorm;
    // up = cross(fw, rt);
    up[0] = fw[1] * rt[2] - fw[2] * rt[1];
    up[1] = fw[2] * rt[0] - fw[0] * rt[2];
    up[2] = fw[0] * rt[1] - fw[1] * rt[0];
    // up = normalize(up);
    agl_float upnorm = sqrtf(up[0]*up[0] + up[1]*up[1] + up[2]*up[2]);
    up[0] = up[0] / upnorm;
    up[1] = up[1] / upnorm;
    up[2] = up[2] / upnorm;

    canvas->camera.rot[0][0] = rt[0];
    canvas->camera.rot[1][0] = rt[1];
    canvas->camera.rot[2][0] = rt[2];

    canvas->camera.rot[0][1] = up[0];
    canvas->camera.rot[1][1] = up[1];
    canvas->camera.rot[2][1] = up[2];

    canvas->camera.rot[0][2] = fw[0];
    canvas->camera.rot[1][2] = fw[1];
    canvas->camera.rot[2][2] = fw[2];
}

void agl_gfx_set_camera_perspective(agl_gfx_canvas_t canvas, agl_float fovY, agl_float nearZ, agl_float farZ) {
    canvas->camera.aspect = (agl_float)canvas->width / (agl_float)canvas->height;
    canvas->camera.fovY = fovY;
    canvas->camera.nearZ = nearZ;
    canvas->camera.farZ = farZ;
}

static void agl__MakeViewMatrix(agl_float4 mat[4], const agl_float3 pos, const agl_float3 rot[3]) {
    memset(mat, 0, sizeof(agl_float4[4]));
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
        mat[j][i] = rot[i][j];
    }
    for (int i = 0; i < 3; i++) {
        mat[3][i] = -(pos[0]*rot[0][i] + pos[1]*rot[1][i] + pos[2]*rot[2][i]);
    }
    mat[3][3] = 1.f;
}

static void agl__MakePerspectiveMatrix(agl_float4 mat[4], agl_float aspect, agl_float fovY, agl_float nearZ, agl_float farZ) {
    agl_float n = nearZ, f = farZ;
    agl_float t = tanf(fovY / 2) * n;
    agl_float b = -t;
    agl_float r = t * aspect;
    agl_float l = -t * aspect;
    memset(mat, 0, sizeof(agl_float4[4]));
    mat[0][0] = 2 * n / (r - l);
    mat[1][1] = 2 * n / (t - b);
    mat[2][0] = (r + l) / (r - l);
    mat[2][1] = (t + b) / (t - b);
    mat[2][2] = -(f + n) / (f - n);
    mat[2][3] = -1;
    mat[3][2] = -2 * f * n / (f - n);
}

static void agl__MakeTransformMatrix(agl_float4 mat[4], const agl_float3 pos, const agl_float4 quat, const float scale) {
    memset(mat, 0, sizeof(agl_float4[4]));
    agl_float q0 = quat[3], q1 = quat[0], q2 = quat[1], q3 = quat[2];
    mat[0][0] = 1 - 2*q2*q2 - 2*q3*q3;
	mat[1][0] = 2*q1*q2 - 2*q0*q3;
	mat[2][0] = 2*q1*q3 + 2*q0*q2;
	mat[0][1] = 2*q1*q2 + 2*q0*q3;
	mat[1][1] = 1 - 2*q1*q1 - 2*q3*q3;
	mat[2][1] = 2*q2*q3 - 2*q0*q1;
	mat[0][2] = 2*q1*q3 - 2*q0*q2;
	mat[1][2] = 2*q2*q3 + 2*q0*q1;
	mat[2][2] = 1 - 2*q1*q1 - 2*q2*q2;
    for (int i = 0; i < 3; i++) {
        mat[3][i] = pos[i];
    }
    mat[3][3] = 1.f;
}

void agl_gfx_draw_mesh(agl_gfx_canvas_t canvas, agl_gfx_mesh_t mesh, const agl_float3 pos, const agl_float4 rot, agl_float scale, const agl_float4 color)
{
	// Bind mesh buffer
    agl__gfx_mesh_t *pmesh = agl__MeshPoolGet(&canvas->context->meshPool, mesh);
    agl__gfx_buffer_t *pbuf = agl__BufferPoolGet(&canvas->context->bufferPool, pmesh->vertexBufId);
    if (canvas->activeMesh.id != mesh.id) {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, pbuf->buf);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pmesh->ibo);
        canvas->activeMesh.id = mesh.id;
    }
    {
        agl_float4 mat[4];
        // mat4 CameraView;
        agl__MakeViewMatrix(mat, canvas->camera.pos, canvas->camera.rot);
        glProgramUniformMatrix4fv(canvas->meshProg, 1, 1, GL_FALSE, &mat[0][0]);
        // mat4 CameraProj;
        agl__MakePerspectiveMatrix(mat, (agl_float)canvas->width / (agl_float)canvas->height, canvas->camera.fovY, canvas->camera.nearZ, canvas->camera.farZ);
        glProgramUniformMatrix4fv(canvas->meshProg, 2, 1, GL_FALSE, &mat[0][0]);
        // mat4 Transform;
        agl__MakeTransformMatrix(mat, pos, rot, scale);
        glProgramUniformMatrix4fv(canvas->meshProg, 3, 1, GL_FALSE, &mat[0][0]);
        // vec4 TintColor
        if (color == NULL)
            color = (agl_float4){1,1,1,1};
        glProgramUniform4fv(canvas->meshProg, 4, 1, &color[0]);
    }
    agl__SwitchProgram(canvas, canvas->meshProg);
    if (pmesh->ibo) {
        glDrawElements(GL_TRIANGLES, pmesh->indexCount, GL_UNSIGNED_INT, 0);
        // agl__gfx_tracef("Draw Call (Mesh) : %d verts, %d indxs", pmesh->vertexCount, pmesh->indexCount);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, pmesh->vertexCount);
        // agl__gfx_tracef("Draw Call (Mesh) : %d verts", pmesh->vertexCount);
    }
}

static uint32_t agl__GetFontGlyph(char c) {
    switch (c) {
    case ' ': return AGL_FONT_GLYPH_SPACE;
    case '0': return AGL_FONT_GLYPH_0;
    case '1': return AGL_FONT_GLYPH_1;
    case '2': return AGL_FONT_GLYPH_2;
    case '3': return AGL_FONT_GLYPH_3;
    case '4': return AGL_FONT_GLYPH_4;
    case '5': return AGL_FONT_GLYPH_5;
    case '6': return AGL_FONT_GLYPH_6;
    case '7': return AGL_FONT_GLYPH_7;
    case '8': return AGL_FONT_GLYPH_8;
    case '9': return AGL_FONT_GLYPH_9;
    case 'A': return AGL_FONT_GLYPH_A;
    case 'B': return AGL_FONT_GLYPH_B;
    case 'C': return AGL_FONT_GLYPH_C;
    case 'D': return AGL_FONT_GLYPH_D;
    case 'E': return AGL_FONT_GLYPH_E;
    case 'F': return AGL_FONT_GLYPH_F;
    case 'G': return AGL_FONT_GLYPH_G;
    case 'H': return AGL_FONT_GLYPH_H;
    case 'I': return AGL_FONT_GLYPH_I;
    case 'J': return AGL_FONT_GLYPH_J;
    case 'K': return AGL_FONT_GLYPH_K;
    case 'L': return AGL_FONT_GLYPH_L;
    case 'M': return AGL_FONT_GLYPH_M;
    case 'N': return AGL_FONT_GLYPH_N;
    case 'O': return AGL_FONT_GLYPH_O;
    case 'P': return AGL_FONT_GLYPH_P;
    case 'Q': return AGL_FONT_GLYPH_Q;
    case 'R': return AGL_FONT_GLYPH_R;
    case 'S': return AGL_FONT_GLYPH_S;
    case 'T': return AGL_FONT_GLYPH_T;
    case 'U': return AGL_FONT_GLYPH_U;
    case 'V': return AGL_FONT_GLYPH_V;
    case 'W': return AGL_FONT_GLYPH_W;
    case 'X': return AGL_FONT_GLYPH_X;
    case 'Y': return AGL_FONT_GLYPH_Y;
    case 'Z': return AGL_FONT_GLYPH_Z;
    case 'a': return AGL_FONT_GLYPH_a;
    case 'b': return AGL_FONT_GLYPH_b;
    case 'c': return AGL_FONT_GLYPH_c;
    case 'd': return AGL_FONT_GLYPH_d;
    case 'e': return AGL_FONT_GLYPH_e;
    case 'f': return AGL_FONT_GLYPH_f;
    case 'g': return AGL_FONT_GLYPH_g;
    case 'h': return AGL_FONT_GLYPH_h;
    case 'i': return AGL_FONT_GLYPH_i;
    case 'j': return AGL_FONT_GLYPH_j;
    case 'k': return AGL_FONT_GLYPH_k;
    case 'l': return AGL_FONT_GLYPH_l;
    case 'm': return AGL_FONT_GLYPH_m;
    case 'n': return AGL_FONT_GLYPH_n;
    case 'o': return AGL_FONT_GLYPH_o;
    case 'p': return AGL_FONT_GLYPH_p;
    case 'q': return AGL_FONT_GLYPH_q;
    case 'r': return AGL_FONT_GLYPH_r;
    case 's': return AGL_FONT_GLYPH_s;
    case 't': return AGL_FONT_GLYPH_t;
    case 'u': return AGL_FONT_GLYPH_u;
    case 'v': return AGL_FONT_GLYPH_v;
    case 'w': return AGL_FONT_GLYPH_w;
    case 'x': return AGL_FONT_GLYPH_x;
    case 'y': return AGL_FONT_GLYPH_y;
    case 'z': return AGL_FONT_GLYPH_z;
    case '_': return AGL_FONT_GLYPH_UNDERSCORE;
    case ':': return AGL_FONT_GLYPH_COLON;
    case '.': return AGL_FONT_GLYPH_DOT;
    case '=': return AGL_FONT_GLYPH_EQUAL;
    case '+': return AGL_FONT_GLYPH_PLUS;
    case '-': return AGL_FONT_GLYPH_MINUS;
    case '*': return AGL_FONT_GLYPH_STAR;
    case '/': return AGL_FONT_GLYPH_SLASH;
    case '%': return AGL_FONT_GLYPH_PERCENT;
    default: ;
    }
    return AGL_FONT_GLYPH_SPACE;
}

static void agl__DrawGlyph(agl_gfx_canvas_t canvas, const agl_float2 pos, agl_float height, agl_color color, char c) {
    agl__gfx_image_t *image = agl__ImagePoolGet(&canvas->context->imagePool, canvas->fontImage);
    agl__gfx_assertf(image, "Font texture not initialized!");
    if (canvas->quadsUsed == canvas->quadsTotal) {
        agl__FlushQuads(canvas);
    }
    agl__gfx_quad_t *quad = &canvas->quads[canvas->quadsUsed++];
    quad->pos[0] = pos[0];
    quad->pos[1] = pos[1];
    quad->size[0] = height * (agl_float)canvas->fontGlyphWidth / (agl_float)canvas->fontGlyphHeight;
    quad->size[1] = height;
    quad->angle = 0;
    quad->glyph = agl__GetFontGlyph(c);
	quad->color = color;
    quad->texture = image->handle;
    quad->flags = AGL_GFX_FLAG_TEXTURED | AGL_GFX_FLAG_FONTGLYPH;
}

void agl_gfx_draw_text(agl_gfx_canvas_t canvas, const agl_float2 startpos, agl_float height, agl_color color, const char *text) {
    if (!text) return;
    agl_float glyphX = startpos[0];
    agl_float glyphY = startpos[1];
    agl_float glyphH = height;
    agl_float glyphW = height * (agl_float)canvas->fontGlyphWidth / (agl_float)canvas->fontGlyphHeight;
    for (const char *c = text; *c != '\0'; c++) {
        agl__DrawGlyph(canvas, (agl_float2){ glyphX, glyphY }, height, color, *c);
        glyphX += glyphW;
    }
}


#define AGL_FONT_GLYPH_BITMAP_TYPE uint32_t
#define AGL_FONT_ATLAS_MAXCOLS 16
#define AGL_FONT_GLYPH_BITMAP_WIDTH 7
#define AGL_FONT_GLYPH_BITMAP_HEIGHT 10

#define AGL_COLOR_TRANSPARENT 0x00000000
#define AGL_COLOR_WHITE 0xFFFFFFFF

#define _0 AGL_COLOR_TRANSPARENT
#define _1 AGL_COLOR_WHITE

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_SPACE[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_0[] = {
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _1, _1, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _1, _1, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_1[] = {
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _1, _1, _0, _0, _0,
    _0, _1, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_2[] = {
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _1, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_3[] = {
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_4[] = {
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _1, _1, _0, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _1, _0, _0, _1, _0, _0,
    _0, _1, _0, _0, _1, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_5[] = {
    _0, _1, _1, _1, _1, _1, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_6[] = {
    _0, _0, _0, _1, _1, _1, _0,
    _0, _0, _1, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _1, _1, _0, _0,
    _0, _1, _1, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_7[] = {
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _1, _0, _0, _0, _0,
    _0, _0, _1, _0, _0, _0, _0,
    _0, _0, _1, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_8[] = {
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_9[] = {
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _1, _1, _0,
    _0, _0, _1, _1, _0, _1, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _1, _1, _1, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_A[] = {
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_B[] = {
    _0, _1, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_C[] = {
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_D[] = {
    _0, _1, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_E[] = {
    _0, _1, _1, _1, _1, _1, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_F[] = {
    _0, _1, _1, _1, _1, _1, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_G[] = {
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _1, _1, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_H[] = {
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_I[] = {
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_J[] = {
    _0, _0, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _1, _1, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_K[] = {
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _1, _0, _0,
    _0, _1, _0, _1, _0, _0, _0,
    _0, _1, _1, _0, _0, _0, _0,
    _0, _1, _0, _1, _0, _0, _0,
    _0, _1, _0, _0, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_L[] = {
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_M[] = {
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _1, _0, _1, _1, _0,
    _0, _1, _1, _0, _1, _1, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_N[] = {
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _1, _0, _0, _1, _0,
    _0, _1, _1, _0, _0, _1, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _1, _0, _0, _1, _1, _0,
    _0, _1, _0, _0, _1, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_O[] = {
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_P[] = {
    _0, _1, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_Q[] = {
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
};


const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_R[] = {
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _1, _1, _1, _0, _0,
    _0, _1, _0, _1, _0, _0, _0,
    _0, _1, _0, _0, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};


const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_S[] = {
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _0, _1, _0, _0, _0, _0,
    _0, _0, _0, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_T[] = {
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_U[] = {
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_V[] = {
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_W[] = {
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_X[] = {
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_Y[] = {
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_Z[] = {
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _1, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_a[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_b[] = {
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_c[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _1, _1, _1, _1, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _0, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_d[] = {
    _0, _0, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_e[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_f[] = {
    _0, _0, _0, _0, _1, _1, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_g[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _1, _1, _1, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_h[] = {
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_i[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _1, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_j[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _1, _1, _0, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _1, _1, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_k[] = {
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _1, _0, _0,
    _0, _1, _0, _1, _0, _0, _0,
    _0, _1, _1, _1, _0, _0, _0,
    _0, _1, _0, _0, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_l[] = {
    _0, _0, _1, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_m[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _1, _1, _0, _1, _0, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_n[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_o[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_p[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_q[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _1, _1, _1, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _1, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_r[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _1, _0, _1, _1, _0, _0,
    _0, _1, _1, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_s[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _0, _0, _0,
    _0, _0, _0, _0, _1, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_t[] = {
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _0, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_u[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_v[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_w[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_x[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _1, _0, _1, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_y[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _1, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_z[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _1, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_UNDERSCORE[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_COLON[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_DOT[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_EQUAL[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_PLUS[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_MINUS[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _1, _1, _1, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_STAR[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _1, _1, _1, _0, _0,
    _0, _1, _0, _1, _0, _1, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_SLASH[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _1, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _1, _0, _0, _0, _0,
    _0, _0, _1, _0, _0, _0, _0,
    _0, _1, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

const AGL_FONT_GLYPH_BITMAP_TYPE AGL_FONT_GLYPH_BITMAP_PERCENT[] = {
    _0, _0, _0, _0, _0, _0, _0,
    _0, _1, _1, _0, _0, _1, _0,
    _0, _1, _1, _0, _1, _0, _0,
    _0, _0, _0, _0, _1, _0, _0,
    _0, _0, _0, _1, _0, _0, _0,
    _0, _0, _1, _0, _0, _0, _0,
    _0, _0, _1, _0, _1, _1, _0,
    _0, _1, _0, _0, _1, _1, _0,
    _0, _0, _0, _0, _0, _0, _0,
    _0, _0, _0, _0, _0, _0, _0,
};

#undef _0
#undef _1

const AGL_FONT_GLYPH_BITMAP_TYPE *AGL_FONT_GLYPH_BITMAP_ARRAY[] = {
    AGL_FONT_GLYPH_BITMAP_SPACE,
    AGL_FONT_GLYPH_BITMAP_0,
    AGL_FONT_GLYPH_BITMAP_1,
    AGL_FONT_GLYPH_BITMAP_2,
    AGL_FONT_GLYPH_BITMAP_3,
    AGL_FONT_GLYPH_BITMAP_4,
    AGL_FONT_GLYPH_BITMAP_5,
    AGL_FONT_GLYPH_BITMAP_6,
    AGL_FONT_GLYPH_BITMAP_7,
    AGL_FONT_GLYPH_BITMAP_8,
    AGL_FONT_GLYPH_BITMAP_9,
    AGL_FONT_GLYPH_BITMAP_A,
    AGL_FONT_GLYPH_BITMAP_B,
    AGL_FONT_GLYPH_BITMAP_C,
    AGL_FONT_GLYPH_BITMAP_D,
    AGL_FONT_GLYPH_BITMAP_E,
    AGL_FONT_GLYPH_BITMAP_F,
    AGL_FONT_GLYPH_BITMAP_G,
    AGL_FONT_GLYPH_BITMAP_H,
    AGL_FONT_GLYPH_BITMAP_I,
    AGL_FONT_GLYPH_BITMAP_J,
    AGL_FONT_GLYPH_BITMAP_K,
    AGL_FONT_GLYPH_BITMAP_L,
    AGL_FONT_GLYPH_BITMAP_M,
    AGL_FONT_GLYPH_BITMAP_N,
    AGL_FONT_GLYPH_BITMAP_O,
    AGL_FONT_GLYPH_BITMAP_P,
    AGL_FONT_GLYPH_BITMAP_Q,
    AGL_FONT_GLYPH_BITMAP_R,
    AGL_FONT_GLYPH_BITMAP_S,
    AGL_FONT_GLYPH_BITMAP_T,
    AGL_FONT_GLYPH_BITMAP_U,
    AGL_FONT_GLYPH_BITMAP_V,
    AGL_FONT_GLYPH_BITMAP_W,
    AGL_FONT_GLYPH_BITMAP_X,
    AGL_FONT_GLYPH_BITMAP_Y,
    AGL_FONT_GLYPH_BITMAP_Z,
    AGL_FONT_GLYPH_BITMAP_a,
    AGL_FONT_GLYPH_BITMAP_b,
    AGL_FONT_GLYPH_BITMAP_c,
    AGL_FONT_GLYPH_BITMAP_d,
    AGL_FONT_GLYPH_BITMAP_e,
    AGL_FONT_GLYPH_BITMAP_f,
    AGL_FONT_GLYPH_BITMAP_g,
    AGL_FONT_GLYPH_BITMAP_h,
    AGL_FONT_GLYPH_BITMAP_i,
    AGL_FONT_GLYPH_BITMAP_j,
    AGL_FONT_GLYPH_BITMAP_k,
    AGL_FONT_GLYPH_BITMAP_l,
    AGL_FONT_GLYPH_BITMAP_m,
    AGL_FONT_GLYPH_BITMAP_n,
    AGL_FONT_GLYPH_BITMAP_o,
    AGL_FONT_GLYPH_BITMAP_p,
    AGL_FONT_GLYPH_BITMAP_q,
    AGL_FONT_GLYPH_BITMAP_r,
    AGL_FONT_GLYPH_BITMAP_s,
    AGL_FONT_GLYPH_BITMAP_t,
    AGL_FONT_GLYPH_BITMAP_u,
    AGL_FONT_GLYPH_BITMAP_v,
    AGL_FONT_GLYPH_BITMAP_w,
    AGL_FONT_GLYPH_BITMAP_x,
    AGL_FONT_GLYPH_BITMAP_y,
    AGL_FONT_GLYPH_BITMAP_z,
    AGL_FONT_GLYPH_BITMAP_UNDERSCORE,
    AGL_FONT_GLYPH_BITMAP_COLON,
    AGL_FONT_GLYPH_BITMAP_DOT,
    AGL_FONT_GLYPH_BITMAP_EQUAL,
    AGL_FONT_GLYPH_BITMAP_PLUS,
    AGL_FONT_GLYPH_BITMAP_MINUS,
    AGL_FONT_GLYPH_BITMAP_STAR,
    AGL_FONT_GLYPH_BITMAP_SLASH,
    AGL_FONT_GLYPH_BITMAP_PERCENT,
};

static void agl__BlockCopy(void *dst, int dstOffsetX, int dstOffsetY, int dstSizeX, int dstSizeY, const void *src, int srcOffsetX, int srcOffsetY, int srcSizeX, int srcSizeY, int stride) {
    // agl__gfx_debugf("BlockCopy( dstOffsetX=%d, dstOffsetY=%d, dstSizeX=%d, dstSizeY=%d, srcOffsetX=%d, srcOffsetY=%d, srcSizeX=%d, srcSizeY=%d, stride=%d )", dstOffsetX, dstOffsetY, dstSizeX, dstSizeY, srcOffsetX, srcOffsetY, srcSizeX, srcSizeY, stride);
    for (int y = 0; y < srcSizeY; y++) for (int x = 0; x < srcSizeX; x++) {
        uint32_t dstOffset = (dstOffsetY + y) * dstSizeX + (dstOffsetX + x);
        uint32_t srcOffset = (srcOffsetY + y) * srcSizeX + (srcOffsetX + x);
        uint8_t *d = (uint8_t*)((uintptr_t)dst + (dstOffset * stride));
        uint8_t *s = (uint8_t*)((uintptr_t)src + (srcOffset * stride));
        // agl__gfx_debugf(" >> dstOffset=%u, srcOffset=%u, stride=%u )", dstOffset, srcOffset, stride);
        memcpy(d, s, stride);
    }
}

static void agl__CreateFontImage(agl_gfx_context_t context) {
    agl_gfx_image_params_t fontImageParams;
    uint32_t fontImageCols = min(AGL_FONT_GLYPH_COUNT, AGL_FONT_ATLAS_MAXCOLS);
    uint32_t fontImageRows = (AGL_FONT_GLYPH_COUNT + fontImageCols - 1) / fontImageCols;
    size_t fontImageSize = fontImageCols * fontImageRows * AGL_FONT_GLYPH_BITMAP_WIDTH * AGL_FONT_GLYPH_BITMAP_HEIGHT * sizeof(AGL_FONT_GLYPH_BITMAP_TYPE);
    AGL_FONT_GLYPH_BITMAP_TYPE *fontBitmapCombined = (AGL_FONT_GLYPH_BITMAP_TYPE*)agl__ScratchAlloc(&context->scratchAllocator, fontImageSize);
    memset(fontBitmapCombined, 0, fontImageSize);
    for (int g = 0; g < AGL_FONT_GLYPH_COUNT; g++) {
        uint32_t c = g % fontImageCols;
        uint32_t r = g / fontImageCols;
        agl__BlockCopy(
            fontBitmapCombined,
            c * AGL_FONT_GLYPH_BITMAP_WIDTH, r * AGL_FONT_GLYPH_BITMAP_HEIGHT,
            fontImageCols * AGL_FONT_GLYPH_BITMAP_WIDTH, fontImageRows * AGL_FONT_GLYPH_BITMAP_HEIGHT,
            AGL_FONT_GLYPH_BITMAP_ARRAY[g],
            0, 0,
            AGL_FONT_GLYPH_BITMAP_WIDTH, AGL_FONT_GLYPH_BITMAP_HEIGHT,
            sizeof(AGL_FONT_GLYPH_BITMAP_TYPE));
    }
    fontImageParams.pixelData = fontBitmapCombined;
    fontImageParams.width = fontImageCols * AGL_FONT_GLYPH_BITMAP_WIDTH;
    fontImageParams.height = fontImageRows * AGL_FONT_GLYPH_BITMAP_HEIGHT;
    fontImageParams.format = AGL_GFX_IMAGE_FORMAT_R8G8B8A8_UNORM;
    agl_gfx_image_t fontImage = agl_gfx_create_image(context, &fontImageParams);
    context->canvas->fontImage = fontImage;
    context->canvas->fontGlyphWidth = AGL_FONT_GLYPH_BITMAP_WIDTH;
    context->canvas->fontGlyphHeight = AGL_FONT_GLYPH_BITMAP_HEIGHT;
    context->canvas->fontTexCols = fontImageCols;
    context->canvas->fontTexRows = fontImageRows;
    agl__ScratchFree(&context->scratchAllocator);
}

void agl_gfxh_show_font_texture(agl_gfx_canvas_t canvas, const agl_float2 position) {
    agl_gfx_draw_screen_quad(canvas, position, (agl_float2){ 0.01 * canvas->fontGlyphWidth * canvas->fontTexCols, 0.01 * canvas->fontGlyphHeight * canvas->fontTexRows }, 0, AGL_COLOR_WHITE, canvas->fontImage);
}

#undef XSTR
#undef STR

#endif // AGL_GFX_IMPLEMENTED

#endif // AGL_GFX_IMPLEMENTATION