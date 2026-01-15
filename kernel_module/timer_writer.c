#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <linux/fs.h>
#include <linux/atomic.h>
#include <linux/jiffies.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("l0puh.github.io/");
MODULE_DESCRIPTION("timer-based file writer");

static char *filename = "/var/tmp/test_module/log.txt";
static int seconds = 2;

module_param(filename, charp, 0644);
module_param(seconds, int, 0644);

static struct timer_list timer;
static struct work_struct write_work;
static atomic_t counter = ATOMIC_INIT(0);

static void write_worker(struct work_struct *work){
    struct file *file;
    loff_t pos;
    char msg[128];
    int count;
    ssize_t ret;

    count = atomic_inc_return(&counter);
    snprintf(msg, sizeof(msg),
             "Hello from kernel module (%d)\n", count);

    file = filp_open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (IS_ERR(file)) {
        pr_err("file open failed: %ld\n", PTR_ERR(file));
        return;
    }

    pos = file->f_pos;
    ret = kernel_write(file, msg, strlen(msg), &pos);
    if (ret < 0)
        pr_err("kernel_write failed: %zd\n", ret);
    else
        file->f_pos = pos;

    filp_close(file, NULL);
}

static void timer_callback(struct timer_list *t){
    schedule_work(&write_work);
    mod_timer(&timer, jiffies + seconds * HZ);
}

static int __init writer_init(void){
    if (seconds < 1)
        return -EINVAL;

    INIT_WORK(&write_work, write_worker);

    timer_setup(&timer, timer_callback, 0);
    mod_timer(&timer, jiffies + seconds * HZ);

    pr_info("timer_writer loaded\n");
    return 0;
}

static void __exit writer_exit(void){
    timer_shutdown_sync(&timer);
    flush_work(&write_work);
    pr_info("timer_writer unloaded\n");
}

module_init(writer_init);
module_exit(writer_exit);
