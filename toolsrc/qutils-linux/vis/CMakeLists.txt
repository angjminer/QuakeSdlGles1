cmake_minimum_required(VERSION 2.6)
project(vis)


include_directories(
	"../common/"
) 

set(SOURCE_FILES
	"../common/mathlib.c"
	"../common/cmdlib.c"
	"../common/bspfile.c"
	"vis.c"
	"flow.c" 
	"soundpvs.c"
)


add_executable(vis ${SOURCE_FILES})

target_link_libraries(vis
        m
)

install(TARGETS vis RUNTIME DESTINATION bin) 
