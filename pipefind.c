#include "headers.h"
#include "variables.h"

int pipefind()
{
    num_pipes = 0;

    for(int i =0; i<=cmdsize ; i++)
    {
        if(strcmp(toks[i],"|") == 0)
        {
            pipe_loc[num_pipes] = i;
            num_pipes++;
        }
    }
    return 0;
}