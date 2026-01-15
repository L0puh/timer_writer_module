#include <linux/module.h>
#include <linux/init.h>

int init(void){
   printk("Hello world\n");
   return 0;
}

void cleanup(void){
   printk("Goodbye!\n");
}

module_init(init);
module_exit(cleanup);

MODULE_LICENSE("GPL");

