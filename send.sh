#!/bin/bash
PRG=`basename "$PWD"`
HOSTDIR="applepi://home/nils"
echo "[${PRG}] Sending to AppleIO ..."
scp "build/${PRG}.po" $HOSTDIR
