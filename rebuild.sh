#!/bin/bash
hg pull -u
make clobber
make all
rm ghw
ln -s dist/Release/GNU-Linux-x86/ghw
