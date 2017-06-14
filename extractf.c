#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#ifndef DEFWIDTH
 #define DEFWIDTH 176
#endif
#ifndef DEFHEIGHT
 #define DEFHEIGHT 144
#endif

int main(int argc, char *argv[])
{

	if (argc < 2)
	{
		fprintf(stderr, "Syntax: %s [Width] [Height] [-nNumber] filename\n", argv[0]);
		fprintf(stderr, "To extract <number> frames of raw video with resolution of <Width x Height>\n");
		return 1;
	}

	return 0; /* Everything Ok. */
}

