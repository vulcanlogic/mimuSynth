#!/bin/bash
PRG=`basename "$PWD"`

if test -f "${PRG}.dsk"; then
  echo "[${PRG}] Cleaning up boot disk."
  rm "build/${PRG}.dsk"
fi

echo "[${PRG}] Preparing boot disk image."
cp boot.dsk "build/${PRG}.dsk"
ac.sh -p "build/${PRG}.dsk" "${PRG}.system" sys < /usr/share/cc65/target/apple2/util/loader.system

echo "[${PRG}] Copy to boot disk."
ac.sh -as "build/${PRG}.dsk" $PRG < "build/${PRG}.apple2"
echo "[${PRG}] Boot disk image created."
