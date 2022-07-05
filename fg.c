#include "headers.h"
#include "variables.h"
#include "intfunctions.h"

long long int powers (int num)
{
    long long int ans = 1;
    for(int i=0; i<num; i++)
        ans *= 10;
    return ans;
}

int fg()
{
    if(insize == 1)
    {
        int l = strlen(arr[1]);
        long long int num = 0;
        for(int i=0; i< l; i++)
        {
            num += (powers(l-1-i))*(arr[1][i] - '0');
        }
        //printf("%d\n",num);
        if(num > pos || num<=0)
        {
            printf("Invalid process number\n");
            return(1);
        }
        int j =0 ,k=0;
        while(j != num - 1)
        {
            if(status[k] == 0) j++;
            k++;
        }
        //printf("%d %d %s\n", k, pid[k], procname[k]);
        signal(SIGCHLD, SIG_IGN);
        int chk = kill(pid[k], SIGCONT);
        if(chk != 0)
        {
            perror("Kill error");
            return(1);
        }
        status[k] = 1;
        fg_stat = 1;
        fg_pid = pid[k];
        strcpy(fg_name, procname[k]);
        waitpid(-1, NULL, WUNTRACED);
        fg_stat = 0;
    }
    else
    {
        printf("Invalid number of arguments\n");
        return(1);
    }
    signal(SIGCHLD, proctrk);
    return (0);
}