obj-m = trial.o

KVERSION = $(shell uname -r)

all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules
	gcc test.c

clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
	rm a.out

