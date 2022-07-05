#include "headers.h"
#include "variables.h"

void chandler() // ;)
{
    //fprintf(stderr," fg status = %d", fg_stat);
    if(fg_stat == 1)
    {
        int chk = kill(fg_pid, SIGINT);
        if(chk < 0)
        {
            perror("Kill error");
            return;
        }
        fg_stat = 0;
    }
    signal(SIGINT, chandler);
}

void zhandler()
{
    if(fg_stat == 1)
    {
        int chk = kill(fg_pid, SIGTTIN);
        if(chk < 0)
        {
            perror("Kill error");
            return;
        }
        chk = kill(fg_pid, SIGTSTP);
        if(chk < 0)
        {
            perror("Kill error");
            return;
        }
        fg_stat = 0;
        pid[pos] = fg_pid;
        status[pos] = 0;
        procname[pos] = malloc(150*sizeof(char));
        strcpy(procname[pos], fg_name);
        pos++;
        ex_stat = 1;
    }
    signal(SIGTSTP, zhandler);
}