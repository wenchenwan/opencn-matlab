#!/bin/bash

# Check if the file path is provided as an argument
if [ $# -eq 0 ]; then
    echo "Please provide the path to a file as an argument."
    exit 1
fi

# Get the file path from the arguments
file_path="$1"

echo '' > "$file_path"
echo 'git opencn-matlab : ' >> "$file_path"

# Get the name of the current Git branch
current_branch=$(git rev-parse --abbrev-ref HEAD)

# Get the hash of the last commit
commit_hash=$(git rev-parse HEAD)

# Get the last commit message
commit_message=$(git log -1 --pretty=%B)

# Add the information to the file
echo "Current Git branch: $current_branch" >> "$file_path"
echo "Hash of the last commit: $commit_hash" >> "$file_path"
echo "Last commit message: $commit_message" >> "$file_path"

cd ../../..

# Get the name of the current Git branch
current_branch=$(git rev-parse --abbrev-ref HEAD)

# Get the hash of the last commit
commit_hash=$(git rev-parse HEAD)

# Get the last commit message
commit_message=$(git log -1 --pretty=%B)

cd -

echo '' >> "$file_path"
echo 'git opencn : ' >> "$file_path"

# Add the information to the file
echo "Current Git branch: $current_branch" >> "$file_path"
echo "Hash of the last commit: $commit_hash" >> "$file_path"
echo "Last commit message: $commit_message" >> "$file_path"


echo "Information successfully added to $file_path."
