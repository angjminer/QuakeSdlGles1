cmake_minimum_required(VERSION 2.6)
project(texmake)


include_directories(
	"../common/"
) 

set(SOURCE_FILES
	"../common/mathlib.c"
	"../common/cmdlib.c"
	"../common/lbmlib.c"
	"../common/trilib.c"
	"texmake.c" 
)


add_executable(texmake ${SOURCE_FILES})

target_link_libraries(texmake
        m
)

install(TARGETS texmake RUNTIME DESTINATION bin) 
