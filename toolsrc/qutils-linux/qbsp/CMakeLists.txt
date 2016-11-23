cmake_minimum_required(VERSION 2.6)
project(qbsp)


include_directories(
	"../common/"
) 

set(SOURCE_FILES
	"../common/mathlib.c"
	"../common/cmdlib.c"
	"../common/bspfile.c"
	"map.c"
	"brush.c" 
	"csg4.c" 
	"merge.c" 
	"nodraw.c" 
	"portals.c" 
	"outside.c"
	"region.c" 
	"solidbsp.c" 
	"surfaces.c" 
	"tjunc.c" 
	"writebsp.c" 
	"qbsp.c"
)


add_executable(qbsp ${SOURCE_FILES})

target_link_libraries(qbsp
        m
)

install(TARGETS qbsp RUNTIME DESTINATION bin)