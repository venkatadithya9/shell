#include "headers.h"
#include "variables.h"

int unstenv()
{
    int chk = 0;
    if(insize == 0 || insize > 1)
    {
        printf("Invalid number of arguments\n");
        return(1);
    }
    else
    {
        chk = unsetenv(arr[1]);
        if(chk != 0)
        {
            perror("unsetenv error");
            return(1);
        }
    }
    
    return 0;
}