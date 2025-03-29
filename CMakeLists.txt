cmake_minimum_required(VERSION 3.31)
project(iidxio-bio2video VERSION 0.1
			 LANGUAGES C
)

if(NOT EXISTS ./extern/libaio.dll)
	message(FATAL_ERROR "extern/libaio.dll is missing!")
elseif(NOT EXISTS ./extern/libaio-iob.dll)
	message(FATAL_ERROR "extern/libaio-iob.dll is missing!")
elseif(NOT EXISTS ./extern/libaio-iob2_video.dll)
	message(FATAL_ERROR "extern/libaio-iob2_video.dll is missing!")
endif()

include_directories(bemanitools/src/main)

add_executable(bio2test src/main.c)

target_link_libraries(bio2test ./extern/libaio.dll
	                       ./extern/libaio-iob.dll
			       ./extern/libaio-iob2_video.dll
)

