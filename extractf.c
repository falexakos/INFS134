#include "dct.h"

int main(int argc, char *argv[])
{
	int W=MAXWIDTH, H=MAXHEIGHT, frames=FRAMES_NO;

	if (argc < 2)
	{
		fprintf(stderr, "Syntax: %s [Width] [Height] [-nNumber] filename\n", argv[0]);
		fprintf(stderr, "To extract <number> frames of raw video with resolution of <Width x Height>\n");
		return 1;
	}
	if (argc == 3)
	{
		if (!index(argv[1], '-'))
		{
			W=atoi(argv[1]);
			H=atoi(argv[2]);
			if ((W==0) || (H==0))	
			{
				fprintf(stderr, "Wrong arguments!\n");
				return 1;
			}
		}
		else
		{
			frames=atoi(*(argv+1)+2);
			if (frames==0)
			{

				fprintf(stderr, "Wrong arguments!\n");
				return 1;
			}
		}
	}

	return 0; /* Everything Ok. */
}
