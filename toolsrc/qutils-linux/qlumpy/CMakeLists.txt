cmake_minimum_required(VERSION 2.6)
project(qlumpy)


include_directories(
	"../common/"
) 

set(SOURCE_FILES
	"../common/mathlib.c"
	"../common/cmdlib.c"
	"../common/lbmlib.c"
	"../common/wadlib.c"
	"../common/scriplib.c"
	"qlumpy.c" 
	"quakegrb.c"
)


add_executable(qlumpy ${SOURCE_FILES})

target_link_libraries(qlumpy
        m
)

install(TARGETS qlumpy RUNTIME DESTINATION bin) 
