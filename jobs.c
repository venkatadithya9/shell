#include "headers.h"
#include "variables.h"

int jobs()
{
    if(insize == 0)
    {
        int j =0;
        for(int i=0; i<pos ;i++)
        {
            if(status[i] == 0)
            {
                printf("entered\n");
                char str[50];
                j++;
                char* f_name = (char *)malloc(100*sizeof(char));
                char init[] = "/proc/";
                char st[] ="/stat";
                sprintf(f_name, "%s%d%s", init, pid[i], st);
                FILE *fd = fopen(f_name, "r");
                if(fd ==NULL)
                {
                    perror("File open error");
                    return(1);
                }      

                char p_state[2];
                fscanf(fd, "%*d%*s%s", p_state);
                
                strcpy(str, "Running");
                if(p_state[0] == 'T') strcpy(str, "Stopped");


                printf("[%d] %s %s [%d]\n",j,str,procname[i], pid[i]);
                        
            }
        }   
    }   
    else
    {
        printf("Invalid number of arguments\n");
        return(1);
    }
    
    return(0);
}