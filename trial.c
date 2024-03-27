#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/sched.h>
#include<linux/sched/task_stack.h>
#include <linux/kprobes.h>
#include<linux/binfmts.h>

#define N 16
static int counter[N];
static int uvm_dummy_target;


static ssize_t read_counters(struct kobject *kobj,
                                  struct kobj_attribute *attr, char *buf)
{
	// Remember to lseek (fd, 0, SEEK_SET) before reading
	int i, j;
	j = -1;
	j = sprintf (buf, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
			counter[0], counter[1], counter[2], counter[3], counter[4], counter[5], counter[6], counter[7], counter[8], counter[9], counter[10], counter[11], counter[12], counter[13], counter[14], counter[15]);
	printk (KERN_INFO "Call to print counters: returning value %d\n", j);
	for (i = 0; i < N; i++)
		counter[i] = 0;
	return j;
}

static ssize_t increment_count(struct kobject *kobj,
                                   struct kobj_attribute *attr,
                                   const char *buf, size_t count)
{
	// called via a write (fd, "....", count) to /sys/kernel/..
	// buffer may be a garbage buffer
	if (count < 0 || count >= N) {
		printk (KERN_INFO "Bad call to increment_count\n");
		return -1;
	}
	printk (KERN_INFO "Call to increment_count index %lx; old value%d\n", count, 
			counter[count]);
	counter[count] = counter[count] + 1;
        return count;
}

static struct kobj_attribute uvm_counter_attr = __ATTR(uvm_dummy_target, 0664, read_counters, increment_count);


static struct attribute *uvm_ctr_grp[] = {
        &uvm_counter_attr.attr,
        NULL,
};
static struct attribute_group traphook_attr_group = {
        .attrs = uvm_ctr_grp,
        .name = "uvm_counters_group",
};

int init_module(void)
{
	int ret;
	int i = 0; 
	if (N != 16) {
		printk (KERN_INFO "Module was made for 16 counters only\n");
		return -2;
	}
	for (i = 0; i < N; i++)
		counter[i] = 0;
	
	ret = sysfs_create_group (kernel_kobj, &traphook_attr_group);
        if(unlikely(ret))
                printk(KERN_INFO "demo: can't create sysfs\n");
	uvm_dummy_target = 0;
        return 0;
}

void cleanup_module(void)
{
	printk (KERN_INFO "Entered cleanup_module\n");
        sysfs_remove_group (kernel_kobj, &traphook_attr_group);
	printk(KERN_INFO "Removed the group\n");
}
MODULE_LICENSE("GPL");
MODULE_AUTHOR("prsingh@cse.iitk.ac.in")
// Based on modules from CS614 (deba@cse.iitk.ac.in) and Greg KH's samples under linux/samples/kobject/
