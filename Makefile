# This line tells the build system about the module object file
obj-m += beep.o

# The all target tells make to invoke the kernel build system
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

# The clean target cleans up the module object files and other intermediate files
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean

