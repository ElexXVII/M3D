#include "lib_3d.h"
#include "lib_mat.h"

t_point3d *definirPoint3d_etu(double x, double y, double z)	// attention malloc
{
	t_point3d *p;

	p = (t_point3d *) malloc(sizeof(t_point3d));
	if (p != NULL) {
		p->xyzt[0] = x;
		p->xyzt[1] = y;
		p->xyzt[2] = z;
		p->xyzt[3] = 1;
	}

	return p;
}

t_point3d *definirVecteur3d_etu(double x, double y, double z)	// attention malloc
{
	t_point3d *p;

	p = (t_point3d *) malloc(sizeof(t_point3d));
	if (p != NULL) {
		p->xyzt[0] = x;
		p->xyzt[1] = y;
		p->xyzt[2] = z;
		p->xyzt[3] = 0;
	}

	return p;
}

t_point3d *copierPoint3d_etu(t_point3d * p)	// attention malloc
{
	return definirPoint3d(p->xyzt[0], p->xyzt[1], p->xyzt[2]);
}

void libererPoint3d_etu(t_point3d * p)
{
	free(p);
}

t_triangle3d *definirTriangle3d_etu(t_point3d * a, t_point3d * b, t_point3d * c)	// attention malloc
{
	t_triangle3d *T;
	T = (t_triangle3d *) malloc(sizeof(t_triangle3d));
	T->abc[0] = a;
	T->abc[1] = b;
	T->abc[2] = c;
	return T;
}

t_triangle3d *copierTriangle3d_etu(t_triangle3d * t)	// attention malloc multiples
{
	return definirTriangle3d(copierPoint3d(t->abc[0]), copierPoint3d(t->abc[1]), copierPoint3d(t->abc[2]));
}

void libererTriangle3d_etu(t_triangle3d * t)
{
	free(t);
}

double xmoyen_etu(t_triangle3d * t)
{
	double mx = (((t->abc[0])->xyzt[0])+((t->abc[1])->xyzt[0])+((t->abc[2])->xyzt[0]))/3;
	return mx;
}

double ymoyen_etu(t_triangle3d * t)
{
	double my = (((t->abc[0])->xyzt[1])+((t->abc[1])->xyzt[1])+((t->abc[2])->xyzt[1]))/3;
	return my;
}

double zmoyen_etu(t_triangle3d * t)
{
	double mz = (((t->abc[0])->xyzt[2])+((t->abc[1])->xyzt[2])+((t->abc[2])->xyzt[2]))/3;
	return mz;
}

t_point3d *centreGraviteTriangle3d_etu(t_triangle3d * t)	// attention malloc (definirPoint)
{
	t_point3d *p = definirPoint3d(xmoyen(t),ymoyen(t),zmoyen(t));
	return p;
}

void remplirTriangle3d_etu(t_surface * surface, t_triangle3d * triangle, Uint32 c, double l, double h, double d)
{
	t_point2d *p0 = definirPoint2d(0,0);	
	t_point2d *p1 = definirPoint2d(0,0);
	t_point2d *p2 = definirPoint2d(0,0);
	t_triangle2d *t2d = definirTriangle2d(p0, p1, p2);
	int i;
	double n;
	for(i=0;i<3;i++)
	{
		n = ((triangle->abc[i])->xyzt[2])/d;
		(t2d->t[i]).x = (int)floor(((triangle->abc[i])->xyzt[0])/n)+RX/2;
		(t2d->t[i]).y = -(int)floor(((triangle->abc[i])->xyzt[1])/n)+RY/2;
	}
	//printf("1\n");
	//printf("%f, %f, %f\n",((triangle->abc[0])->xyzt[2])/d, ((triangle->abc[1])->xyzt[2])/d, ((triangle->abc[2])->xyzt[2])/d);
	//printf("%d, %d\n",t2d->t[1].x, t2d->t[1].y);
	//printf("%d, %d\n",t2d->t[2].x, t2d->t[2].y);
	remplirTriangle2d(surface,t2d,c);
	libererTriangle2d(t2d);
	libererPoint2d(p0);
	libererPoint2d(p1);
	libererPoint2d(p2);	
	//printf("remplir Fin\n");
}

void translationTriangle3d_etu(t_triangle3d * t, t_point3d * vecteur)
{
	int i;
	int j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			(t->abc[i])->xyzt[j] += vecteur->xyzt[j];	
		}
	}
}

void rotationTriangle3d_etu(t_triangle3d * t, t_point3d * centre, float degreX, float degreY, float degreZ)
{
	double conv = M_PI/180;
	double a = degreX*conv;
	double b = degreY*conv;
	double g = degreZ*conv;
	double tran[4][4] = {	{cos(a)*cos(g),				-sin(g)*cos(b),				sin(b),			centre->xyzt[0]},
				{sin(a)*sin(b)*cos(g)+cos(a)*sin(g),	sin(a)*sin(b)*sin(g)+cos(a)*cos(g),	-sin(a)*cos(b),		centre->xyzt[1]},
				{-sin(b)*cos(a)*cos(g)+sin(a)*sin(g),	sin(g)*sin(b)*cos(a)+sin(a)*cos(g),	cos(a)*cos(b),		centre->xyzt[2]},
				{0,					0,					0,			1	       }
			    };
	transformationTriangle3d(t,tran);
}	

void transformationTriangle3d_etu(t_triangle3d * t, double mat[4][4])
{
	t_triangle3d * t2 = definirTriangle3d(copierPoint3d(t->abc[0]), copierPoint3d(t->abc[1]), copierPoint3d(t->abc[2]));

	int i;
	for(i=0;i<3;i++)
	{
		multiplication_vecteur(t->abc[i],mat,t2->abc[i]);
	}
}

void homothetieTriangle3d_etu(t_triangle3d * t, float facteurX, float facteurY, float facteurZ)
{
	int i;
	for(i=0;i<3;i++)
	{
		(t->abc[i])->xyzt[0] *= facteurX;
		(t->abc[i])->xyzt[1] *= facteurY;
		(t->abc[i])->xyzt[2] *= facteurZ;	
	}
}
