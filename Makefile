CFLAGS = -g -w 
LIBS = -lm
OBJS = extractf.o routines.o 
CC = gcc

extractf:     $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o extractf $(LIBS)
routines.o:   dct.h routines.c 
extractf.o:   dct.h extractf.c 
clean:
	      rm -f $(OBJS) extractf
