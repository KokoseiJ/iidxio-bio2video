cmake_minimum_required(VERSION 3.31)
project(iidxio-bio2video VERSION 0.1
			 LANGUAGES C
)

set(LIBAIO_DLLS "libaio" "libaio-iob" "libaio-iob2_video")

foreach(DLLNAME IN LISTS LIBAIO_DLLS)
	if (NOT EXISTS ${CMAKE_SOURCE_DIR}/extern/dlls/${DLLNAME}.dll)
		message(FATAL_ERROR "extern/dlls/${DLLNAME} is missing!")
	endif()
endforeach()

set(CMAKE_SHARED_LIBRARY_PREFIX "")

include_directories(bemanitools/src/main)

add_library(iidxio-bi2x SHARED src/iidxio.c)

foreach(DLLNAME IN LISTS LIBAIO_DLLS)
	target_link_libraries(iidxio-bi2x ${CMAKE_SOURCE_DIR}/extern/dlls/${DLLNAME}.dll)
	add_custom_command(TARGET iidxio-bi2x POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/extern/dlls/${DLLNAME}.dll ${CMAKE_BINARY_DIR}
		COMMENT "Created ${CMAKE_BINARY_DIR}/${DLLNAME}.dll"
	)
endforeach()

