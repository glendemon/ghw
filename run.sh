#!/bin/bash
###
# Compute weight hierarchy for codes in ./codes directory.
# Write results to ./results directory.
###

CODE_DIR=codes
RESULT_DIR=results

run_ghw(){
	local file=$1
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
