#include "headers.h"
#include "variables.h"

int hismngr()
{
    char fpath[4098];
    strcpy(fpath, cwd);
    strcat(fpath, "/history.txt");
    FILE *his;
    FILE *swp;
    char buff[1010];
    char number[4];
    his = fopen(fpath, "r");
    swp = fopen("swap.txt" , "w");
    
    if(fgets(number, 4, his) == NULL)
    {
        printf("Invalid history.txt\n");
        return(1);
    }
    int ind;
    if(strlen(number) == 2)
    {
        ind = (number[0] - '0');
    }
    else
    {
        ind = (number[1] - '0') + (number[0] - '0')*10;
        if(ind == 20) ind = 0;
    }
    sprintf(number, "%d\n", ind+1);
    fputs(number, swp);
    int lnum = 0;
    
    while((fgets(buff, 1010, his)) != NULL)
    {
        lnum++;
        if(lnum == ind +1)
            fputs(input,swp);
        else
            fputs(buff, swp);
    }
    if(lnum != 20)
    {
        fputs(input, swp);
        if(lnum == 19) his_full = 1;
        else his_full = 0;
    }
    else
    {
        his_full = 1;
    }
    int chk;
    chk = fclose(his);
    if(chk != 0)
        perror("Close error");
    chk = fclose(swp);
    if(chk != 0)
        perror("Close error");
    chk = remove(fpath);
    if(chk == -1)
        perror("Remove");
    rename("swap.txt", fpath);
    return(0);
}
