#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>


#define MY_MAJOR 90


/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("laplas");
MODULE_DESCRIPTION("A hello world LKM");


/**
 * @brief This function is called,when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance)
{
  printk("[LC] - Open was called.\n");
  return 0;
}


/**
 * @brief This function is called,when the device file is closed
 */
static int driver_close(struct inode *device_file, struct file *instance)
{
  printk("[LC] - Close was called.\n");
  return 0;
}


static struct file_operations fops = {
  .owner = THIS_MODULE,
  .open = driver_open,
  .release = driver_close
};


/**
 * @brief This function is called, when the module is loaded into the kernal
 */
static int __init ModuleInit(void) 
{
  int retval;
  printk("[LC] - Successfully Loaded Kernal Module Laplas\n");

  /*
   * Register device number
   */
  retval = register_chrdev(MY_MAJOR, "laplas", &fops);
  if (retval == 0)
  {
    printk("[LC] - Registered Device Number Major: %d,\n[LC] - Registered Device Number Minor: %d\n", MY_MAJOR, 0);
  }
  else if (retval > 0)
  {
    printk("[LC] - Registered Device Number Major: %d,\n[LC] - Registered Device Number Minor: %d\n", retval>>20, retval&0xfffff);
  }
  else
  {
    printk("[LC ~ Error] - Could not register device number.\n");
    return -1;
  }

  return 0;
}


/**
 * @brief This function is called, when the module is removed from the kernal
 */
static void __exit ModuleExit(void)
{
  unregister_chrdev(MY_MAJOR, "laplas");
  printk("[LC] - Unloading Kernal Module Laplas\n");
}


module_init(ModuleInit);
module_exit(ModuleExit);
