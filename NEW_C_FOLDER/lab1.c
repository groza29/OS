#include <stdio.h>

int main(){
    int A[40],n,sum=0;
    printf("Insert No. of elements of the array: \n");
    scanf("%i",&n);
    for(int i =0;i<n;i++){
        printf("Insert %i element: ", i);
        scanf("%d",&A[i]);
        sum+=A[i];
    }
    printf("Sum is equal to = %f \n", (float sum)/n);
    return 0;
}