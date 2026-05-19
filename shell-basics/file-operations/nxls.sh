#!/bin/bash
# List non-executable files in a directory.

if [[ $# -ne 1 ]]; then
        echo "Error! Correct usage: $0 <directory>." >&2
        exit 1
fi

case "$1" in
	".") printf "List of non-executable files in current folder:\n\n" $1 ;;
	*) printf "List of non-executable files in %s:\n\n" $1 ;;
esac 

for file in $1/*; do
	if [[ -f $file ]] && [[ ! -x $file ]]; then
		printf "%s\n" $file
	fi
done
