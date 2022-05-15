#!/bin/bash
PRG=`basename "$PWD"`

if test -f "${PRG}.apple2"; then
  echo "[${PRG}] Removing build files."
  rm build/*.apple2
  rm build/*.map
fi

echo "[${PRG}] Compiling..."
cl65 -t apple2 -Ois -m "build/${PRG}.map" src/main.c src/mockingboard.c -o "build/${PRG}.apple2"
