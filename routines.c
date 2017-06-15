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

void transposeMatr(double a[4][4], double aT[4][4])
{
	register int i,j;
	
	for (i=0; i<4; i++)
	 for (j=0; j<4 ; j++)
	   aT[i][j]=a[j][i];
}

