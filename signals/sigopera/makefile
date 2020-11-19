src = $(wildcard *.c) #找到所有c文件
obj = $(patsubst %.c,%,$(src) )#替换

all:$(obj)


$(obj):%:%.c
	gcc $< -o $@

clean:
	-rm -rf $(obj)


.PHONY:clean all

