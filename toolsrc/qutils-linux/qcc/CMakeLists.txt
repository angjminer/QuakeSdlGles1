cmake_minimum_required(VERSION 2.6)
project(qcc)


include_directories(
	"../common/"
) 

set(SOURCE_FILES
	"../common/cmdlib.c"
	"qcc.c"
	"pr_comp.c" 
	"pr_lex.c"
)


add_executable(qcc ${SOURCE_FILES})

target_link_libraries(qcc
        m
)

install(TARGETS qcc RUNTIME DESTINATION bin) 
