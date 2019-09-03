
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
//extern char **environ;		/* environment info */


main(int argc, char **argv)
     /* argc -- number of arguments */
     /* argv -- an array of strings */ 
{
    char *argvNew[argc];
    int pid;
    struct rusage usage;
    struct timezone tzone;
    double intime = 0;
    double nexttime;
    struct timeval time;
    gettimeofday(&time,&tzone);
    intime = ((double) time.tv_sec *(double)1000) + ((double) time.tv_usec / (double)100);
    char *str;
    char *fcom;
    char input[128];
    char* delim = " ";
    char* prompt = "==>";
    char* promptselect[35];
 while(1) {
  

  printf("%s",prompt);
  scanf(" %[^\n]s",input);
  str = strtok(input,delim);
  fcom = str;
  int v=0;
 if (strcmp("exit",input) == 0){
	exit(1);
}



 else if(strcmp(str,"set") == 0){
	promptselect[0]= str;
 while(str != NULL){
        str = strtok(NULL,delim);
        promptselect[++v]= str;
}
	if( (strcmp("prompt",promptselect[1])== 0) && (strcmp("=",promptselect[2]) == 0)) 
	prompt= promptselect[3];
}

 else if(strcmp("cd",str) == 0){
	str = strtok(NULL,delim);
	if( str == NULL){
	chdir("~/");	 
        }
	else{ 
	chdir(str);
	}
}
else {

char *command [35];
int inum=0;
command[0]= fcom;
 while(str != NULL){
	str = strtok(NULL,delim);
	command[++inum]= str;  	
}
 if ((pid = fork()) < 0) {
        fprintf(stderr, "Fork error\n");
        exit(1);
    
 }
 
    else if (pid == 0) {
        /* child process */     
        if (execvp(command[0], command) < 0) {
            fprintf(stderr, "Execve error\n");
            exit(1);
        }
	
    }
    else {
        /* parent */
	wait(0);
	gettimeofday(&time,&tzone);
        nexttime = ((double) time.tv_sec *(double)1000) + ((double) time.tv_usec / (double)100);
	getrusage( RUSAGE_CHILDREN,&usage);
        
	printf("User CPU time %f\n", ((double) usage.ru_utime.tv_sec *(double)1000) + ((double)usage.ru_utime.tv_usec /(double) 100));		/* wait for the child to finish */
	printf("System  CPU time %f\n", ((double) usage.ru_stime.tv_sec *(double)1000) + ((double)usage.ru_stime.tv_usec /(double) 100));    
 	printf("The total time that process took was %f\n",nexttime-intime);
	printf("Involuntarily context switches: %lu\n",usage.ru_nivcsw);
	printf("Voluntarily context switches: %lu\n", usage.ru_nvcsw);
	printf("Major page faults: %lu\n",usage.ru_majflt);
	printf("Minor page faults: %lu\n",usage.ru_minflt);
 
	};
	
	}

	}}
