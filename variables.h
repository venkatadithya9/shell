#ifndef __VARIABLES_H
#define __VARIABLES_H

char* input ;
char *toks[200];
char *arr[100];
char *cmd[100];
char cwd[4097];
char lwd[4097];
int curr_cmd;
int insize;
int cmdsize;
int num_cmd;
int his_full;
int pid[100];
char *procname[100];
int status[100];
int pos;
int num_pipes;
int pipe_loc[100];
int fg_stat;
int fg_pid;
char fg_name[200];
int avapid;
int ex_stat;
#endif