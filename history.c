#include "headers.h"
#include "variables.h"


void history()
{
    int len, chk;
    if (insize == 0) len = 10;
    else
    {
        if(strlen(arr[1]) == 1)
        {
            len = (arr[1][0] - '0');
        }
        else
        {
            len = (arr[1][1] - '0') + (arr[1][0] - '0')*10;
        }
        //printf("%d",len);
    }
    
    char fpath[4098];
    strcpy(fpath, cwd);
    strcat(fpath, "/history.txt");
    FILE *his;
    his = fopen(fpath, "r");
    char number[4];
    fgets(number, 4, his);
    int ind;
    if(strlen(number) == 2)
    {
        ind = (number[0] - '0');
    }
    else
    {
        ind = (number[1] - '0') + (number[0] - '0')*10;
    }
    //printf(" %d",ind);
    char *stor[20];
    int max;
    if(his_full)
    {
        max = 20;
    }
    else
    {
        max = ind;
    }
    //printf("%d\n",max);
    for(int i=0; i<max; i++)
    {
        stor[i] = malloc(1010*sizeof(char));
        fgets(stor[i], 1010, his);
        //printf("%s\n",stor[i]);
    }
    
    int comp = 0;

    /*for(int i=0; i< max; i++)
        printf("%s", stor[i]);
    */
    if(ind - len >= 0)
    {
        for(int i=(len); i>0 ;i--)
        {
            printf("%s",stor[ind - i]);
        }
    }
    else
    {
        if(his_full == 0)
        {
            for(int i=0; i<max; i++)
                printf("%s",stor[i]);
        }
        else
        {
            for(int i=(ind-len+20); i<20; i++)
            {
                printf("%s",stor[i]);
                if(i == 19) i = -1;
                comp++;
                if(comp == len) break;
            }
        }
        
    }
 
}