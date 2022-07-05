#include "intfunctions.h"
#include "variables.h"
#include "headers.h"

int funlist()
{
    int chk;
    if(strcmp(arr[0],"echo") == 0)
    {
        ex_stat = 0;
        //printf("Entered echo\n");
        chk = echo();
        if(chk != 0) ex_stat = 1;
    }
    else if(strcmp(arr[0],"cd") == 0)
    {
        ex_stat = 0;
        chk = cd();
        if(chk != 0) ex_stat = 1;
    }
    else if(strcmp(arr[0],"pwd") == 0)
    {
        //printf("entered pwd");
        char currcwd[4097];
        ex_stat = 0;
        if(getcwd(currcwd, sizeof(currcwd)) == NULL)
        {
            perror("Current directory");
            ex_stat = 1;
        }
        printf("%s\n", cwd);
    }
    else if(strcmp(arr[0],"ls") == 0)
    {
        ex_stat = 0;
        chk = ls();
        if(chk != 0) ex_stat = 1;
    }
    else if(strcmp(arr[0],"pinfo") == 0)
    {
        ex_stat = 0;
        chk = pinfo();
        if(chk != 0) ex_stat = 1;                  
    }
    else if(strcmp(arr[0],"history") == 0)
    {
        ex_stat = 0;
        history();
    }
    else if(strcmp(arr[0],"setenv") == 0)
    {
        ex_stat = 0;
        chk = stenv();
        if(chk != 0) ex_stat = 1;
    }
    else if(strcmp(arr[0],"unsetenv") == 0)
    {
        ex_stat = 0;
        chk = unstenv();
        if(chk != 0) ex_stat = 1;
    }
    else if(strcmp(arr[0],"jobs") == 0)
    {
        ex_stat = 0;
        chk = jobs();
        if(chk != 0) ex_stat = 1;
    }
    else if(strcmp(arr[0],"kjob") == 0)
    {
        ex_stat = 0;
        chk = kjob();
        if(chk != 0) ex_stat = 1;
    }
    else if(strcmp(arr[0], "overkill") == 0)
    {
        ex_stat = 0;
        chk = overkill();
        if(chk != 0) ex_stat = 1;
    }
    else if(strcmp(arr[0], "fg") == 0)
    {
        ex_stat = 0;
        chk = fg();
        if(chk != 0) ex_stat = 1;
    }
    else if(strcmp(arr[0], "bg") == 0)
    {
        ex_stat = 0;
        chk = bg();
        if(chk != 0) ex_stat = 1;
    }
    else
    {
        int f_pid = fork();
        if(f_pid < 0) ex_stat = 1;
        if( f_pid != 0)
        {
            fg_pid = f_pid;
            fg_stat = 1;
            strcpy(fg_name, arr[0]);
            waitpid(-1, NULL, WUNTRACED);
            fg_stat = 0;
        }
        else
        {
            arr[insize + 1] = NULL;
            ex_stat = 0;
            int chk = execvp(arr[0], arr);
            if(chk == -1)
            {
                printf("Command Not found\n");
                ex_stat = 1;
            }
            exit(0);
        }
    }
    return(0);
    }