cmake_minimum_required(VERSION 2.6)
project(bspinfo)


include_directories(
	"../common/"
) 

set(SOURCE_FILES
	"../common/cmdlib.c"
	"../common/bspfile.c"
	"bspinfo.c"
)


add_executable(bspinfo ${SOURCE_FILES})

target_link_libraries(bspinfo
        m
)

install(TARGETS bspinfo RUNTIME DESTINATION bin) 
