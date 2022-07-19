

#include<linux/init.h>
#include<linux/module.h>

#include<linux/fs.h>
#include<linux/slab.h>
//#include<asm/uaccess.h>
#include<linux/uaccess.h> 

#define BUFFER_SIZE 1024

/* Define device_buffer and other global data structures you will need here */
int countOpen=0;
int countClose=0;
static char *device_buffer[BUFFER_SIZE];

ssize_t simple_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
  /* *buffer is the userspace buffer to where you are writing the data you want to be read from the device file*/
  /* length is the length of the userspace buffer*/
  /* offset will be set to current position of the opened file after read*/
  /* copy_to_user function: source is device_buffer and destination is the userspace buffer *buffer */
  int maxSize=BUFFER_SIZE-*offset;
  if(BUFFER_SIZE<*offset){
    printk(KERN_ALERT"Do not have enough buffer size");
  }else if(BUFFER_SIZE==*offset){
    printk(KERN_ALERT"It is the end of the buffer");
    maxSize=0;
    length=0;
  }else{
    copy_to_user(buffer,device_buffer+*offset,maxSize);
  }
  *offset+=length;
  printk(KERN_ALERT "Device Driver has read %d ", length);

  return 0;
}



ssize_t simple_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
  /* *buffer is the userspace buffer where you are writing the data you want to be written in the device file*/
  /* length is the length of the userspace buffer*/
  /* current position of the opened file*/
  /* copy_from_user function: destination is device_buffer and source is the userspace buffer *buffer */
  //int maxSize=BUFFER_SIZE-*offset;

  if(BUFFER_SIZE<*offset){
    printk(KERN_ALERT"Do not have enough buffer size");
  }//else{
  copy_from_user(device_buffer+*offset,buffer,length);
  //}
  *offset+=length;
  printk(KERN_ALERT"Device Driver has written %d ", length);
  return length;
}


int simple_char_driver_open (struct inode *pinode, struct file *pfile)
{
  /* print to the log file that the device is opened and also print the number of times this device has been opened until now*/
  countOpen++;
  printk(KERN_ALERT"The file has been opened %d times",countOpen);
  return 0;
}

int simple_char_driver_close (struct inode *pinode, struct file *pfile)
{
  /* print to the log file that the device is closed and also print the number of times this device has been closed until now*/
  countClose++;
  printk(KERN_ALERT"The file has been closed %d times",countClose);
  return 0;
}

loff_t simple_char_driver_seek (struct file *pfile, loff_t offset, int whence)
{
  /* Update open file position according to the values of offset and whence */
  loff_t *newPosition=0;
  switch(whence){
    case 0:
      newPosition=offset;
      break;
    case 1:
      newPosition=pfile->f_pos+offset;
      break;
    case 2:
      newPosition=BUFFER_SIZE-offset;
      break;
  }
  if(newPosition>=BUFFER_SIZE){
    printk(KERN_ALERT"You reached the end of the buffer");
  }else if(newPosition<0){
    printk(KERN_ALERT"The new position is small than 0");
  }else{
    pfile->f_pos=newPosition;
  }
  return 0;
}

struct file_operations simple_char_driver_file_operations = {

  .owner   = THIS_MODULE,
  /* add the function pointers to point to the corresponding file operations. look at the file fs.h in the linux souce code*/
  .open    = simple_char_driver_open,
  .release = simple_char_driver_close,
  .llseek  = simple_char_driver_seek,
  .read    = simple_char_driver_read,
  .write   = simple_char_driver_write
};

static int simple_char_driver_init(void)
{
  /* print to the log file that the init function is called.*/
  /* register the device */
  printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
  register_chrdev(240, "PA2_simple_char_driver", &simple_char_driver_file_operations);
  kmalloc(device_buffer, GFP_KERNEL);
  return 0;
}

static void simple_char_driver_exit(void)
{
  /* print to the log file that the exit function is called.*/
  /* unregister  the device using the register_chrdev() function. */
  printk(KERN_ALERT "exit %s function\n",__FUNCTION__);
  unregister_chrdev(240,"PA2_simple_char_driver");
  kfree(&device_buffer);
}

/* add module_init and module_exit to point to the corresponding init and exit function*/
module_init(simple_char_driver_init);
module_exit(simple_char_driver_exit);