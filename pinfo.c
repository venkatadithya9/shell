#include "headers.h"
#include "variables.h"

#include <fcntl.h>
int pinfo()
{
    char* f_name = (char *)malloc(100*sizeof(char));
    char init[] = "/proc/";
    char st[] ="/stat";
    char ex[] = "exe";
    if(insize == 0)
    {
        pid_t id = getpid();
        sprintf(f_name, "%s%d%s", init, id, st);
        printf("pid -- %d\n",id);
    }
    else 
    {
        char *id = arr[1];
        sprintf(f_name, "%s%s%s", init, id, st);
        printf("pid -- %s\n",id);
    }
    FILE *fd = fopen(f_name, "r");
    //printf("%s", f_name);
    if(fd ==NULL)
    {
        perror("File open error");
        return(1);
    }      

    char p_state[2];
    long unsigned int sz;
    fscanf(fd, "%*d%*s%s%*d%*d%*d%*d%*d%*u%*u%*u%*u%*u%*u%*u%*d%*d%*d%*d%*d%*d%*u%lu", p_state, &sz);

    char *exf_name = (char *)malloc(100*sizeof(char));
    strncpy(exf_name, f_name, strlen(f_name) - 4);
    strcat(exf_name, ex);

    char *ex_name = (char*)malloc(500*sizeof(char));
    int chk = readlink(exf_name, ex_name, 490);
    if(chk < 0)
    {
        perror("readlink error");
        return(1);
    }
    ex_name[chk] = '\0';
    printf("Process status -- %s\n", p_state);
    printf("memory -- %lu\n",sz);
    printf("Executable Path -- %s\n", ex_name);
    return(0);
}