#!/bin/bash
###
# Rebuild program and create link.
###
hg pull -u
make clobber
make all
if [ ! -f ghw ]; then
    ln -s dist/Release/GNU-Linux-x86/ghw
fi
