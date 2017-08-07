LFLAG := -L ../Library -lfun -lbitwise_lib -lslist -lmenu -lapc -ldlist -lastack -linfix -lstackarr -lqueue -lbsearch -lsort -lrbtree -lbstree -lhlist -lindexing 
CFLAG := -I ../Include
SRCS := $(wildcard *.c)
#multiple targets	
TARGETS := $(SRCS:.c=.out)
all : ${TARGETS}
#run like a loop i.e. takes one .out file from target and its respective .c file from src at a time
%.out : %.c
	gcc $^ ${LFLAG} ${CFLAG} -o $@
#	gcc $^ -L ../Library -I ../Include -lfun -o $@
clean : 
	rm ${TARGET}
