gcc -Wall -o lab5.out $file 2>&1 | egrep "warning|error" | wc -l 
