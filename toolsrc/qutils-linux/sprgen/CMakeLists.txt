cmake_minimum_required(VERSION 2.6)
project(sprgen)


include_directories(
	"../common/"
) 

set(SOURCE_FILES
	"../common/cmdlib.c"
	"../common/lbmlib.c"
	"../common/scriplib.c" 
	"sprgen.c"
)


add_executable(sprgen ${SOURCE_FILES})

target_link_libraries(sprgen
        m
)

install(TARGETS sprgen RUNTIME DESTINATION bin) 
