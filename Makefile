CC=gcc
CFLAGS=-Wall	-g
OBJS=main.o sysutil.o session.o ftpproto.o privparent.o str.o tunable.o parseconf.o privsock.o
LIBS=-lcrypt
BIN=miniftp
$(BIN):$(OBJS)
		$(CC)	$(CFLAGS)	$^	-o	$@	$(LIBS)
%.o:%.c
		$(CC)	$(CFLAGS)	-c	$<	-o	$@
.PHONY:clean
clean:
	rm	-fr	*.o	$(BIN)
