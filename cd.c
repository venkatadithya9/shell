#include "headers.h"
#include "variables.h"

int cd()
{
    if(strcmp(arr[0], "cd") != 0)
    {
        return(1);
    }

    
    char currcwd[4097];
    //printf("point -1");
    if(getcwd(currcwd, sizeof(currcwd)) == NULL)
    {
        perror("Current directory not found");
        return(1);
    }
    int check;

    if(insize > 0)
    {
        if(strcmp(arr[1],"..") == 0)
        {
            check = chdir("..");
            if(check<0)
            {
                perror("Could not change directory");
                return(1);
            }
        }
        else if(strcmp(arr[1],"~") == 0)
        {
            check = chdir(cwd);
            if(check<0)
            {
                perror("Could not change directory");
                return(1);
            }
        }
        else if(strcmp(arr[1],".") == 0)
        {
            //do nothing
        }
        else if(strcmp(arr[1],"-") == 0)
        {
            check = chdir(lwd);
            if(check<0)
            {
                perror("Could not change directory");
                return(1);
            }
        }
        else
        {
            check = chdir(arr[1]);
            if(check<0)
            {
                perror("Could not change directory");
                return(1);
            }
        }
        strcpy(lwd,currcwd);
        return(0);
    }
}