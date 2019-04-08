#include "lib_3d.h"
#include "lib_objet3d.h"
#include "lib_scene3d.h"

t_point3d *(*definirPoint3d) (double x, double y, double z) = definirPoint3d_etu; // Done
t_point3d *(*definirVecteur3d) (double x, double y, double z) = definirVecteur3d_etu; // Done
t_point3d *(*copierPoint3d) (t_point3d * p) = copierPoint3d_etu; // Done
void (*libererPoint3d) (t_point3d * p) = libererPoint3d_etu; // Done

t_triangle3d *(*definirTriangle3d) (t_point3d * a, t_point3d * b, t_point3d * c) = definirTriangle3d_etu; // Done
t_triangle3d *(*copierTriangle3d) (t_triangle3d * t) = copierTriangle3d_etu; // Done
void (*libererTriangle3d) (t_triangle3d * t) = libererTriangle3d_etu; // Done
void (*differenceVecteur3d) (t_point3d * v1, t_point3d * v2) = differenceVecteur3d_PA;
void (*sommeVecteur3d) (t_point3d * v1, t_point3d * v2) = sommeVecteur3d_PA;
void (*divisionVecteur3d) (t_point3d * v1, int n) = divisionVecteur3d_PA;
t_point3d *(*centreGraviteTriangle3d) (t_triangle3d * t) = centreGraviteTriangle3d_etu; // Done

double (*xmoyen) (t_triangle3d * t) = xmoyen_etu; // Done
double (*ymoyen) (t_triangle3d * t) = ymoyen_etu; // Done
double (*zmoyen) (t_triangle3d * t) = zmoyen_etu; // Done
void (*remplirTriangle3d) (t_surface * surface, t_triangle3d * triangle, Uint32 c, double l, double h, double d) = remplirTriangle3d_etu; // Done
void (*translationTriangle3d) (t_triangle3d * t, t_point3d * vecteur) = translationTriangle3d_etu; // Done
void (*rotationTriangle3d) (t_triangle3d * t, t_point3d * centre, float degreX, float degreY, float degreZ) = rotationTriangle3d_etu; // Done
void (*transformationTriangle3d) (t_triangle3d * t, double mat[4][4]) = transformationTriangle3d_etu; // Done

t_objet3d *(*objet_vide) () = objet_vide_etu; // Done
t_objet3d *(*objet_fichier) (char *fn, Uint32 c1, Uint32 c2) = objet_fichier_PA;
t_objet3d *(*camera) (double l, double h, double n, double f, double d) = camera_etu; // Done
t_objet3d *(*parallelepipede) (double lx, double ly, double lz) = parallelepipede_PA;
t_objet3d *(*tore) (double r1, double r2, double nlat, double nlong) = tore_PA;
t_objet3d *(*sphere) (double r, double nlat, double nlong) = sphere_PA;
t_objet3d *(*sphere_amiga) (double r, double nlat, double nlong) = sphere_amiga_PA;
t_objet3d *(*arbre) (double lx, double ly, double lz) = arbre_PA;
t_objet3d *(*damier) (double lx, double lz, double nx, double nz) = damier_etu; // Done
t_objet3d *(*sinc) (double lx, double lz, double nx, double nz) = sinc_PA;
t_objet3d *(*sierpinski) (double lx, double ly, double lz, int n) = sierpinski_PA;
t_objet3d *(*copierObjet3d) (t_objet3d * o) = copierObjet3d_etu; // Done
void (*composerObjet3d) (t_objet3d * o, t_objet3d * o2) = composerObjet3d_etu; // Done
void (*libererObjet3d) (t_objet3d * o) = libererObjet3d_etu; // Done
t_point3d *(*centreGraviteObjet3d) (t_objet3d * o) = centreGraviteObjet3d_PA;
void (*trierObjet3d) (t_objet3d * pt_objet) = trierObjet3d_PA;
void (*dessinerObjet3d) (t_surface * surface, t_objet3d * pt_objet, t_objet3d * camera) = dessinerObjet3d_etu; // Done ~

void (*translationObjet3d) (t_objet3d * pt_objet, t_point3d * vecteur) = translationObjet3d_etu; // Done
void (*rotationObjet3d) (t_objet3d * pt_objet, t_point3d * centre, float degreX, float degreY, float degreZ) = rotationObjet3d_etu; // Done
void (*homothetieObjet3d) (t_objet3d * pt_objet, float facteurX, float facteurY, float facteurZ) = homothetieObjet3d_etu; // Done
void (*transformationObjet3d) (t_objet3d * pt_objet, double mat[4][4]) = transformationObjet3d_etu; // Done

t_scene3d *(*definirScene3d) (t_objet3d * pt_objet) = definirScene3d_PA; // Probleme
t_scene3d *(*ajouter_relation) (t_scene3d * pt_feuille, t_objet3d * pt_objet) = ajouter_relation_PA;
void (*translationScene3d) (t_scene3d * pt_scene, t_point3d * vecteur) = translationScene3d_PA;
void (*rotationScene3d) (t_scene3d * pt_scene, t_point3d * centre, float degreX, float degreY, float degreZ) = rotationScene3d_PA;
void (*dessinerScene3d) (t_surface * surface, t_scene3d * pt_scene) = dessinerScene3d_PA;
void (*libererScene3d) (t_scene3d * pt_scene) = libererScene3d_etu; // Done
