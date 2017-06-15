#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <errno.h>
#include <math.h>

extern void matr_mult(double a[4][4], double b[4][4], double c[4][4]);
extern void initCoefs(double Amatr[4][4], short);
extern void transposeMatr(double a[4][4], double aT[4][4]);

#define ISH264 1
#ifndef FRAMES_NO
 #define FRAMES_NO 8
#endif

#ifndef DEFWIDTH
 #define DEFWIDTH 176
#endif
#ifndef DEFHEIGHT
 #define DEFHEIGHT 144
#endif

