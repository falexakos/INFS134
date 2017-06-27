#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <errno.h>
#include <math.h>

#define ISH264 1
#ifndef FRAMES_NO
 #define FRAMES_NO 8
#endif

#ifndef MAXWIDTH
 #define MAXWIDTH 176
#endif
#ifndef MAXHEIGHT
 #define MAXHEIGHT 144
#endif

typedef unsigned char uchar;
double A[4][4], AT[4][4], C[4][4], CT[4][4],Ytemp[4][4]; 
extern void matr_mult(double a[4][4], double b[4][4], double c[4][4]);
extern void initCoefs(double Amatr[4][4], short);
extern void transposeMatr(double a[4][4], double aT[4][4]);
extern void readFrame(FILE *rawv, uchar theframe[MAXHEIGHT][MAXWIDTH], int h, int w);

