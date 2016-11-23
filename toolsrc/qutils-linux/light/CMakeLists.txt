cmake_minimum_required(VERSION 2.6)
project(light)


include_directories(
	"../common/"
) 

set(SOURCE_FILES
	"../common/mathlib.c"
	"../common/cmdlib.c"
	"../common/bspfile.c"
	"threads.c" 
	"entities.c" 
	"light.c" 
	"ltface.c" 
	"trace.c"
)


add_executable(light ${SOURCE_FILES})

target_link_libraries(light
        m
)

install(TARGETS light RUNTIME DESTINATION bin)
