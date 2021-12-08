#include <rtdm/driver.h>
#include <linux/module.h>

struct rtdm_device *rt_demo_dev;

int rt_demo_open(struct rtdm_fd *fd, int oflags)
{
	return 0;
}

ssize_t rt_demo_read(struct rtdm_fd *fd, void *buf, size_t nbyte)
{
	return 0;
}

ssize_t rt_demo_write(struct rtdm_fd *fd, const void *buf, size_t nbyte)
{
	return 0;
}

void rt_demo_close(struct rtdm_fd *fd)
{
}

static struct rtdm_driver rt_demo_driver = {
	.profile_info = (struct rtdm_profile_info)RTDM_PROFILE_INFO(
		"rt_demo", RTDM_CLASS_TESTING, 0, 0),
	.device_flags = RTDM_NAMED_DEVICE,
	.base_minor = 0,
	.device_count = 256,
	.context_size = 0,
	.ops = {
		.open = rt_demo_open,
		.read_rt = rt_demo_read,
		.write_rt = rt_demo_write,
		.close = rt_demo_close,
	},
};

static int __init rt_demo_driver_init(void)
{
	int err = -1;

	rt_demo_dev = kmalloc(sizeof(struct rtdm_device), GFP_KERNEL);

	rt_demo_dev->driver = &rt_demo_driver;
	rt_demo_dev->label = "rtdemo";

	err = rtdm_dev_register(rt_demo_dev);
	if (err)
	{
		return -1;
	}

	return 0;
}

static void __exit rt_demo_driver_exit(void)
{
	rtdm_dev_unregister(rt_demo_dev);
}

module_init(rt_demo_driver_init);
module_exit(rt_demo_driver_exit);

MODULE_LICENSE("GPL");
