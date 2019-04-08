#ifndef _LIB_3D_H_
#define _LIB_3D_H_

#include <math.h>
#include "lib_2d.h"

typedef struct {
	double xyzt[4];
} t_point3d;

typedef struct {
	t_point3d *abc[3];
} t_triangle3d;

/*
 * Zone PA
 */

t_point3d *definirPoint3d_PA(double x, double y, double z);
t_point3d *definirVecteur3d_PA(double x, double y, double z);
t_point3d *copierPoint3d_PA(t_point3d * p);
void libererPoint3d_PA(t_point3d * p);
t_triangle3d *definirTriangle3d_PA(t_point3d * a, t_point3d * b, t_point3d * c);
t_triangle3d *copierTriangle3d_PA(t_triangle3d * t);
void libererTriangle3d_PA(t_triangle3d * t);
void differenceVecteur3d_PA(t_point3d * v1, t_point3d * v2);	//v1 = v1-v2
void sommeVecteur3d_PA(t_point3d * v1, t_point3d * v2);	//v1 = v1+v2
void divisionVecteur3d_PA(t_point3d * v1, int n);	//v1 = v1/n
t_point3d *centreGraviteTriangle3d_PA(t_triangle3d * t);

double xmoyen_PA(t_triangle3d * t);
double ymoyen_PA(t_triangle3d * t);
double zmoyen_PA(t_triangle3d * t);
void remplirTriangle3d_PA(t_surface * surface, t_triangle3d * triangle, Uint32 c, double l, double h, double d);

void translationTriangle3d_PA(t_triangle3d * t, t_point3d * vecteur);
void rotationTriangle3d_PA(t_triangle3d * t, t_point3d * centre, float degreX, float degreY, float degreZ);
void transformationTriangle3d_PA(t_triangle3d * t, double mat[4][4]);

/*
 * Zone etu
 */

t_point3d *definirPoint3d_etu(double x, double y, double z);
t_point3d *definirVecteur3d_etu(double x, double y, double z);
t_point3d *copierPoint3d_etu(t_point3d * p);
void libererPoint3d_etu(t_point3d * p);
t_triangle3d *definirTriangle3d_etu(t_point3d * a, t_point3d * b, t_point3d * c);
t_triangle3d *copierTriangle3d_etu(t_triangle3d * t);
void libererTriangle3d_etu(t_triangle3d * t);
void differenceVecteur3d_etu(t_point3d * v1, t_point3d * v2);	//v1 = v1-v2
void sommeVecteur3d_etu(t_point3d * v1, t_point3d * v2);	//v1 = v1+v2
void divisionVecteur3d_etu(t_point3d * v1, int n);	//v1 = v1/n
t_point3d *centreGraviteTriangle3d_etu(t_triangle3d * t);

double xmoyen_etu(t_triangle3d * t);
double ymoyen_etu(t_triangle3d * t);
double zmoyen_etu(t_triangle3d * t);
void remplirTriangle3d_etu(t_surface * surface, t_triangle3d * triangle, Uint32 c, double l, double h, double d);

void translationTriangle3d_etu(t_triangle3d * t, t_point3d * vecteur);
void homothetieTriangle3d_etu(t_triangle3d * t, float facteurX, float facteurY, float facteurZ);
void rotationTriangle3d_etu(t_triangle3d * t, t_point3d * centre, float degreX, float degreY, float degreZ);
void transformationTriangle3d_etu(t_triangle3d * t, double mat[4][4]);

/*
 * -------------------------------------------
 */

/* entrée : 3 coordonnees
 * sortie : un point 3d (dernière coordonnée dans le systeme homogene à 1)
 */
extern t_point3d *(*definirPoint3d) (double x, double y, double z);
/* entrée : 3 coordonnees
 * sortie : un vecteur 3d (dernière coordonnée dans le systeme homogene à 0)
 */
extern t_point3d *(*definirVecteur3d) (double x, double y, double z);
/* entrée : un point 3d
 * sortie : un point 3d qui est une recopie (avec de la nouvelle mémoire) du point en entree
 */
extern t_point3d *(*copierPoint3d) (t_point3d * p);

/* entrée : un triangle 3d
 * sortie : void
 */
extern void (*libererPoint3d) (t_point3d * p);

/* entrée : 3 points 3d
 * sortie : un triangle 3d
 */
extern t_triangle3d *(*definirTriangle3d) (t_point3d * a, t_point3d * b, t_point3d * c);
/* entrée : un triangle 3d
 * sortie : un triangle 3d qui est une recopie (avec de la nouvelle mémoire) du triangle en entree
 */
extern t_triangle3d *(*copierTriangle3d) (t_triangle3d * t);

/* entrée : un triangle 3d
 * sortie : void
 */
extern void (*libererTriangle3d) (t_triangle3d * t);

/* entrée : 2 vecteurs 3d :  v1 = v1-v2
 * sortie : void
 */
extern void (*differenceVecteur3d) (t_point3d * v1, t_point3d * v2);
/* entrée : 2 vecteurs 3d :  v1 = v1+v2
 * sortie : void
 */
extern void (*sommeVecteur3d) (t_point3d * v1, t_point3d * v2);
/* entrée : 2 vecteurs 3d :  v1 = v1/n (sert a normaliser un vecteur avec une division par la norme)
 * sortie : void
 */
extern void (*divisionVecteur3d) (t_point3d * v1, int n);
/* entrée : un triangle 3d
 * sortie : un point 3d qui est le centre de gravite du triangle
 */
extern t_point3d *(*centreGraviteTriangle3d) (t_triangle3d * t);

/* entrée : un triangle 3d
 * sortie : moyenne de la coordonnee x des 3 points du triangle
 */
extern double (*xmoyen) (t_triangle3d * t);

/* entrée : un triangle 3d
 * sortie : moyenne de la coordonnee y des 3 points du triangle
 */
extern double (*ymoyen) (t_triangle3d * t);

/* entrée : un triangle 3d
 * sortie : moyenne de la coordonnee z des 3 points du triangle
 */
extern double (*zmoyen) (t_triangle3d * t);

/* entrée : un triangle 3d a afficher sur la surface, definition de la couleur c de remplissage et des dimensions de la camera l,h, et d distance focale
 * sortie : void
 */
extern void (*remplirTriangle3d) (t_surface * surface, t_triangle3d * triangle, Uint32 c, double l, double h, double d);

/* entrée : un triangle 3d et un vecteur de translation
 * sortie : void
 */
extern void (*translationTriangle3d) (t_triangle3d * t, t_point3d * vecteur);
/* entrée : un triangle 3d, un point 3d centre de roation et 3 angles de rotation
 * sortie : void
 */
extern void (*rotationTriangle3d) (t_triangle3d * t, t_point3d * centre, float degreX, float degreY, float degreZ);
/* entrée : un triangle 3d et une matrice de transformation
 * sortie : void
 */
extern void (*transformationTriangle3d) (t_triangle3d * t, double mat[4][4]);

void usage_lib_3d();

#endif
