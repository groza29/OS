#!/bin/bash

# Compile the C file
gcc -o output_file $1 2> temp_error_file.txt

# Extract the errors and warnings from the error file
errors=$(grep -o 'error' temp_error_file.txt | wc -l)
warnings=$(grep -o 'warning' temp_error_file.txt | wc -l)

# Print the number of errors and warnings
echo "Number of errors: $errors"
echo "Number of warnings: $warnings"

# Delete the temporary error file
rm temp_error_file.txt

