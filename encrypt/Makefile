CFLAGS  += -I. -D_FILE_OFFSET_BITS=64 -Wall -W -Wdeclaration-after-statement
OFLAGS  = -O2

OBJS=	aes.o

all: things

.SILENT:

.c.o:
		echo "  CC    $<"
		$(CC) $(CFLAGS) $(OFLAGS) -c $<

things:	things.c $(OBJS)
				echo   "  CC    things"
				$(CC) $(CFLAGS) $(OFLAGS) things.c -o $@ $(OBJS)

clean:
		rm -f *.o things
