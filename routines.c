#include "dct.h"

void matr_mult(double a[4][4], double b[4][4], double c[4][4])
{
	register int i,j,k;
	
	for (i=0; i<4; i++)
	 for (j=0; j<4; j++)
	 {
	 	c[i][j]=0.0;
	 	for (k=0; k<4; k++) c[i][j]+=a[i][k]*b[k][j];
	 }
}

void initCoefs(double Amatr[4][4], short flag)
{
	double a,b,c;

	if (flag != ISH264)
	{	
		a=0.5; b=sqrt(0.5)*cos(M_PI/8); c=sqrt(0.5)*cos(3*M_PI/8);
		Amatr[0][0]=Amatr[0][1]=Amatr[0][2]=Amatr[0][3]=a;
		Amatr[1][0]=b;Amatr[1][1]=c;Amatr[1][2]=-c;Amatr[1][3]=-b;
		Amatr[2][0]=Amatr[2][3]=a;Amatr[2][1]=Amatr[2][2]=-a;
		Amatr[3][0]=c;Amatr[3][1]=-b;Amatr[3][2]=b;Amatr[3][3]=-c;
	}
	else
	{
		a=0.5;b=sqrt(0.4);
		Amatr[0][0]=Amatr[2][0]=Amatr[0][2]=Amatr[2][2]=a*a;
		Amatr[1][0]=Amatr[0][1]=Amatr[1][2]=Amatr[2][1]=Amatr[2][3]=Amatr[3][2]=Amatr[0][3]=Amatr[3][0]=(a*b)/2;
		Amatr[1][1]=Amatr[1][3]=Amatr[3][1]=Amatr[3][3]=(b*b)/4;
	}
}

void clearMatr16(double m[4][4])
{
	register int i,j;

	for (i=0;i<4;i++)
   	 for (j=0;j<4;j++) m[i][j]=0.0;
}

void transposeMatr(double a[4][4], double aT[4][4])
{
	register int i,j;
	
	for (i=0; i<4; i++)
	 for (j=0; j<4 ; j++)
	   aT[i][j]=a[j][i];
}

void readFrame(FILE *rawv, uchar theframe[MAXHEIGHT][MAXWIDTH], int h, int w)
{
	uchar Ybuf[h*w];
	int YLEN=h*w;
	register int i,j,k=0;

	fread(Ybuf, 1, YLEN, rawv);
	if (ferror(rawv)!=0)
  	{
		perror("readFrame()");
		exit(2);
	}
	for (j=0; j<w; j++) 
       	 for (i=0;i<h;i++) theframe[i][j]=Ybuf[k++]; 
  	
	fread(Ybuf, 1, (int)(YLEN/2), rawv); /* Skip chroma data */
	if (ferror(rawv)!=0)
	{
		perror("readFrame()");
		exit(2);
	}
	return;
}

void performDCT(uchar theframe[MAXHEIGHT][MAXWIDTH], int h, int w)
{
	register int i,j,k,l,q,p,m;
	double submatr[ARRAYS][4][4], X[4][4],Y[ARRAYS][4][4], energies[4][4];
	double Ytemp[4][4];
	double macblocks=h*w, arrs=macblocks/16.0; //'macblocks' = How many Macroblocks. 'arrs'=Denominator to calculate average energies

	initCoefs(A,0); transposeMatr(A, AT);
	clearMatr16(energies);
	k=0;l=0;m=0;
	/* The DCT itself */
	do
	{
	 for (i=l;i<l+4;i++) 
	  for (j=k;j<k+4;j++) X[i-l][j-k]=theframe[i][j];
	  matr_mult(A,X,Ytemp);
	  matr_mult(Ytemp, AT, Y[m]);
	  for (q=0; q<4; q++)
	   for (p=0;p<4;p++) 
            energies[q][p]+=Y[m][q][p]*Y[m][q][p];
	  m++;
	  k=(k+4)%w; /*k+=4; if (k>=w) k=0;*/
	  if (k==0) l+=4;
	}
	while (l<h);
	printf("DONE!\n");
	/* Now, let's calculate energy. */
	l=0;
	for (i=0; i<4; i++)
	 for (j=0;j<4;j++) printf("%d.Average Energy for [%d , %d] is %.3lf\n", ++l,i+1,j+1,energies[i][j]/arrs);
	putchar('\n');
	initCoefs(A,ISH264);
	C[0][0]=C[0][1]=C[0][2]=C[0][3]=1.0;
	C[1][0]=2.0;C[1][1]=1;C[1][2]=-1.0;C[1][3]=-2.0;	
	C[2][0]=1.0;C[2][1]=C[2][2]=-1.0;C[2][3]=1.0;
	C[3][0]=1;C[3][1]=-2.0;C[3][2]=2.0;C[3][3]=-1.0;
	transposeMatr(C,CT);
	clearMatr16(energies);
	/* Perform DCT (with "rounded" constants) for each 4x4 submatrix */
	/**********
	m=0;k=0;l=0;
	do
	{
	 for (i=l;i<l+4;i++) 
	  for (j=k;j<k+4;j++) X[i-l][j-k]=theframe[i][j];
	  matr_mult(C,X,Ytemp);
	  matr_mult(Ytemp, CT, Y[m]);
	  for (q=0; q<4; q++)
	   for (p=0;p<4;p++) 
	   {
		Y[m][p][q]*=A[p][q];             
		energies[q][p]+=Y[m][q][p]*Y[m][q][p];
	   }
	  m++;
	  k=(k+4)%w; 
	  if (k==0) l+=4;
	}
	while (l<h);
	printf("H.264 \"rounded\" completed!\n");
	l=0;
	for (i=0; i<4; i++)
	 for (j=0;j<4;j++) printf("%d.Average Energy for [%d , %d] is %.3lf\n", ++l,i+1,j+1,energies[i][j]/(double)arrs);
	putchar('\n');
	**********/
	return;
}

