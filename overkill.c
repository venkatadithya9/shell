#include "headers.h"
#include "variables.h"

int overkill()
{
    for(int i=0; i<pos; i++)
    {
        if(status[i] == 0)
        {
            int chk = kill(pid[i], SIGKILL);
            if(chk != 0)
            {
                perror("Kill error");
                return(1);
            }
        }
    }
    return(0);
}