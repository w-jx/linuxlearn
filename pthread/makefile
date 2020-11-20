src=$(wildcard *.c)
obj=$(patsubst %.c,%,$(src))


all:$(obj)

CFLAGES:-lpthread
$(obj):%:%.c
	gcc $< -o $@ -pthread

clean:
	-rm -rf $(obj)

.PHONY:
	clean all
