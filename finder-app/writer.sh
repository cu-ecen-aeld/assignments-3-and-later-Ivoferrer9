#!/bin/bash

# Check if the number of arguments are equal to 2
if [ "$#" -ne 2 ]; then
    echo "Error: Two arguments are required."
    exit 1
fi
#assign first argument as writefile
writefile="$1"

#assign second argument as content
writestr="$2"
if [ -z "$writefile" ] || [ -z "$writestr" ]; then
    echo "Error: Arguments cannot be empty."
    exit 1
fi
mkdir -p "$(dirname "$writefile")"

# Write the content to the file
echo "$writestr" > "$writefile"

# the returned value is checked if there is error
if [ "$?" -ne 0 ]; then
    echo "Error: Failed to write to the file."
    exit 1
fi

echo "File '$writefile' created with content:"
echo "$writestr"
