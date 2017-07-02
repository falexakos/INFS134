CFLAGS = -DMAXWIDTH=352 -DMAXHEIGHT=288 -g -w 
# CIF Format: 352x288
LIBS = -lm
OBJS = extractf.o routines.o 
CC = gcc

extractf:     $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o extractf $(LIBS)
routines.o:   dct.h routines.c 
extractf.o:   dct.h extractf.c 
clean:
	      rm -f $(OBJS) extractf
