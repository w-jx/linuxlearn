src=$(wildcard *.c)
obj=$(patsubst  %.c,%,$(src) )

all:$(obj)

$(obj):%:%.c
	gcc $< -o $@

clean:
	-rm -rf $(obj)

.PHONY:
	clean all
