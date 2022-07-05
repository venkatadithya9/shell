#include "headers.h"
#include "variables.h"

int stenv()
{
    int chk = 0;
    if(insize == 0 || insize > 2)
    {
        printf("Invalid number of arguments\n");
        return(1);
    }
    else if(insize == 1)
    {
        chk = setenv(arr[1], "\0", 1);
        if(chk != 0)
        {
            perror("setenv error");
            return(1);
        }
    }
    else
    {
        chk = setenv(arr[1], arr[2], 1);
        if(chk != 0)
        {
            perror("setenv error");
            return(1);
        }
    }
    return(0);
}