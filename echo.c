#include"headers.h"
#include"variables.h"

int echo()
{
    if(strcmp(arr[0], "echo") != 0)
    {
        return(1);
    } 
    //printf("Inside echo\n");
    char delim[] = "\t";
    char* token;
    for(int i=1; i<= insize; i++)
    {
        printf("%s", arr[i]);
        if(i < insize ) printf(" ");
    }
    printf("\n");
    return(0);
}