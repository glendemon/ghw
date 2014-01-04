#!/bin/bash
###
# Compute weight hierarchy for codes in ./codes directory.
# Write results to ./results directory.
###

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
CODE_DIR=$DIR/codes
RESULT_DIR=$DIR/results

[ ! -d $RESULT_DIR ] && mkdir -p $RESULT_DIR

run_ghw(){
	local file=`basename $1`
	if [ -f $file ]
	then
		echo "Processing ${file}."
		(time ./ghw $CODE_DIR/$file) &> $RESULT_DIR/$file
	fi
}

if [ -f $1 ]
then
	run_ghw $1
else
	for file in $CODE_DIR/*
	do
		run_ghw file
	done
fi
