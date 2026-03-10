cmake_minimum_required(VERSION 3.20)

project(agl_tests
	VERSION 0.1
	LANGUAGES C CXX)

enable_testing()

include(agl.cmake)

# Header-only libraries
add_library(agl-gfx INTERFACE)
target_include_directories(agl-gfx INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
if (WIN32)
	target_link_libraries(agl-gfx INTERFACE opengl32)
endif()

add_library(agl-math INTERFACE)
target_include_directories(agl-math INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
if (UNIX)
	target_link_libraries(agl-math INTERFACE m)
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|Intel")
	target_compile_options(agl-math INTERFACE "-msse4.2" "-mavx" "-mavx2")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	target_compile_options(agl-math INTERFACE "/arch:AVX2")
endif()

# Shared library
option(AGL_GFX_ENABLE_ASSERTS "Enable asserts in agl-gfx" ON)

add_library(agl SHARED
	agl.c
	agl_gfx.h
	agl_math.h)
target_link_libraries(agl PUBLIC agl-gfx agl-math)
if(UNIX)
	target_compile_options(agl PRIVATE -fPIC)
endif()
target_compile_definitions(agl PRIVATE AGL_EXPORTS AGL_GFX_CREATE_FONT_IMAGE
	$<$<BOOL:${AGL_GFX_ENABLE_ASSERTS}>:AGL_GFX_ENABLE_ASSERTS>)

# Tests
add_executable(gfx-test agl_gfx.h tests/gfx_test.c)
target_link_libraries(gfx-test agl-gfx)
	
add_executable(math-test agl_math.h tests/math_test.c)
target_link_libraries(math-test agl-math)

# Plugins
add_agl_plugin(fps_counter plugins/fps_counter.c)

add_agl_plugin(gltf_loader plugins/gltf_loader.cpp)
target_include_directories(gltf_loader PRIVATE deps)
