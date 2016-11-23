cmake_minimum_required(VERSION 2.6)
#project(qutils)
#stuff we will actually use
add_subdirectory (qbsp)
add_subdirectory (vis)
add_subdirectory (light)
add_subdirectory (qcc)
#othere exes that were in the archive, just for completeness atm
#will remove later
add_subdirectory (modelgen)
add_subdirectory (qfiles)
add_subdirectory (qlumpy)
add_subdirectory (sprgen)
add_subdirectory (texmake)
add_subdirectory (bspinfo)
#install(TARGETS tssow RUNTIME DESTINATION bin)