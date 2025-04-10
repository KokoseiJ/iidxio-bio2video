cmake_minimum_required(VERSION 3.30)
project(iidxio-bio2video VERSION 0.1
			 LANGUAGES C
)

if (NOT EXISTS ${CMAKE_SOURCE_DIR}/extern/dlls/libaio.dll)
	message(FATAL_ERROR "extern/dlls/ is missing!")
elseif (NOT EXISTS ${CMAKE_SOURCE_DIR}/extern/dlls/libaio-iob.dll)
	message(FATAL_ERROR "extern/dlls/ is missing!")
elseif (NOT EXISTS ${CMAKE_SOURCE_DIR}/extern/dlls/libaio-iob2_video.dll)
	message(FATAL_ERROR "extern/dlls/ is missing!")
endif()

set(CMAKE_SHARED_LIBRARY_PREFIX "")
add_compile_options(-g -Wall)

include_directories(bemanitools/src/main)

add_library(libaio_wrap STATIC src/libaio_wrap.c)
target_link_libraries(libaio_wrap ${CMAKE_SOURCE_DIR}/extern/dlls/libaio.dll
								  ${CMAKE_SOURCE_DIR}/extern/dlls/libaio-iob.dll
								  ${CMAKE_SOURCE_DIR}/extern/dlls/libaio-iob2_video.dll)

add_library(iidxio-bi2x SHARED src/iidxio.c)
target_link_libraries(iidxio-bi2x libaio_wrap)

add_executable(bi2xtest src/main.c)
target_link_libraries(bi2xtest libaio_wrap)

