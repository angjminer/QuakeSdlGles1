#!/bin/bash
rm ./QSdlGles
cp ../build/QSdlGles ./QSdlGles
./QSdlGles -window -width 640 -height 480 -nomouse
