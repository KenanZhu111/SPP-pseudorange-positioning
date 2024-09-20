#ifndef _XYZ2BLH_H_
#define _XYZ2BLH_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include"read.h"

typedef struct 
{   
  double B;
  double L;
  double H;  
}xyz2blh, *pxyz2blh;

pxyz2blh XYZtoBLH(pxyz2blh xyz2blh, 
                  double X, double Y, double Z, double a, double e2)

{
    xyz2blh = (pxyz2blh)malloc(sizeof(pxyz2blh));
    double B = 0.0, N = 0.0, H = 0.0, R0, R1, deltaH, deltaB;
    R0 = sqrt(pow(X, 2) + pow(Y, 2));
    R1 = sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));
    //经度直接求解
    xyz2blh->L = atan2(Y, X) * 57.295779513;
    //迭代求大地维度和大地高
    N = a;
    H = R1 - a;
    B = atan2(Z * (N + H), R0 * (N * (1 - e2) + H));
    do
    {
        deltaH = N;//判断收敛所用
        deltaB = B;
		N = a / sqrt(1 - e2 * pow(sin(B), 2));
		H = R0 / cos(B) - N;
		B = atan2(Z * (N + H), R0 * (N * (1 - e2) + H));
	} while (fabs(deltaH - H) > 1.0e-3 && fabs(deltaB - B) > 1.0e-9);
	xyz2blh->B = B * 57.295779513;
	xyz2blh->H = H;

    return xyz2blh;
}
    


#endif