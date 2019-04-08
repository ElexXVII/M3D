#include <assert.h>
#include <math.h>
#include "lib_mat.h"
#include "lib_scene3d.h"

/*
 * GESTION DES SCENES
 */

void matNulle(double mat[4][4])
{
	int i;
	int j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			mat[i][j] = 0;
		}		
	}
}

t_scene3d *definirScene3d_etu(t_objet3d * pt_objet)
{
	t_scene3d *scene = (t_scene3d *) malloc(sizeof(t_scene3d));
	scene->objet = pt_objet;
	double mN[4][4];
	matNulle(mN);
	//scene->descendant = MATRICE_IDENTITE;
	//scene->montant = MATRICE_IDENTITE;
	scene->pt_pere = NULL;
	scene->pt_suiv = NULL;

	scene->pt_fils = NULL;

	return scene;
}

t_scene3d *ajouter_relation_etu(t_scene3d * pt_feuille, t_objet3d * pt_objet)	// ajout de l'objet en tete des fils
{

	return NULL;
}

t_point3d *centreGraviteScene3d_etu(t_scene3d * pt_scene)
{

	return NULL;
}

void dessinerScene3d_etu(t_surface * surface, t_scene3d * scn_camera)
{
}

void libererScene3d_etu(t_scene3d * scene)
{
	if(scene->pt_fils != NULL)
	{
		libererScene3d(scene->pt_fils);
	}
	if(scene->pt_suiv != NULL)
	{
		libererScene3d(scene->pt_suiv);
	}
	free(scene);
}
/*
 * TRANSFORMATIONS DES SCENES
 */

void translationScene3d_etu(t_scene3d * pt_scene, t_point3d * vecteur)
{
}

void rotationScene3d_etu(t_scene3d * pt_scene, t_point3d * centre, float degreX, float degreY, float degreZ)
{
}
