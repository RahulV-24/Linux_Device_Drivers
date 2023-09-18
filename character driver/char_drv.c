#include <linux/module.h>     /* Needed by all modules */
#include <linux/kernel.h>     /* Needed for KERN_INFO */
#include <linux/init.h>       /* Needed for the macros */
#include <linux/fs.h>
#include <asm/uaccess.h>  /* for put_user */
#include <asm/errno.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rahul Varshney");
MODULE_DESCRIPTION("Character device driver");

volatile static int is_open = 0;
static char message[1024];
static int dev_num =0;
int message_length;

	static ssize_t device_read(struct file *filp, /* see include/linux/fs.h   */ 
                           char __user *buffer, /* buffer to fill with data */ 
                           size_t length, /* length of the buffer     */ 
                           loff_t *offset) 
	{
		
		int bytes_read = 0;
//		message_length = strlen(message);
		if(offset ==NULL) return -EINVAL;
		
		if(*offset >= message_length)	return 0;
		
		while((*offset < message_length)&&(bytes_read<length))
		{
			 __put_user( message[ *offset] , &buffer[bytes_read]);
			 *offset = *offset + 1;
			 bytes_read = bytes_read+1;
		} 
		
//		copy_to_user(message, buffer , message_length);
		printk(KERN_INFO " message - read - %s \n",message);
		printk(KERN_INFO " buffer - read - %s \n",buffer);
		return bytes_read;
	}
	
	ssize_t device_write (struct file * filep, const char __user * buffer, size_t length, loff_t * offset)
	{
		int bytes_write = 0;
		message_length = strlen(message);
		
		if(offset ==NULL) return -EINVAL;
		
		if(*offset >= 1023)	return -EINVAL;
		
		while((*offset <= 1023)&&(bytes_write<length))
		{
			 __get_user(message[ *offset] , &buffer[bytes_write]);
			 *offset = *offset + 1;
			 bytes_write = bytes_write+1;
		}
//		copy_from_user(buffer, message , message_length);
		printk(KERN_INFO "%s \n",message);
		return bytes_write;
		
	}
	int device_open (struct inode * inodep, struct file * filep)
	{
		if(is_open == 1)
		{
			printk(KERN_INFO "Error - char device already open");    // binary semaphore for mutual exclusion 
			return -EBUSY;
		}
		is_open = 1;
		try_module_get(THIS_MODULE);
		
		return 0;
			
	}
	int device_release (struct inode * inodep, struct file * filep)
	{
		if(is_open == 0)
		{
			printk(KERN_INFO "Error - char device already closed");  // binary semaphore for mutual exclusion
			return -EBUSY;
		}
		is_open =0;
		module_put(THIS_MODULE);
		
		return 0;
	}
	
	
	struct file_operations fops = {
		.read = device_read,
		.write = device_write,
		.open = device_open,
		.release = device_release
		};
    
    static int __init char_driver_init(void)
    {
    	strncpy(message,"char message test. ",1023);
    	message_length = strlen(message);	
        dev_num = register_chrdev(0,"char_drv", &fops);
    	printk(KERN_INFO" char device major no. is %d\n",dev_num);
    	
    	return 0; 
    }
    
    static void __exit char_driver_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
	unregister_chrdev(dev_num,"char_drv");

}
module_init(char_driver_init);
module_exit(char_driver_exit);
