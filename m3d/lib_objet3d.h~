#ifndef _LIB_OBJET3D_H_
#define _LIB_OBJET3D_H_

#include "lib_3d.h"

typedef enum {
	false = 0, true
} t_bool;

typedef struct __liste3d t_maillon;

struct __liste3d {
	t_triangle3d *face;
	Uint32 couleur;
	t_maillon *pt_suiv;
};

typedef struct __objet3d t_objet3d;

struct __objet3d {
	t_bool est_trie;
	t_bool est_camera;
	double largeur, hauteur;	// pas de sens si ce n'est pas une camera
	double proche, loin, distance_ecran;	// pas de sens si ce n'est pas une camera
	t_bool possede_texture;
	Uint32 *texture;
	t_maillon *tete;	// pas de sens si c'est une camera
};

extern int nb_faces;

/*
 * Zone PA
 */

t_objet3d *objet_vide_PA();
t_objet3d *objet_fichier_PA(char *fn, Uint32 c1, Uint32 c2);	// retourne l'objet defini dans le fichier .obj
t_objet3d *camera_PA(double l, double h, double n, double f, double d);	// zone l*h dans le champ n->f
t_objet3d *parallelepipede_PA(double lx, double ly, double lz);
t_objet3d *sphere_PA(double r, double nlat, double nlong);
t_objet3d *tore_PA(double r1, double r2, double nlat, double nlong);
t_objet3d *sphere_amiga_PA(double r, double nlat, double nlong);
t_objet3d *arbre_PA(double lx, double ly, double lz);
t_objet3d *damier_PA(double lx, double lz, double nx, double nz);
t_objet3d *sinc_PA(double lx, double lz, double nx, double nz);
t_objet3d *sierpinski_PA(double lx, double ly, double lz, int n);
t_objet3d *copierObjet3d_PA(t_objet3d * o);	// attention, effectue une copie mirroir
void composerObjet3d_PA(t_objet3d * o, t_objet3d * o2);
void libererObjet3d_PA(t_objet3d * o);
t_point3d *centreGraviteObjet3d_PA(t_objet3d * o);
void trierObjet3d_PA(t_objet3d * pt_objet);
void dessinerObjet3d_PA(t_surface * surface, t_objet3d * pt_objet, t_objet3d * camera);

void translationObjet3d_PA(t_objet3d * pt_objet, t_point3d * vecteur);
void rotationObjet3d_PA(t_objet3d * pt_objet, t_point3d * centre, float degreX, float degreY, float degreZ);
void homothetieObjet3d_PA(t_objet3d * pt_objet, float facteurX, float facteurY, float facteurZ);
void transformationObjet3d_PA(t_objet3d * pt_objet, double mat[4][4]);

/*
 * Zone etu
 */

t_objet3d *objet_vide_etu();
t_objet3d *objet_fichier_etu(char *fn, Uint32 c1, Uint32 c2);	// retourne l'objet defini dans le fichier .obj
t_objet3d *camera_etu(double l, double h, double n, double f, double d);	// zone l*h dans le champ n->f
t_objet3d *parallelepipede_etu(double lx, double ly, double lz);
t_objet3d *tore_etu(double r1, double r2, double nlat, double nlong);
t_objet3d *sphere_etu(double r, double nlat, double nlong);
t_objet3d *sphere_amiga_etu(double r, double nlat, double nlong);
t_objet3d *arbre_etu(double lx, double ly, double lz);
t_objet3d *damier_etu(double lx, double lz, double nx, double nz);
t_objet3d *sinc_etu(double lx, double lz, double nx, double nz);
t_objet3d *sierpinski_etu(double lx, double ly, double lz, int n);
t_objet3d *copierObjet3d_etu(t_objet3d * o);
void composerObjet3d_etu(t_objet3d * o, t_objet3d * o2);
void libererObjet3d_etu(t_objet3d * o);
t_point3d *centreGraviteObjet3d_etu(t_objet3d * o);
void trierObjet3d_etu(t_objet3d * pt_objet);
void dessinerObjet3d_etu(t_surface * surface, t_objet3d * pt_objet, t_objet3d * camera);

void translationObjet3d_etu(t_objet3d * pt_objet, t_point3d * vecteur);
void rotationObjet3d_etu(t_objet3d * pt_objet, t_point3d * centre, float degreX, float degreY, float degreZ);
void homothetieObjet3d_etu(t_objet3d * pt_objet, float facteurX, float facteurY, float facteurZ);
void transformationObjet3d_etu(t_objet3d * pt_objet, double mat[4][4]);

/*
 * -------------------------------------------
 */

/* entrée : void
 * sortie : un objet 3d initialisé, mais vide
 */
extern t_objet3d *(*objet_vide) ();

/* entrée : un nom de fichier .obj, deux couleurs
 * sortie : un objet 3d initialisé, les faces sont colorees aleatoirement entre c1 et c2 (via utilisation de la fonction couleur_entre de lib_surface et rand() entre 1 et 100)
 */
extern t_objet3d *(*objet_fichier) (char *fn, Uint32 c1, Uint32 c2);


/* entrée : largeur et hauteur de l'ouverture de la camera, distance proche (near) et loin (far) de l'espace 3d, distance focale de la camera
 * sortie : un objet 3d caméra, ne contient pas de face
 */
extern t_objet3d *(*camera) (double l, double h, double n, double f, double d);


/* entrée : longueur sur les 3 axes du parallelepipede
 * sortie : un objet 3d initialisé, 12 faces
 */
extern t_objet3d *(*parallelepipede) (double lx, double ly, double lz);


/* entrée : rayon, latitude et longitude du tore
 * sortie : un objet 3d initialisé
 */
extern t_objet3d *(*tore) (double r1, double r2, double nlat, double nlong);


/* entrée : rayon, latitude et longitude de la sphere
 * sortie : un objet 3d initialisé
 */
extern t_objet3d *(*sphere) (double r, double nlat, double nlong);


/* entrée : rayon, latitude et longitude de la sphere
 * sortie : un objet 3d initialisé, les faces sont alternativement rouges et blanches
 */
extern t_objet3d *(*sphere_amiga) (double r, double nlat, double nlong);


/* entrée : taille sur les 3 axes de l'arbre
 * sortie : un objet 3d initialisé, un parallelepipede avec une pyramide au sommet
 */
extern t_objet3d *(*arbre) (double lx, double ly, double lz);


/* entrée : taille du damier et nombre de carreaux sur les deux axes
 * sortie : un objet 3d initialisé, faces alternativement noires et blanches
 */
extern t_objet3d *(*damier) (double lx, double lz, double nx, double nz);


/* entrée : taille du damier et nombre de carreaux sur les deux axes
 * sortie : un objet 3d initialisé, surface en forme de sinc(x)=sin(x)/x
 */
extern t_objet3d *(*sinc) (double lx, double lz, double nx, double nz);


/* entrée : taille de l'objet et nombre d'iteration rec
 * sortie : un objet 3d initialisé, fractale triangle de sierpinski
 */
extern t_objet3d *(*sierpinski) (double lx, double ly, double lz, int n);


/* entrée : un objet 3d
 * sortie : un objet 3d qui contient une copie de toutes les faces de l'objet en entrée (création de nouveaux triangles)
 */
extern t_objet3d *(*copierObjet3d) (t_objet3d * o);


/* entrée : deux objets 3d à concaténer : attention, l'objet 2 est ajouté à l'objet 1, il ne sera donc plus utilisable
 * sortie : void
 */
extern void (*composerObjet3d) (t_objet3d * o, t_objet3d * o2);


/* entrée : un objet 3d, toutes les mémoires utilisées par l'objets sont libérées
 * sortie : void
 */
extern void (*libererObjet3d) (t_objet3d * o);


/* entrée : un objet 3d
 * sortie : un point 3d au centre de gravité de l'objet
 */
extern t_point3d *(*centreGraviteObjet3d) (t_objet3d * o);


/* entrée : un objet 3d
 * sortie : void
 */
extern void (*trierObjet3d) (t_objet3d * pt_objet);


/* entrée : un objet 3d a afficher
 * sortie : void
 */
extern void (*dessinerObjet3d) (t_surface * surface, t_objet3d * pt_objet, t_objet3d * camera);


/* entrée : un objet 3d et un vecteur de translation
 * sortie : void
 */
extern void (*translationObjet3d) (t_objet3d * pt_objet, t_point3d * vecteur);


/* entrée : un objet 3d, un point 3d centre de rotation et 3 angles de rotation
 * sortie : void
 */
extern void (*homothetieObjet3d) (t_objet3d * pt_objet, float facteurX, float facteurY, float facteurZ);


/* entrée : un objet 3d, un point 3d centre de rotation et 3 angles de rotation
 * sortie : void
 */
extern void (*rotationObjet3d) (t_objet3d * pt_objet, t_point3d * centre, float degreX, float degreY, float degreZ);


/* entrée : un objet 3d et une matrice de transformation
 * sortie : void
 */
extern void (*transformationObjet3d) (t_objet3d * pt_objet, double mat[4][4]);

void usage_lib_objet_3d();

#endif
