#include "headers.h"
#include "variables.h"
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
/*
0 -> ls
1 -> ls -l
2 -> ls -a
3 -> ls -al
*/
int blk_sz;
char *listview(char *path)
{
    //printf("Entered listview");
    struct stat sbuff;
    int chk = stat(path, &sbuff);
    if(chk != 0) perror("Stat error");
    //block size
    blk_sz += sbuff.st_blocks;
    //Permissions for one file in the directory -> prmsns
    char prmsns[] = "----------";
    mode_t x = sbuff.st_mode;
    if(S_ISDIR(x)) prmsns[0] = 'd';
    if(S_IRUSR & x) prmsns[1] = 'r';
    if(S_IWUSR & x) prmsns[2] = 'w';
    if(S_IXUSR & x) prmsns[3] = 'x';

    if(S_IRGRP & x) prmsns[4] = 'r';
    if(S_IWGRP & x) prmsns[5] = 'w';
    if(S_IXGRP & x) prmsns[6] = 'x';

    if(S_IROTH & x) prmsns[7] = 'r';
    if(S_IWOTH & x) prmsns[8] = 'w';
    if(S_IXOTH & x) prmsns[9] = 'x';
              
    //Number of links -> link
    int link;
    link = sbuff.st_nlink;

    //username and groupname -> usgr
    struct passwd *usr = getpwuid(sbuff.st_uid);
    if(usr == NULL) perror("User Name error");
    struct group *grp = getgrgid(sbuff.st_gid);
    if(grp == NULL) perror("Group Name error");
    char usgr[strlen(usr->pw_name) + strlen(grp->gr_name) + 3];
    sprintf(usgr, "%s %s", usr->pw_name, grp->gr_name);

    //file size -> fsz
    int fsz = sbuff.st_size;

    //time -> time
    struct tm *tminfo;
    char time[35];

    tminfo = localtime(&(sbuff.st_mtime));
    strftime(time, sizeof(time), "%h %e %H:%M", tminfo);

    char *fin = (char*)malloc(300*sizeof(char));
    sprintf(fin, "%s %d %s %d %s", prmsns, link, usgr, fsz, time);
    return fin;
}

int cmp(const struct dirent** a, const struct dirent** b) {
    return strcasecmp((*b)->d_name,
            (*a)->d_name);
}

int filter(const struct dirent * dir) {
    char *s = (char *)dir->d_name;
    if (s[0] == '.')
        return 0;
    return 1;
}

int ls()
{
    //printf("Entered ls %d\n", insize);
    int type = 0, flag = 1;
    int dirchk = 0;
    char *dirs[10];
    blk_sz = 0;

    char currcwd[4097];
    //printf("point -1");
    if(getcwd(currcwd, sizeof(currcwd)) == NULL)
    {
        perror("Current directory");
    }
    //printf("point 0");
    int j;
    for( j= strlen(currcwd) -1; j>0; j--)
    {
        if(currcwd[j] == '/') break;
    }
    char prevwd[4097];
    //printf("point 1");
    strncpy(prevwd, currcwd, j);
    //printf("point 2");
    if(insize == 0)
    {
        type = 0;
        dirchk = 0;
    }
    else
    { 
        for(int i=1; i<= insize; i++)
        {
            if(strcmp(arr[i], "-l") == 0)
            {
                if(type == 0 || type == 2) type++;
            }
            else if(strcmp(arr[i], "-a") == 0)
            {
                if(type == 0 || type == 1) type += 2;
            }
            else if (strcmp(arr[i], "-al") == 0 || strcmp(arr[i], "-la") == 0)
            {
                type  = 3;
            }
            else
            {
                
                if(strcmp(arr[i], "&") != 0)
                {
                    if(dirchk<10)
                    {
                        if(strcmp(arr[i],".") == 0)
                            dirs[dirchk] = currcwd;
                        else if(strcmp(arr[i],"..") == 0)
                            dirs[dirchk] = prevwd;
                        else if(strcmp(arr[i], "~") == 0)
                            dirs[dirchk] = cwd;
                        else
                        {
                            dirs[dirchk] = arr[i];
                        }
                        
                        dirchk ++;
                    }
                }
            }
        }
    }
    //printf("%d %d\n", type, dirchk);
    //for(int i=0; i<dirchk; i++) printf("%s\n",dirs[i]);
    
    if(dirchk == 0)
    {
        struct dirent *dirinfo;
        if(type == 0)
        {
            DIR *dirstr = opendir(currcwd);
            if(dirstr == NULL)
            {
                perror("Could not open directory");
                return(1);;
                
            }
            while((dirinfo = readdir(dirstr)) != NULL)
                if(dirinfo->d_name[0] != '.')
                    printf("%s ",dirinfo->d_name);
            printf("\n");
            //closedir(dirstr);
        }
        else
        {
            dirs[0] = currcwd;
            dirchk++;
            flag = 0;
            //implement scandir, filters and comparators and for loop with print function for multiple directories
        }
        
    }
    //printf("%d %d\n", type, dirchk);

    if(dirchk >0)
    {
        //printf("Entered\n");
        for(int i=0; i<dirchk; i++)
        {
           
            if(dirchk > 1)printf("%s:\n", dirs[i]);

            if(type == 0)
            {
                struct dirent *dirinfo;
                DIR *dirstr = opendir(dirs[i]);
                if(dirstr == NULL)
                {
                    perror("Could not open directory");
                    return(1);;
                }
                while((dirinfo = readdir(dirstr)) != NULL)
                    if(dirinfo->d_name[0] != '.')
                        printf("%s ",dirinfo->d_name);
                printf("\n");
                //closedir(dirstr);
            }

            if(type == 2)
            {
                //printf("Entered -a");
                struct dirent *dirinfo;
                DIR *dirstr = opendir(dirs[i]);
                if(dirstr == NULL)
                {
                    perror("Could not open directory");
                    return(1);;
                }
                while((dirinfo = readdir(dirstr)) != NULL)
                    printf("%s ",dirinfo->d_name);
                printf("\n");
                //closedir(dirstr);
            }

            if(type == 1 || type == 3)
            {
                //perror("check");
                //printf("Entered -l");
                struct dirent **dirinfo;
                int tot;
                if(type == 1)
                {
                    tot = scandir(dirs[i], &dirinfo, &filter, &cmp);
                    if(tot == -1)
                    {
                        perror("Could not open directory");
                        return(1);;
                    }
                    //perror("-l");
                }
                if(type == 3)
                {
                    tot = scandir(dirs[i], &dirinfo, 0, &cmp);
                    if(tot == -1)
                    {
                        perror("Could not open directory");
                        return(1);;
                    }
                }
                //perror("Scandir done");
                //printf("%s", dirs[i]);
                char *fin_string[tot];
                int tut = tot;
                while(tot>0)
                {
                    char *path = (char *)malloc(500*sizeof(char));
                    //char *parent_path = (char *)malloc(300*sizeof(char));
                    if(dirs[i][0] != '/')
                    {
                        strcpy(path, currcwd);
                        strcat(path, "/");
                        strcat(path, dirs[i]);
                        //strcpy(parent_path, path);
                        strcat(path, "/");
                        strcat(path, dirinfo[(tot - 1)]->d_name);
                    }
                   
                    else
                    {
                        strcpy(path, dirs[i]);
                        strcat(path, "/");
                        strcat(path, dirinfo[(tot -1)]->d_name);
                    }
                    //printf("%s\n", path);
                    char *final = listview(path);
                    //perror("listview");
                    fin_string[tot-1] = (char *)malloc(500*sizeof(char));
                    sprintf(fin_string[tot-1],"%s %s\n", final, dirinfo[(tot -1)] -> d_name );
                    tot--;
                }
                printf("total %d\n",blk_sz/2);
                for(int i=0; i<tut; i++) printf("%s", fin_string[i]);
            }
        }
    }
    return(0);
}