#!/bin/bash
PRG=`basename "$PWD"`

if test -f "${PRG}.po"; then
  echo "[${PRG}] Cleaning up ProDOS image."
  rm "build/${PRG}.po"
fi

echo "[${PRG}] Creating new ProDOS image."
ac.sh -pro140 "build/${PRG}.po" $PRG

echo "[${PRG}] Copy to ProDOS image."
ac.sh -as "build/${PRG}.po" $PRG < "build/${PRG}.apple2"

echo "[${PRG}] Packaging done."
