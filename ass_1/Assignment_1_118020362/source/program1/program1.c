#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>


int main (int argc, char *argv[]) {
    
    int state;
    pid_t pid = fork();
    
    if (pid < 0) {
        printf ("Fork error!\n");
    }
    else {
        
        //Child process
        if (pid == 0) {
            
            int i;
            char *arg[argc];
            
            printf("I am the child process, my pid is %d\n",getpid());
            
            for(i=0;i<argc-1;i++){
                arg[i]=argv[i+1];
            }
            arg[argc-1]=NULL;
            
	    
            printf("Child process start to execute test program:\n");
            execve(arg[0],arg,NULL);
            
            printf("Continue to run original child process!\n");
            
            perror("execve");
            exit(EXIT_FAILURE);
        }
        
        //Parent process
        else{
            //wait(&state);
            printf("I am the parent process, mypid is %d\n",getpid());
         
            waitpid(pid,&state,WUNTRACED);
            
            printf("Parent process receiving the SIGCHLD signal.\n");
            if(WIFEXITED(state)){
               printf("Normal termination with EXIT STATUS = %d\n", WEXITSTATUS(state));
               
            
            }
            else if(WIFSIGNALED(state)){
               int signal=WTERMSIG(state);
               if(signal==9){
                   printf("child process get SIGKILL signal.\n");
                   printf("child process is killed by kill signal.\n");
    
               }
               else if(signal==6){
                   printf("child process get SIGABRT signal.\n");
                   printf("child process is abort by abort signl.\n");
               }
               else if(signal==14){
                   printf("child process get SIGALRM signal.\n");
                   printf("child process is alarmed by alarm signal.\n");
   
               }
               else if(signal==7){
                    printf("child process get SIGBUS signal.\nchild process is terminated by bus signal.\n");
               }
               else if(signal==8){
                    printf("child process get SIGFPE signal.\nchild process is terminated by floating signal.\n");
               }
               else if(signal==1){
                    printf("child process get SIGHUP signal.\nchild process is terminated by hangup signal.\n");
               }
               else if(signal==4){
                    printf("child process get SIGILL signal.\nchild process is terminated by illegal_instr signal.\n");
               }
               else if(signal==2){

                    printf("child process get SIGINT signal.\nchild process is terminated by interrupt signal.\n");
               }
               else if(signal==13){
                    printf("child process get SIGPIPE signal.\nchild process is terminated by pipe signal.\n");
               }
               else if(signal==3){
                    printf("child process get SIGQUIT signal.\nchild process is terminated by quit signal.\n");
               }
               else if(signal==11){
                    printf("child process get SIGSEGV signal.\nchild process is terminated by segment_fault signal.\n");
               }
               else if(signal==15){
                    printf("child process get SIGTERM signal.\nchild process is terminated by terminate signal.\n");
               }
               else if(signal==5){
                    printf("child process get SIGTRAP signal.\nchild process is terminated by trap signal.\n");
               }
          
               
               printf("CHILD EXECUTION FAILED!!\n");  
            }
            else if(WIFSTOPPED(state)){
               printf("child process get SIGSTOP signal.\nchild process stopped.\n");
               printf("CHILD PROCESS STOPPED.\n"); 

            }
            exit(1);
        }
    }
    
    return 0;
}
