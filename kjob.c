#include "headers.h"
#include "variables.h"

int kjob()
{
    if(insize == 2)
    {
        int pnum;
        if(strlen(arr[1]) == 1) pnum = arr[1][0] - '0';
        else if(strlen(arr[1]) == 2) pnum = arr[1][0] - '0' + 10*(arr[1][1] - '0');
        else
        {
            printf("Background job limit exceeded\n");
            return(1);
        }
        if(pnum > pos || pnum <= 0)
        {
            printf("Invalid job number\n");
            return(1);
        }
        int signum = arr[2][0] - '0';
        int chk, j =0 ;
        while(j != pnum - 1)
        {
            if(status[j] == 0) j++; 
        }
        chk = kill(pid[j], signum);
        if(chk != 0)
        {
            perror("Kill error");
            return(1);
        }
    }
    else
    {
        printf("Invalid number of arguments\n");
        return(1);
    }
    
    return(0);
}