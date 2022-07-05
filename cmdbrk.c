#include "headers.h"
#include "variables.h"

void cmdbrk()
{
    cmdsize = 0;
    for(int i=0; i<100; i++)
        toks[i] = NULL;
    char delim2[] = " \n\t";
    char *token;
    token = strtok(cmd[curr_cmd], delim2);
    int i=0;
        while(token != NULL)
        {
            toks[i] = token;
            i++;
            token = strtok(NULL ,delim2);
        }
    cmdsize = i-1;
}