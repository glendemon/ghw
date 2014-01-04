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
	if [ -f $CODE_DIR/$file ]
	then
		echo "Processing ${file}."
		(time $DIR/ghw $CODE_DIR/$file) &> $RESULT_DIR/$file
	fi
}

if [ $# -ge 0  ]
then
	for argv in "$@"
	do
		run_ghw $argv
	done
else
	for file in $CODE_DIR/*
	do
		run_ghw file
	done
fi
