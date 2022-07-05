#include "headers.h"
#include "variables.h"

void token()
{
    for(int i=0; i<100; i++)
        cmd[i] = NULL;
    char* token;
    char delim1[] = ";\n";
    int i=0;
    token = strtok(input, delim1);
    
    while(token != NULL)
    {
        cmd[i] = token;
        i++;
        token = strtok(NULL ,delim1);
    }
        
    num_cmd = i;
        
}