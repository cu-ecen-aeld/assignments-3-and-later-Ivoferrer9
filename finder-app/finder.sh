#!/bin/bash

# Step 1: Check if the correct number of arguments is provided
if [ "$#" -ne 2 ]; then
    echo "Error: Two arguments are required."
    exit 1
fi

# Step 2: Assign provided arguments to variables
filesdir="$1"
searchstr="$2"

# Step 3: Check if the provided directory exists and is a directory
if [ ! -d "$filesdir" ]; then
    echo "Error: $filesdir is not a directory or does not exist."
    exit 1
fi

# Step 4: Use grep to search for the given string within the files in the directory and its subdirectories
# Step 5: Count the number of matching lines and the number of files
num_files=$(find "$filesdir" -type f | wc -l)
num_matches=$(grep -r "$searchstr" "$filesdir" | wc -l)

# Step 6: Print the message with the counts
echo "The number of files are $num_files and the number of matching lines are $num_matches"
