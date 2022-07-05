#include "headers.h"
#include "variables.h"
#include "intfunctions.h"
#include <fcntl.h>
int flag;
void proctrk()
{
    while(1)
    {
        int cstatus;
        int i;
        pid_t id = waitpid(-1, &cstatus, WNOHANG);
        if(id <= 0) break;
        //printf("%d\n",id);
        for(i=0 ;i<100; i++)
        {
            if(pid[i] == id)
            {
                break;
            }  
        }
        if(WIFEXITED(cstatus))
        {
            fprintf(stderr,"\r%s with pid %d exited normally\n",procname[i],pid[i]);
            status[i] = 1;
            pos--;
        }
        else if(WIFSIGNALED(cstatus))
            fprintf(stderr,"\r%s with pid %d killed by signal %d\n",procname[i],pid[i],WTERMSIG(cstatus));
        else if(WIFSTOPPED(cstatus))
            fprintf(stderr,"\r%s with pid %d stopped by signal %d\n",procname[i],pid[i],WSTOPSIG(cstatus));
        else if(WIFCONTINUED(cstatus))
            fprintf(stderr,"\r%s with pid %d continued\n",procname[i],pid[i]);
        //printf("%s with pid %d exited normally\n",p_name,id);
        prompt();
        fflush(stdout);
        
    }

}

int main()
{
    if(getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("Current directory");
    }
    pos = 0;
    int chk = 0;
    strcpy(lwd, cwd);
    fg_stat = 0;
    flag = 0;
    ex_stat = -1;
    avapid = getpid();

    while (1)
    {
        signal(SIGCHLD, proctrk);
        signal(SIGINT, chandler);
        signal(SIGTSTP, zhandler);
        
        prompt();
        input = (char*) malloc(1000*sizeof(char));
        size_t inpsz = 800;
        int inputsz;
        inputsz = getline(&input, &inpsz, stdin);
        if(inputsz <= 0)
        {
            printf("quit\n");
            return 0;
        }
        chk = hismngr();
        if(chk != 0) printf("history manager error\n");
        token();
        for(curr_cmd = 0; curr_cmd <num_cmd; curr_cmd++)
        {
            cmdbrk();
           
            int bgrnd = 0;
            if(strcmp(toks[cmdsize], "&") == 0)
            {
                bgrnd = 1;
            }
            pid_t chid;
            if(strcmp(toks[0],"quit") == 0)
            {
                //printf("entered exit");
                return 0;
            }
            if(bgrnd == 0)
            {  
                
                int stdin = dup(0);
                int stdout = dup(1);   
                //implement pipes and redirection and use funlis()
                pipefind();
                if(num_pipes == 0)
                {
                    //printf("number of pipes = 0 and %d\n",insize);
                    insize = -1;
                   for(int i=0;i<=cmdsize;i++)
                   {
                        if(strcmp(toks[i],">") == 0)
                        {
                            char *fname = toks[i+1];
                            int fd = open(fname, O_CREAT|O_TRUNC|O_WRONLY, 0644);
                            if(fd == -1)
                            {
                                perror("Could not open file");
                                ex_stat = 1;
                            }
                            dup2(fd,STDOUT_FILENO);
                            close(fd);
                            i++;
                        }
                        else if(strcmp(toks[i],">>") == 0)
                        {
                            char *fname = toks[i+1];
                            int fd = open(fname, O_CREAT|O_WRONLY|O_APPEND, 0644);
                            if(fd == -1)
                            {
                                perror("Could not open file");
                                ex_stat = 1;
                            }
                            dup2(fd,STDOUT_FILENO);
                            close(fd);
                            i++;
                        }
                        else if(strcmp(toks[i],"<") == 0)
                        {
                            char *fname = toks[i+1];
                            int fd = open(fname, O_RDONLY);
                            if(fd < 0)
                            {
                                perror("Could not open file");
                                ex_stat = 1;
                            }
                            dup2(fd,STDIN_FILENO);
                            close(fd);
                            i++;
                        }
                        else
                        {
                            insize++;
                            arr[insize] = toks[i];
                        }
                    }
                    funlist();
                    dup2(stdin,STDIN_FILENO);
                    dup2(stdout,STDOUT_FILENO);    
                }
                else
                {
                    //printf("entered else\n");
                    int infd = 0, outfd = 1, curpip = 0;
                    for(int i=0;i<=num_pipes;i++)
                    {
                        /*if(i == pipe_loc[curpip])
                        {
                            curpip++;
                            continue;
                        }*/
                        int pfd[2];
                        pipe(pfd);
                        int chk = fork();
                        if(chk < 0)
                        {
                            perror("Fork error\n");
                            ex_stat = 1;
                        }
                        else if(chk == 0)
                        {
                            if(i==0)
                            {
                                insize = -1;
                                for(int j= 0;j<pipe_loc[0];j++)
                                {
                                    if(strcmp(toks[j],"<") == 0)
                                    {
                                        char *fname = toks[j+1];
                                        infd = open(fname, O_RDONLY);
                                        if(infd == -1)
                                        {
                                            perror("Could not open file");
                                            ex_stat = 1;
                                        }
                                        j++;
                                    }
                                    
                                    else
                                    {
                                        insize++;
                                        arr[insize] = toks[j];
                                    }
                                    
                                }
                            }
                            dup2(infd, STDIN_FILENO);
                            if(i==num_pipes)
                            {
                                insize = -1;
                                for(int j=pipe_loc[i - 1] +1;j<=cmdsize;j++)
                                {
                                    if(strcmp(toks[j],">") == 0)
                                    {
                                        char *fname = toks[j+1];
                                        int fd = open(fname, O_CREAT|O_TRUNC|O_WRONLY, 0644);
                                        if(fd == -1)
                                        {
                                            perror("Could not open file");
                                            ex_stat = 1;
                                        }
                                        dup2(fd,STDOUT_FILENO);
                                        
                                        j++;
                                    }
                                    else if(strcmp(toks[j],">>") == 0)
                                    {
                                        char *fname = toks[j+1];
                                        int fd = open(fname, O_CREAT|O_WRONLY|O_APPEND, 0644);
                                        if(fd == -1)
                                        {
                                            perror("Could not open file");
                                            ex_stat = 1;
                                        }
                                        dup2(fd,STDOUT_FILENO);
                                        
                                        j++;
                                    }
                                    else
                                    {
                                        insize++;
                                        arr[insize] = toks[j];
                                    }
                                }
                            }
                            else dup2(pfd[1],1);
                            close(pfd[0]);
                            if(i != 0 && i!= num_pipes)
                            {
                                insize=-1;
                                for(int j=pipe_loc[i - 1] + 1; j<pipe_loc[i]; j++)
                                {
                                    insize++;
                                    arr[insize] = toks[j];
                                }
                            }
                            funlist();
                            exit(1);
                        }
                        else
                        {
                            wait(NULL);
                            close(pfd[1]);
                            outfd = pfd[1];
                            infd = pfd[0];
                        }
                    }
                    dup2(stdin,STDIN_FILENO);
                    dup2(stdout,STDOUT_FILENO);
                }
            }    
            else
            {
                //printf("Enterd bg\n");
                chid = fork();
                if(chid < 0)
                {
                    perror("Fork error");
                    ex_stat =1;
                }
                else if(chid == 0)
                {
                    ex_stat = 0;
                    for(int i=0; i<cmdsize ;i++)
                    {
                        if(strcmp(toks[i],"<") == 0)
                        {
                            char *fname = toks[i+1];
                            int fd = open(fname, O_RDONLY);
                            if(fd == -1)
                            {
                                perror("Could not open file");
                                ex_stat = 1;
                            }
                            dup2(fd,STDIN_FILENO);
                            toks[i] = NULL;
                            toks[i+1] = NULL;
                        }
                        
                        if(strcmp(toks[i],">") == 0)
                        {
                            char *fname = toks[i+1];
                            int fd = open(fname, O_CREAT|O_TRUNC|O_WRONLY, 0644);
                            if(fd == -1)
                            {
                                perror("Could not open file");
                                ex_stat = 1;
                            }
                            dup2(fd,STDOUT_FILENO);
                            toks[i] = NULL;
                            toks[i+1] = NULL;
                        }
                        
                        if(strcmp(toks[i],">>") == 0)
                        {
                            char *fname = toks[i+1];
                            int fd = open(fname, O_CREAT|O_WRONLY|O_APPEND, 0644);
                            if(fd == -1)
                            {
                                perror("Could not open file");
                                ex_stat = 1;
                            }
                            dup2(fd,STDOUT_FILENO);
                            toks[i] = NULL;
                            toks[i+1] = NULL;
                        }
                    }
                    setpgid(0,0);
                    toks[cmdsize] = NULL;
                    int chk = execvp(toks[0], toks);
                    if(chk == -1)
                    {
                        printf("Command Not found");
                        ex_stat = 1;
                    }
                }
                pid[pos] = chid;
                procname[pos] = malloc(150*sizeof(char));
                strcpy(procname[pos], toks[0]);
                status[pos] = 0;
                pos++;
                printf("%d\n",chid);
            }
        }
        
    }
    return 0;
}
