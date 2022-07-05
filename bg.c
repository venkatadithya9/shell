#include "headers.h"
#include "variables.h"

long long int power (int num)
{
    long long int ans = 1;
    for(int i=0; i<num; i++)
        ans *= 10;
    return ans;
}

int bg()
{
    if(insize == 1)
    {
        int l = strlen(arr[1]),chk;
        long long int num = 0;
        for(int i=0; i< l; i++)
        {
            num += (power(l-1-i))*(arr[1][i] - '0');
        }
        if(num > pos || num<=0)
        {
            printf("Invalid process number\n");
            return(1);
        }
        int j =0, k=0;
        while(j != num)
        {
            if(status[k] == 0) j++;
            k++;
        }
        chk = kill(pid[k], SIGTTIN);
        if(chk != 0)
        {
            perror("Kill error");
        }
        chk = kill(pid[k], SIGCONT);
        if(chk != 0)
        {
            perror("Kill error");
        }
    }
    else
    {
        printf("Invalid number of arguments\n");
        return(1);
    }
    
    return (0);
}