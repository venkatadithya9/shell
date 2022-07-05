#include "headers.h"
#include "variables.h"

int prompt() {

    struct utsname name;
    char* u_name = getenv("USERNAME");
    char currcwd[4097];
    if(getcwd(currcwd, sizeof(currcwd)) == NULL)
    {
        perror("Current directory not found");
        return(1);
    }
    uname(&name);
    int x = strcmp(cwd,currcwd);
    if(x == 0)
    {
        if(ex_stat == -1) printf("<%s@%s:~>", u_name,name.sysname);
        else if(ex_stat == 0) printf(":`)<%s@%s:~>", u_name,name.sysname);
        else if(ex_stat == 1) printf(":`(<%s@%s:~>", u_name,name.sysname);
    }
    else if(x < 0)
    {
        int len = strlen(cwd);
        if(ex_stat == 0) printf(":`)<%s@%s:~%s>", u_name,name.sysname,currcwd + len);
        else if(ex_stat == 1) printf(":`(<%s@%s:~%s>", u_name,name.sysname,currcwd + len);
    }
    else
    {
        if(ex_stat == 0) printf(":`)<%s@%s:%s>", u_name,name.sysname,currcwd);
        else if(ex_stat == 1) printf(":`(<%s@%s:%s>", u_name,name.sysname,currcwd);
    }
    return(0);
}
