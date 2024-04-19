#!/bin/bash


if [ "$#" -ne 2 ]; then
    echo "Error: Two arguments are required."
    exit 1
fi

writefile="$1"

writestr="$2"
if [ -z "$writefile" ] || [ -z "$writestr" ]; then
    echo "Error: Arguments cannot be empty."
    exit 1
fi
mkdir -p "$(dirname "$writefile")"


echo "$writestr" > "$writefile"


if [ "$?" -ne 0 ]; then
    echo "Error: Failed to write to the file."
    exit 1
fi

echo "File '$writefile' created with content:"
echo "$writestr"
