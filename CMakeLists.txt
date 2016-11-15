cmake_minimum_required(VERSION 2.6)
project(QSdlGles)

add_definitions(
    #-DHAVE_OPENGLES 
)

#find_package(OpenGL REQUIRED)
add_subdirectory (extlib)

include_directories(
	"engsrc/"
	"extlib/glm/"
	"extlib/SDL2/include/"
	${OPENGL_INCLUDE_DIR}
)
set(MY_EXTLIB_SOURCE
	"extlib/arraylib/array.c"
)
set(CL_SOURCE_FILES
        "engsrc/cl_demo.c"
        "engsrc/cl_input.c"
        "engsrc/cl_main.c"
        "engsrc/cl_parse.c"
        "engsrc/cl_tent.c"
        "engsrc/chase.c"
        "engsrc/cmd.c"
        "engsrc/common.c"
        "engsrc/console.c"
        "engsrc/crc.c"
        "engsrc/cvar.c"
)
set(SV_SOURCE_FILES
        "engsrc/host.c"
        "engsrc/host_cmd.c"
        "engsrc/keys.c"
        "engsrc/menu.c"
        "engsrc/mathlib.c"
        "engsrc/net_dgrm.c"
        "engsrc/net_loop.c"
        "engsrc/net_main.c"
        "engsrc/net_vcr.c"
        "engsrc/net_udp.c"
        "engsrc/net_bsd.c"
        "engsrc/pr_cmds.c"
        "engsrc/pr_edict.c"
        "engsrc/pr_exec.c"
        "engsrc/r_part.c"
        "engsrc/sbar.c"
        "engsrc/sv_main.c"
        "engsrc/sv_phys.c"
        "engsrc/sv_move.c"
        "engsrc/sv_user.c"
        "engsrc/zone.c"
        "engsrc/view.c"
        "engsrc/wad.c"
        "engsrc/world.c"
        "engsrc/cd_null.c"
        "engsrc/sys_linux.c"
        "engsrc/snd_dma.c"
        "engsrc/snd_mem.c"
        "engsrc/snd_mix.c"
        "engsrc/snd_sdl.c"
)
set(GL_SOURCE_FILES
        "engsrc/gl_draw.c"
        "engsrc/gl_mesh.c"
        "engsrc/gl_model.c"
        "engsrc/gl_refrag.c"
        "engsrc/gl_rlight.c"
        "engsrc/gl_rmain.c"
        "engsrc/gl_rmisc.c"
        "engsrc/gl_rsurf.c"
        "engsrc/gl_screen.c"
        "engsrc/gl_warp.c"
        #"engsrc/gl_vidlinuxglx.c"
        "engsrc/gl_vidsdl.c"
 )
 
 add_executable(QSdlGles ${CL_SOURCE_FILES} ${SV_SOURCE_FILES} ${GL_SOURCE_FILES} ${MY_EXTLIB_SOURCE})
 
 target_link_libraries(QSdlGles
	SDL2
	#${OPENGL_LIBRARIES}
)

install(TARGETS QSdlGles RUNTIME DESTINATION QSdlGles)
