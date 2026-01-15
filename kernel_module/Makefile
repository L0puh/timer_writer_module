obj-m += timer_writer.o
KDIR := /lib/modules/$(shell uname -r)/build
SRC := $(CURDIR)
TMP=/var/tmp/test_module/


all: 
	$(MAKE) -C $(KDIR) M=$(SRC) modules

clean:
	$(MAKE) -C $(KDIR) M=$(SRC) clean
	sudo rm -rf $(TMP)

load:
	sudo mkdir -p $(TMP)
	sudo chmod 777 $(TMP)
	sudo insmod timer_writer.ko

unload:
	sudo rmmod timer_writer.ko
