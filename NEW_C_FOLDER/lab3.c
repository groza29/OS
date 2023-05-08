#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct songs
{
    unsigned int year;
    char name[60];
    char author[60];
}*A;

int main(int argc, char **argv)
{
    FILE *f;
    char str[1023];
    char *s;
    int nL=0,n=0,i=0;
    unsigned int yea;
    if(argc==3)
    {
        if(!(f=(fopen(argv[1],"r"))))
    {
        printf("Error");
    }
    while(fgets(str,1023,f)!=NULL)
    {
        nL++;
    }
    printf("Lines %i\n",nL);
    A=(struct songs *)malloc(nL * sizeof(struct songs));
    fclose(f);
    f=(fopen(argv[1],"r"));
    while(fgets(str,1023,f)!=NULL)
    {
        n=0;
        if(str[0]=='"')
        {
            s=strtok(str+1,"\"");
            strcpy(A[i].name,s);
            s=strtok(NULL,",");
        }
        else{
            s=strtok(str,",");
            strcpy(A[i].name,s);
        }
        while(n<=2&&s!=NULL)
        {
            n++;
            s=strtok(NULL,",");
            if(n==1)
            {
            strcpy(A[i].author,s);
            }
            if(n==2)
            {
            A[i].year=atoi(s);
            }
        }
        i++;
    }
    fclose(f);
    yea=atoi(argv[2]);
    for(int k=0;k<nL;k++)
    {
        if(yea==A[k].year)
        {
            printf("%i %s    %s     %u \n",k+1,A[k].name,A[k].author,A[k].year);
        }
    }
    free(A);
    }
    else
    {
        printf("Error\n");
    }
    return 0;
}