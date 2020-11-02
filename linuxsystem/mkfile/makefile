src = $(wildcard *.c) 
obj = $(patsubst %.c,%.o,$(src))

ALL:a.out

a.out:$(obj)
	gcc $^ -o $@

%.o:%.c
	gcc -c $< -o $@

clean:
	-rm -rf $(obj) a.out

 .PHONY:clean All
