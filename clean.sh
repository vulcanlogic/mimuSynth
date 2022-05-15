#!/bin/bash
PRG=`basename "$PWD"`

echo "[${PRG}] Cleaning up build directory."
rm -rf build
mkdir build

# if test -f "${PRG}.apple2"; then
#   rm *.apple2
#   rm *.map
# fi
#
# if test -f "${PRG}.po"; then
#   rm "${PRG}.po"
# fi
#
# if test -f "${PRG}.dsk"; then
#   rm "${PRG}.dsk"
# fi
