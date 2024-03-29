#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/fs.h>
#include <linux/workqueue.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include "ioc_hw5.h"

MODULE_LICENSE("GPL");




// DMA
#define DMA_BUFSIZE 64
#define DMASTUIDADDR 0x0        // Student ID
#define DMARWOKADDR 0x4         // RW function complete
#define DMAIOCOKADDR 0x8        // ioctl function complete
#define DMAIRQOKADDR 0xc        // ISR function complete
#define DMACOUNTADDR 0x10       // interrupt count function complete
#define DMAANSADDR 0x14         // Computation answer
#define DMAREADABLEADDR 0x18    // READABLE variable for synchronize
#define DMABLOCKADDR 0x1c       // Blocking or non-blocking IO
#define DMAOPCODEADDR 0x20      // data.a opcode
#define DMAOPERANDBADDR 0x21    // data.b operand1
#define DMAOPERANDCADDR 0x25    // data.c operand2
void *dma_buf;

// Declaration for file operations
static ssize_t drv_read(struct file *filp, char __user *buffer, size_t, loff_t*);
static int drv_open(struct inode*, struct file*);
static ssize_t drv_write(struct file *filp, const char __user *buffer, size_t, loff_t*);
static int drv_release(struct inode*, struct file*);
static long drv_ioctl(struct file *, unsigned int , unsigned long );

// cdev file_operations
static struct file_operations fops = {
      owner: THIS_MODULE,
      read: drv_read,
      write: drv_write,
      unlocked_ioctl: drv_ioctl,
      open: drv_open,
      release: drv_release,
};

// in and out function
void myoutc(unsigned char data,unsigned short int port);
void myouts(unsigned short data,unsigned short int port);
void myouti(unsigned int data,unsigned short int port);
unsigned char myinc(unsigned short int port);
unsigned short myins(unsigned short int port);
unsigned int myini(unsigned short int port);

// Work routine
static struct work_struct *work_routine;
#define DEV_NAME "mydev"        // name for alloc_chrdev_region
#define DEV_BASEMINOR 0         // baseminor for alloc_chrdev_region
#define DEV_COUNT 1             // count for alloc_chrdev_region
static int dev_major;
static int dev_minor;
static struct cdev *dev_cdev;


// For input data structure
struct DataIn {
    char a;
    int b;
    short c;
} *dataIn;


// Arithmetic funciton
static void drv_arithmetic_routine(struct work_struct* ws);


// Input and output data from/to DMA
void myoutc(unsigned char data,unsigned short int port) {
    *(volatile unsigned char*)(dma_buf+port) = data;
}
void myouts(unsigned short data,unsigned short int port) {
    *(volatile unsigned short*)(dma_buf+port) = data;
}
void myouti(unsigned int data,unsigned short int port) {
    *(volatile unsigned int*)(dma_buf+port) = data;
}
unsigned char myinc(unsigned short int port) {
    return *(volatile unsigned char*)(dma_buf+port);
}
unsigned short myins(unsigned short int port) {
    return *(volatile unsigned short*)(dma_buf+port);
}
unsigned int myini(unsigned short int port) {
    return *(volatile unsigned int*)(dma_buf+port);
}

int prime(int base, short nth)
{
    int fnd=0;
    int i, num, isPrime;

    num = base;
    while(fnd != nth) {
        isPrime=1;
        num++;
        for(i=2;i<=num/2;i++) {
            if(num%i == 0) {
                isPrime=0;
                break;
            }
        }
        
        if(isPrime) {
            fnd++;
        }
    }
    return num;
}

static int drv_open(struct inode* ii, struct file* ff) {
	try_module_get(THIS_MODULE);
    	printk("%s:%s(): device open\n", PREFIX_TITLE, __func__);
	return 0;
}
static int drv_release(struct inode* ii, struct file* ff) {
	module_put(THIS_MODULE);
    	printk("%s:%s(): device close\n", PREFIX_TITLE, __func__);
	return 0;
}
static ssize_t drv_read(struct file *filp, char __user *buffer, size_t ss, loff_t* lo) {
	/* Implement read operation for your device */
  
  
    int ans=myini(DMAANSADDR);
    
    put_user(ans, (int *)buffer);
    printk("%s:%s():ans is %d\n",PREFIX_TITLE,__func__,ans);
    myouti(0,DMAANSADDR);
    myouti(0,DMAREADABLEADDR);
    

	  return 0;
}
static ssize_t drv_write(struct file *filp, const char __user *buffer, size_t ss, loff_t* lo) {
	/* Implement write operation for your device */
  int IOMode;
  
  struct DataIn * data=kmalloc(ss,GFP_KERNEL);
  char operator;
  int operand1;
  short operand2;
  copy_from_user(data,buffer,ss);
  operator = data->a;
  operand1=data->b;
  operand2=data->c;
  IOMode=myini(DMABLOCKADDR);
  myoutc(operator,DMAOPCODEADDR);
  myouti(operand1,DMAOPERANDBADDR);
  myouts(operand2,DMAOPERANDCADDR);

  INIT_WORK(work_routine, drv_arithmetic_routine);

  // Decide io mode
  if(IOMode) {
    // Blocking IO
    printk("%s:%s(): queue work\n", PREFIX_TITLE, __func__);
    printk("%s:%s(): block\n", PREFIX_TITLE, __func__);

    schedule_work(work_routine);
    flush_scheduled_work();
      } 
  else {
    // Non-locking IO
    printk("%s,%s(): queue work\n",PREFIX_TITLE, __func__);
    schedule_work(work_routine);
     }
  
	return 0;
}
static long drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
	/* Implement ioctl setting for your device */
  int arg1=0;
  int IOMode=0;
  int readable=0;
  switch (cmd){
    case(HW5_IOCSETSTUID):
        
        get_user(arg1,(int *)arg);
        myouti(arg1, DMASTUIDADDR);
        printk("%s:%s:My STUID is %d\n",PREFIX_TITLE,__func__,arg1);
        return 0;
    case(HW5_IOCSETRWOK):
        
        get_user(arg1,(int *)arg);
        myouti(arg1, DMARWOKADDR);
        printk("%s:%s():RW OK\n",PREFIX_TITLE,__func__);
        return 0;
    case(HW5_IOCSETIOCOK):
        
        get_user(arg1,(int *)arg);
        myouti(arg1, DMAIOCOKADDR);
        return 0;
    case(HW5_IOCSETIRQOK):
         
         get_user(arg1,(int *)arg);
         myouti(arg1, DMAIRQOKADDR);
         printk("%s:%s():IOC OK\n",PREFIX_TITLE,__func__);
         return 0;
    case(HW5_IOCSETBLOCK):
         
         get_user(arg1,(int *)arg);
         myouti(arg1, DMABLOCKADDR);
         if(arg1==1){
          printk("%s:%s():Blocking IO\n",PREFIX_TITLE,__func__);
         }
         else if(arg1==0){
          printk("%s:%s():NonBlocking IO\n",PREFIX_TITLE,__func__);
         }
         return 0;
    case(HW5_IOCWAITREADABLE):
         IOMode=myini(DMABLOCKADDR);
         readable=myini(DMAREADABLEADDR);
         printk("%s:%s():Wait Readable 1\n",PREFIX_TITLE,__func__);
         if(!IOMode){ //non-blocking write
           while(!readable){
              msleep(1000);
              readable=myini(DMAREADABLEADDR);
           }
         }
         
         put_user(readable,(int *)arg);
         return 0;
    default:
         return -1;          
  }
	
}

static void drv_arithmetic_routine(struct work_struct* ws) {
	/* Implement arthemetic routine */
  
    int ans;
    char opcode;
    int operand1;
    short operand2;
    //int IOMode = myini(DMABLOCKADDR);
    myouti(0,DMAREADABLEADDR);

  
    opcode= myinc(DMAOPCODEADDR);
    operand1= myini(DMAOPERANDBADDR);
    operand2= myins(DMAOPERANDCADDR);
    

    switch(opcode) {
        case '+':
            ans=operand1+operand2;
            break;
        case '-':
            ans=operand1-operand2;
            break;
        case '*':
            ans=operand1*operand2;
            break;
        case '/':
            ans=operand1/operand2;
            break;
        case 'p':
            ans = prime(operand1, operand2);
            break;
        default:
            ans=0;
    }
    myouti(ans, DMAANSADDR);
    /*if(!IOMode){
      int readable=1;
      myouti(readable,DMAREADABLEADDR);
    }*/
    myouti(1,DMAREADABLEADDR);
    printk("%s:%s():%d %c %d = %d\n",PREFIX_TITLE,__func__,operand1,opcode,operand2,ans);

}

static int __init init_modules(void) {

  dev_t dev; 
	printk("%s:%s():...............Start...............\n", PREFIX_TITLE, __func__);
  
  dev_cdev = cdev_alloc();

	/* Register chrdev */ 
        
 if(alloc_chrdev_region(&dev,DEV_BASEMINOR,DEV_COUNT,DEV_NAME)<0)
 {
            printk(KERN_ALERT"Register chrdev failed!\n");
            return -1;
 }
 else
 {
            printk("%s:%s(): register chrdev(%i,%i)\n", PREFIX_TITLE, __func__, MAJOR(dev), MINOR(dev));
 }
 dev_major = MAJOR(dev);
 dev_minor = MINOR(dev);
	/* Init cdev and make it alive */
 dev_cdev->ops = &fops;
 dev_cdev->owner = THIS_MODULE;

 if(cdev_add(dev_cdev, dev, 1) < 0) {
    printk(KERN_ALERT"Add cdev failed!\n");
    return -1;
 }
     
	/* Allocate DMA buffer */
  dma_buf = kzalloc(DMA_BUFSIZE, GFP_KERNEL);
  printk("%s:%s():allocate dma buffer\n",PREFIX_TITLE,__func__);

	/* Allocate work routine */
  work_routine = kmalloc(sizeof(typeof(*work_routine)), GFP_KERNEL);

	return 0;
}

static void __exit exit_modules(void) {

	/* Free DMA buffer when exit modules */
  dev_t dev;
  
  dev = MKDEV(dev_major, dev_minor);
  

  kfree(dma_buf);
  printk("%s:%s():free dma buffer\n",PREFIX_TITLE,__func__);

  printk("%s:%s():unregister chrdev\n",PREFIX_TITLE,__func__);
  unregister_chrdev_region(dev, 1);
	/* Delete character device */
  cdev_del(dev_cdev);
	/* Free work routine */
  kfree(work_routine);

	printk("%s:%s():..............End..............\n", PREFIX_TITLE, __func__);
}

module_init(init_modules);
module_exit(exit_modules);
