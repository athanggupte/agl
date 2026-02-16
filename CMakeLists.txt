cmake_minimum_required(VERSION 3.20)

project(agl_tests
	VERSION 0.1
	LANGUAGES C CXX)

enable_testing()

add_executable(gfx-test agl_gfx.h tests/gfx_test.c)
target_include_directories(gfx-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
if (WIN32)
	target_link_libraries(gfx-test opengl32)
endif()
	
add_executable(math-test agl_math.h tests/math_test.c)
target_include_directories(math-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
if (UNIX)
	target_link_libraries(math-test m)
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|Intel")
	target_compile_options(math-test PRIVATE "-msse4.2" "-mavx" "-mavx2")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	target_compile_options(math-test PRIVATE "/arch:AVX2")
endif()