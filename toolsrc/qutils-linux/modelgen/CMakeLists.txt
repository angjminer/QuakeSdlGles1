cmake_minimum_required(VERSION 2.6)
project(modelgen)


include_directories(
	"../common/"
) 

set(SOURCE_FILES
	"../common/mathlib.c"
	"../common/cmdlib.c"
	"../common/scriplib.c"
	"../common/trilib.c"
	"../common/lbmlib.c"
	"modelgen.c"
)


add_executable(modelgen ${SOURCE_FILES})

target_link_libraries(modelgen
        m
)

install(TARGETS modelgen RUNTIME DESTINATION bin) 
