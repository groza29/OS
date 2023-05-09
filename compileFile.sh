gcc -Wall -o lab5.out $1 2>&1 | egrep "warning" | wc -l 
gcc -Wall -o lab5.out $1 2>&1 | egrep "error" | wc -l 

