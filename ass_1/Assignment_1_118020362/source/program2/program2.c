#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kthread.h>
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/printk.h>
#include <linux/jiffies.h>
#include <linux/kmod.h>
#include <linux/fs.h>
#include <linux/pid.h>

MODULE_LICENSE("GPL");

struct wait_opts{
   enum pid_type wo_type;
   int wo_flags;
   struct pid * wo_pid;
   struct siginfo __user * wo_info;
   int __user * wo_stat;
   struct rusage __user * wo_rusage;
   wait_queue_t child_wait;
   int notask_error;


};


extern int do_execve(struct filename *filename,
        const char __user *const __user *__argv,
        const char __user *const __user *__envp);
extern struct filename * getname(const char __user * filename);
extern long do_wait(struct wait_opts *wo);
extern long _do_fork(unsigned long clone_flags,
              unsigned long stack_start,
              unsigned long stack_size,
              int __user *parent_tidptr,
              int __user *child_tidptr,
              unsigned long tls);

static struct task_struct * task;

int my_exec(void){
    int result;
    const char path[]="/home/seed/work/assignment1/source/program2/test";
    const char *const argv[]={path,NULL,NULL};
    const char *const envp[]={"HOME=/","PATH=/sbin:/user/sbin:/bin:/usr/bin",NULL};
    struct filename * my_filename=getname(path);
  
    result=do_execve(my_filename,argv,envp);
    if(!result){
       return 0;
    }
    do_exit(result);

}


void my_wait(long pid){
   int a;
   int status;
   struct wait_opts wo;
   struct pid * wo_pid=NULL;
   enum pid_type type;
   type=PIDTYPE_PID;
   wo_pid=find_get_pid(pid);

   wo.wo_type=type;
   wo.wo_pid=wo_pid;
   wo.wo_flags=WUNTRACED|WEXITED;
   wo.wo_info=NULL;
   wo.wo_stat=(int __user*)&status;
   wo.wo_rusage=NULL;

   a=do_wait(&wo);
   printk("[program2] : child process\n");
   
   if(*wo.wo_stat==9){
      printk("[program2] : get SIGKILL signal\n");
      printk("[program2] : child process has kill error\n");
      printk("[program2] : The return signal is 9\n");
   }
   else if(*wo.wo_stat==6){
     printk("[program2] : get SIGABRT signal\n");
      printk("[program2] : child process has abort error\n");
      printk("[program2] : The return signal is 6\n");

   }
   else if(*wo.wo_stat==14){
     printk("[program2] : get SIGALRM signal\n");
      printk("[program2] : child process has alarm error\n");
      printk("[program2] : The return signal is 14\n");

   }
   else if(*wo.wo_stat==7){
     printk("[program2] : get SIGBUS signal\n");
      printk("[program2] : child process has bus error\n");
      printk("[program2] : The return signal is 7\n");

   }
   else if(*wo.wo_stat==8){
     printk("[program2] : get SIGFPE signal\n");
      printk("[program2] : child process has floating error\n");
      printk("[program2] : The return signal is 8\n");

   }
   else if(*wo.wo_stat==1){
     printk("[program2] : get SIGHUP signal\n");
      printk("[program2] : child process has hangup error\n");
      printk("[program2] : The return signal is 1\n");

   }
   else if(*wo.wo_stat==4){
     printk("[program2] : get SIGILL signal\n");
      printk("[program2] : child process has illegal_instr error\n");
      printk("[program2] : The return signal is 4\n");

   }
   else if(*wo.wo_stat==2){
     printk("[program2] : get SIGINT signal\n");
      printk("[program2] : child process has interrupt error\n");
      printk("[program2] : The return signal is 2\n");

   }
   else if(*wo.wo_stat==13){
     printk("[program2] : get SIGPIPE signal\n");
      printk("[program2] : child process has pipe error\n");
      printk("[program2] : The return signal is 13\n");

   }
   else if(*wo.wo_stat==3){
     printk("[program2] : get SIGQUIT signal\n");
      printk("[program2] : child process has quit error\n");
      printk("[program2] : The return signal is 3\n");

   }
   else if(*wo.wo_stat==11) {
     printk("[program2] : get SIGSEGV signal\n");
      printk("[program2] : child process has sefment_fault error\n");
      printk("[program2] : The return signal is 11\n");

   }
   else if(*wo.wo_stat==15){
     printk("[program2] : get SIGTERM signal\n");
      printk("[program2] : child process has termination error\n");
      printk("[program2] : The return signal is 15\n");

   }
   else if(*wo.wo_stat==5){
     printk("[program2] : get SIGTRAP signal\n");
      printk("[program2] : child process has trap error\n");
      printk("[program2] : The return signal is 5\n");

   }
   else if(*wo.wo_stat==4991){
     printk("[program2] : get SIGSTOP signal\n");
      printk("[program2] : child process has stop error\n");
      printk("[program2] : The return signal is 19\n");

   }
   else if(*wo.wo_stat==0){
     printk("[program2] : get no signal\n");
      printk("[program2] : child process exit normally\n");
      printk("[program2] : The return signal is 0\n");

   }


  
   put_pid(wo_pid);


}

//implement fork function
int my_fork(void *argc){
	
	
	//set default sigaction for current process
	int i;
        long pid;
       
      
 
	struct k_sigaction *k_action = &current->sighand->action[0];
	for(i=0;i<_NSIG;i++){
		k_action->sa.sa_handler = SIG_DFL;
		k_action->sa.sa_flags = 0;
		k_action->sa.sa_restorer = NULL;
		sigemptyset(&k_action->sa.sa_mask);
		k_action++;
	}
	
	/* fork a process using do_fork */
	
        pid=_do_fork(SIGCHLD,(unsigned long)&my_exec,0,NULL,NULL,0);
        printk("[program2] : The child process has pid = %ld\n",pid);       
        printk("[program2] : This is the parent process, pid = %d\n",(int)current->pid);
      
        my_wait(pid);
	/* execute a test program in child process */
	
	/* wait until child process terminates */
	
	return 0;
}

static int __init program2_init(void){

	printk("[program2] : Module_init\n");
	
	/* write your code here */
	
	/* create a kernel thread to run my_fork */
	printk("[program2] : module_init create kthread start\n");
        task=kthread_create(&my_fork,NULL,"My Thread");
        
        if(!IS_ERR(task)){
            printk("[program2] : module_init kthread start\n");
            wake_up_process(task);
        }
	return 0;
}

static void __exit program2_exit(void){
	printk("[program2] : Module_exit\n");
}

module_init(program2_init);
module_exit(program2_exit);
