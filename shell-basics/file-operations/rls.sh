#!/bin/bash
# List files whose names are within a length range.

if [[ $# -ne 2 ]]; then
	echo "Error! Correct usage: $0 <min> <max>" >&2
	exit 1
fi

for element in *; do
	
	length=${#element}

	if [[ $length -ge $1 ]] && [[ $length -lt $2 ]]; then
		printf "$element, length: %d\n" $length
	fi
done
