cmake_minimum_required(VERSION 3.20)

project(agl_tests
	VERSION 0.1
	LANGUAGES C CXX)

enable_testing()

add_executable(gfx-test agl_gfx.h tests/gfx_test.c)
if (WIN32)
	target_link_libraries(gfx-test opengl32)
	target_include_directories(gfx-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endif()
