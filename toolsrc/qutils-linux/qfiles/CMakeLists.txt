cmake_minimum_required(VERSION 2.6)
project(qfiles)


include_directories(
	"../common/"
) 

set(SOURCE_FILES
	"../common/cmdlib.c"
	"qfiles.c"
)


add_executable(qfiles ${SOURCE_FILES})

target_link_libraries(qfiles
        m
)

install(TARGETS qfiles RUNTIME DESTINATION bin) 
