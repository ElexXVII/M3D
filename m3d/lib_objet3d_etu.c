#include <assert.h>
#include <math.h>
#include <float.h>
#include "lib_mat.h"
#include "lib_objet3d.h"

int nb_faces = 0;
int debug = 0;


void insere_maillon(t_objet3d * pt_objet, t_maillon * pt_maillon)
{
	if(pt_objet->tete != NULL)
	{
		t_maillon *cursor_m = pt_objet->tete;

		while(cursor_m->pt_suiv != NULL)
		{
			cursor_m = cursor_m->pt_suiv;
		}	

		cursor_m->pt_suiv = pt_maillon;
	}
}

t_maillon *__cree_maillon(t_triangle3d * face, Uint32 couleur)
{
	t_maillon *m = (t_maillon *) malloc(sizeof(t_maillon));
	m->face = face;
	m->couleur = couleur;
	m->pt_suiv = NULL; 
	return m;
}

void __insere_tete(t_objet3d * pt_objet, t_maillon * pt_maillon)
{
	pt_objet->tete = pt_maillon;
}

/*
 * CREATION DES OBJETS
 */

t_objet3d *objet_vide_etu()
{
	t_objet3d * o = (t_objet3d *) malloc(sizeof(t_objet3d));
	o->est_trie = true;
	o->est_camera = false;
	o->largeur = 0;
	o->hauteur = 0;
	o->proche = 0;
	o->loin = 0;
	o->distance_ecran = 0;
	o->possede_texture = false;
	o->texture = NULL; //0xF4CE42;
	o->tete = NULL;
	return o;
}

t_objet3d *camera_etu(double l, double h, double n, double f, double d)
{
	t_objet3d *pt_objet = objet_vide();
	pt_objet->est_camera = true;
	pt_objet->largeur = l;
	pt_objet->hauteur = h;
	pt_objet->proche = n;
	pt_objet->loin = f;
	pt_objet->distance_ecran = d;
	return pt_objet;
}

t_objet3d *objet_fichier_etu(char *fn, Uint32 c1, Uint32 c2)
{
	t_objet3d *pt_objet = objet_vide();
	return pt_objet;
}

t_objet3d *parallelepipede_etu(double lx, double ly, double lz)
{
	t_objet3d *pt_objet = objet_vide();
	return pt_objet;
}

t_objet3d *tore_etu(double r1, double r2, double nlat, double nlong)
{
	t_objet3d *pt_objet = objet_vide();
	return pt_objet;
}

t_objet3d *sphere_etu(double r, double nlat, double nlong)
{
	t_objet3d *pt_objet = objet_vide();
	return pt_objet;
}

t_objet3d *sphere_amiga_etu(double r, double nlat, double nlong)
{
	t_objet3d *pt_objet = objet_vide();
	return pt_objet;
}

t_objet3d *arbre_etu(double lx, double ly, double lz)
{
	t_objet3d *pt_objet = objet_vide();
	return pt_objet;
}

t_objet3d *sinc_etu(double lx, double lz, double nx, double nz)
{
	t_objet3d *pt_objet = objet_vide();
	return pt_objet;
}

t_objet3d *damier_etu(double lx, double lz, double nx, double nz)
{
	unsigned int x = (unsigned int)nx;
	unsigned int z = (unsigned int)nz;
	t_objet3d *pt_objet = objet_vide();
	t_point3d **lp = malloc(sizeof(t_point3d)*(x+1)*(z+1));
	t_maillon *Mtemp;
	t_triangle3d *t1;
	t_triangle3d *t2;
	int i;
	int j;
	for(i=0;i<nx+1;i++)
	{
		for(j=0;j<nz+1;j++)
		{
			lp[i*((int)x+1)+j] = definirPoint3d(i*lx/nx-lx/2,0,j*lz/nz-lz/2);
		}
	}
	for(i=0;i<nx;i++)
	{
		for(j=0;j<nz;j++)
		{
			t1 = definirTriangle3d(lp[i*((int)x+1)+j],lp[i*((int)x+1)+(j+1)],lp[(i+1)*((int)x+1)+j]);
			t2 = definirTriangle3d(lp[(i+1)*((int)x+1)+(j+1)],lp[i*((int)x+1)+(j+1)],lp[(i+1)*((int)x+1)+j]);
			t_maillon *M1 = __cree_maillon(t1, (((i+j)%2==0)?0x00333333:0xffffffff));
			t_maillon *M2 = __cree_maillon(t2, (((i+j)%2==0)?0x00333333:0xffffffff));
			if(i==0 && j==0)
			{
				__insere_tete(pt_objet,M1);
			}
			else
			{
				Mtemp->pt_suiv = M1;
			}
			M1->pt_suiv = M2;
			Mtemp = M2;
		}
	}
	return pt_objet;
}

t_objet3d *sierpinski_etu(double lx, double ly, double lz, int n)
{
	t_objet3d *pt_objet = objet_vide();
	return pt_objet;
}

/*
 * GESTION DES OBJETS
 */

t_objet3d *copierObjet3d_etu(t_objet3d * o)	// retourne une copie de o
{
	t_objet3d *pt_objet = objet_vide();
	if(o->tete != NULL)
	{	
		t_maillon *cursor = o->tete;
		t_maillon *newtete = __cree_maillon(copierTriangle3d(cursor->face),cursor->couleur);
		__insere_tete(pt_objet, newtete);

		while(cursor->pt_suiv != NULL)
		{
			cursor = cursor->pt_suiv;
			insere_maillon(pt_objet, __cree_maillon(copierTriangle3d(cursor->face),cursor->couleur));
		}

	}
	return pt_objet;
}

void composerObjet3d_etu(t_objet3d * o, t_objet3d * o2)
{		/* o = o+o2, o2 ne signifiera plus rien */
	if(o2->tete != NULL)
	{
		if (o->tete == NULL)
		{
			o->tete = o2->tete;
		}
		else
		{
			insere_maillon(o,o2->tete);
		}
	}
	//trierObjet3d(o);
	o->est_trie = false;
}

void libererMaillonRec(t_maillon *m)
{
	if(m->pt_suiv != NULL)
	{
		libererMaillonRec(m->pt_suiv);
	}
	//m->pt_suiv = NULL;
	free(m);
}

void libererObjet3d_etu(t_objet3d * o)
{
	if(o->tete != NULL)
	{
		libererMaillonRec(o->tete);
	}
	//o->tete = NULL;
	free(o);
}

t_point3d *centreGraviteObjet3d_etu(t_objet3d * o)	//attention malloc (definirVecteur)
{
	
	t_point3d *g = definirVecteur3d(0,0,0);
	return g;
}

void trierObjet3d_etu(t_objet3d * pt_objet)
{
}

void dessinerObjet3d_etu(t_surface * surface, t_objet3d * pt_objet, t_objet3d * camera)
{
	debug = 0;
	trierObjet3d(pt_objet);
	t_maillon *cursor = pt_objet->tete;
	//printf("%f %f %f\n", g->xyzt[0], g->xyzt[1], g->xyzt[2]);

	while(cursor != NULL)
	{	
		t_point3d *g = centreGraviteTriangle3d(cursor->face);
		double d =  sqrt(pow(g->xyzt[0],2)+ pow(g->xyzt[1],2)+ pow(g->xyzt[2],2));
		double z1 = cursor->face->abc[0]->xyzt[2];
		double z2 = cursor->face->abc[1]->xyzt[2];
		double z3 = cursor->face->abc[2]->xyzt[2];
		//debug++;
		if(z1 <= -0.0000001 && z2 <= -0.0000001 && z3 <= -0.0000001 && d >= 100)
		{
			remplirTriangle3d(surface, cursor->face, cursor->couleur, camera->largeur, camera->hauteur, camera->distance_ecran);
		}
		cursor = cursor->pt_suiv;
	}
}

/*
 * TRANSFORMATION DES OBJETS
 */

void translationObjet3d_etu(t_objet3d * pt_objet, t_point3d * vecteur)
{
	t_maillon *cursor = pt_objet->tete;
	while(cursor != NULL)
	{
		translationTriangle3d(cursor->face,vecteur);
		cursor = cursor->pt_suiv;
	}
}

void homothetieObjet3d_etu(t_objet3d * pt_objet, float facteurX, float facteurY, float facteurZ)
{
	t_maillon *cursor = pt_objet->tete;
	while(cursor != NULL)
	{
		homothetieTriangle3d_etu(cursor->face,facteurX, facteurY, facteurZ);
		cursor = cursor->pt_suiv;
	}
}

void rotationObjet3d_etu(t_objet3d * pt_objet, t_point3d * centre, float degreX, float degreY, float degreZ)
{
	t_maillon *cursor = pt_objet->tete;
	while(cursor != NULL)
	{
		rotationTriangle3d(cursor->face, centre, degreX, degreY, degreZ);
		cursor = cursor->pt_suiv;
	}
}

void transformationObjet3d_etu(t_objet3d * pt_objet, double mat[4][4])
{
	t_maillon *cursor = pt_objet->tete;
	while(cursor != NULL)
	{
		transformationTriangle3d(cursor->face, mat);
		cursor = cursor->pt_suiv;
	}
}
