#include "dct.h"

int main(int argc, char *argv[])
{
	int W=MAXWIDTH, H=MAXHEIGHT, frames=FRAMES_NO;
	register int i;
	uchar curframe[MAXHEIGHT][MAXWIDTH];
	char fname[256];

	if (argc < 2)
	{
		fprintf(stderr, "Syntax: %s [Width] [Height] [-nNumber] filename\n", argv[0]);
		fprintf(stderr, "To extract <number> frames of raw video with resolution of <Width x Height>\n");
		return 1;
	}
	if (argc==2)
		strcpy(fname, argv[1]);
	if (argc == 3)
	{
		if (!strncmp(argv[1], "-n",2))
		{
			frames=atoi(*(argv+1)+2);
			if (frames==0)
			{

				fprintf(stderr, "Wrong arguments!\n");
				return 1;
			}
			strcpy(fname, argv[2]);
		}
		else
		{
			fprintf(stderr, "Wrong arguments!\n");
			fprintf(stderr, "What do you mean by %s ?\n", argv[1]);
			return 1;
		}		
	}
	if (argc == 4)
	{
		W=atoi(argv[1]);
		H=atoi(argv[2]);
		if ((W==0) || (H==0))
		{
			fprintf(stderr, "Wrong arguments! (width, weight ?)\n");
			return 1;
		}
		strcpy(fname,argv[3]);
	}
	if (argc == 5)
	{
		if (strncmp(argv[3],"-n",2))
		{
			fprintf(stderr, "Wrong arguments!\n");
			fprintf(stderr, "What do you mean by %s ?\n", argv[3]);
			return 1;
		}		
		frames=atoi(*(argv+3)+2);
		if (frames==0)
		{

			fprintf(stderr, "Wrong arguments! (Frame no ?)\n");
			return 1;
		}
		W=atoi(argv[1]);
		H=atoi(argv[2]);
		strcpy(fname, argv[4]);
	}
	printf("Going to extract %d frames sized %dx%d from file: %s\n", frames, W,H, fname);
	fp=fopen(fname, "r");
	if (!fp)
	{
		perror("In main()");
		exit(1);
	}
	for (i=0;i<frames;i++)
	{
		readFrame(fp,curframe, H, W);
		printf("Calculating DCT for frame no. %d ...\n", i+1);
		performDCT(curframe, H, W);
	}
	fclose(fp);
	return 0; /* Everything Ok. */
}
