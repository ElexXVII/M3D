#ifndef _LIB_MAT_H_
#define _LIB_MAT_H_

#include "lib_3d.h"

#define MATRICE_IDENTITE (double[4][4])\
{ { 1., 0., 0., 0.}, \
  { 0., 1., 0., 0.}, \
  { 0., 0., 1., 0.}, \
  { 0., 0., 0., 1.} \
}

void multiplication_vecteur(t_point3d * v1, double m[4][4], t_point3d * v2);	// v1 = m*v2
void multiplication_matrice(double m1[4][4], double m2[4][4], double m3[4][4]);	// m1 = m2*m3
void copier_matrice(double m1[4][4], double m2[4][4]);	// m1 = m2

#endif
