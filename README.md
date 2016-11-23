This is id software's Quake(1)
converted to sdl2/gles 1.1.
look in the origsrc folder for terms of use.

Why did I do this?
although there are many "ports" out there
that are visually more pretty,
As an excersize mainly,
but also to let there be a working q1 engine source
that wasnt clompleteley removed from the original(vanilla).

On to it,

Building:
the sdl2 library is in the extlib dir,
it will be built along with the game exe.
the engine uses gles1.1 so make sure you get the dev libs for that as well.

create a "build" folder next to the CMakeLists.txt file
from the build folder call "cmake .."
pay attention to what it says and fix missing dependencies.
notably the one about gles1.

If you are using linux,
switch to the exectestdir

get your quake1 pak files(make the names lower case)
and put them in the id1 folder
and run test.sh
it will copy the exe from the build dir
and run it.
enjoy.

windows/mac
may have to do some work to get it going,
get the full original source here:
https://github.com/id-Software
and edit the CMakeLists.txt to reflect the file changes.
EG:
instead of "sys_linux.c"
you will want "sys_win.c"
that may be all you need to do?
MAC:
you may be able to use as is?

sorry.

any way 

snd_sdl.c was borrowed from the original sdl port of quake
without change.
you can read the README.SDL for author info.

a search for glvertex3, glvertex2,
will lead you to most of the gl changes.
ive left the old code commented out but above
so you can see the difference.

there have also been some 64bit fixes(so it would compile, and not segfault),
you will have to dif the original to find those.

r_mirror, works in the start level, segfaults else where, use at your own peril.

envmapping has not been touched.
screen flashes do not rely completely on the palette,
search //angelo screen flash to see what i did.

most of the code in gl_vidsdl.c came from gl_vidlinuxglx.c, 
and the key/mouse code came from the afor mentioned sdl port with changes for sdl2
i am sure it can be done better, but it works well.

gamma, does not work.
the models are flat shaded.

search for -lmi and compare the file to the original for lightmap workaround.

this is just a working base, as close to the original as possible with gles.
if you find old tutorials EG:
quakesrc.org

it shouldnt be to difficult to follow along.
get it to build first though :D
and make backups every time your changes work as expected.

I will get a list of all the dev libs you need soon.

HAVE FUN

angelo miner
angjminer


