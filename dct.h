#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <ctype.h>
#include <strings.h>
#include <errno.h>
#include <math.h>

#define ISH264 1
#ifndef FRAMES_NO
 #define FRAMES_NO 8
#endif

#ifndef MAXWIDTH
 #define MAXWIDTH 352
#endif
#ifndef MAXHEIGHT
 #define MAXHEIGHT 288
#endif
#define ARRAYS (int)(MAXWIDTH*MAXHEIGHT)/16

typedef unsigned char uchar;
double A[4][4], AT[4][4], C[4][4], CT[4][4]; 
FILE *fp;
extern void clearMatr16(double m[4][4]);
extern void matr_mult(double a[4][4], double b[4][4], double c[4][4]);
extern void initCoefs(double Amatr[4][4], short);
extern void transposeMatr(double a[4][4], double aT[4][4]);
extern void readFrame(FILE *rawv, uchar theframe[MAXHEIGHT][MAXWIDTH], int h, int w);
extern void performDCT(uchar theframe[MAXHEIGHT][MAXWIDTH], int h, int w);

