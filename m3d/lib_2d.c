#include "lib_2d.h"

t_point2d *definirPoint2d(int x, int y)	// attention malloc il faut penser au free pour les retours
{
	t_point2d *p;

	p = (t_point2d *) malloc(sizeof(t_point2d));

	p->x = x;
	p->y = y;

	return p;
}

#if 0
#define __copierPoint2d(src, dest)	memcpy(dest, src, sizeof(t_point2d))
#else
void __copierPoint2d(t_point2d * src, t_point2d * dest)	// pas d'allocation de memoire il faut un dest deja alloue, fonction en dehors du .h cependant
{
	dest->x = src->x;
	dest->y = src->y;
}
#endif

void libererPoint2d(t_point2d * p)
{
	free(p);
}

t_triangle2d *definirTriangle2d(t_point2d * a, t_point2d * b, t_point2d * c)	// attention malloc
{
	t_triangle2d *t;

	t = (t_triangle2d *) malloc(sizeof(t_triangle2d));

	__copierPoint2d(a, &(t->t[0]));
	__copierPoint2d(b, &(t->t[1]));
	__copierPoint2d(c, &(t->t[2]));

	return t;
}

void libererTriangle2d(t_triangle2d * t)
{
	free(t);
}

void __echangerPointsTriangle(t_triangle2d * triangle, int a, int b)
{
	t_point2d p;

	__copierPoint2d(&(triangle->t[a]), &p);	// copierp2d ne fait pas de malloc...
	__copierPoint2d(&(triangle->t[b]), &(triangle->t[a]));	// copierp2d ne fait pas de malloc...
	__copierPoint2d(&p, &(triangle->t[b]));	// copierp2d ne fait pas de malloc...
}

void __ordonnerPointsTriangle(t_triangle2d * triangle)
{				/* ordonne dans le sens croissant des y */
	if (triangle->t[0].y > triangle->t[1].y) {	/* on passe le plus grand des
							   deux premier au milieu */
		__echangerPointsTriangle(triangle, 0, 1);
	}
	if (triangle->t[1].y > triangle->t[2].y) {	/* on passe le plus grand des
							   deux dernier au fin */
		__echangerPointsTriangle(triangle, 1, 2);
	}
	if (triangle->t[0].y > triangle->t[1].y) {	/* on passe le plus grand des
							   deux premier au milieu */
		__echangerPointsTriangle(triangle, 0, 1);
	}
}

void __majMinMax(t_surface * surface, int x, int y, int *xmin, int *xmax)
{
	if (x < 0)
		x = 0;
	if (x > t_surface_x(surface) - 1)
		x = t_surface_x(surface) - 1;
	if (y > 0 && y < t_surface_y(surface)) {
		if (x < xmin[y])
			xmin[y] = x;
		if (x > xmax[y])
			xmax[y] = x;
	}
}

#if 0
/*
 * Algo de Bresenham
 * en realite, il y a une reduction de perfs par rapport a la version naive...
 */
void __calculerBornes(t_surface * surface, int xi, int yi, int xf, int yf, int *xmin, int *xmax, int ymin)
{
	int cumul;
	int i;
	int x = xi, y = yi;
	int dx = xf - xi;
	int dy = yf - yi;
	int xinc = (dx > 0) ? 1 : -1;
	int yinc = (dy > 0) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);

	if (dx > dy) {
		cumul = dx / 2;
		for (i = 0; i < dx; i++) {
			x += xinc;
			cumul += dy;
			if (cumul > dx) {
				cumul -= dx;
				y += yinc;
			}

			__majMinMax(surface, x, y, xmin, xmax);
		}
	} else {
		cumul = dy / 2;
		for (i = 0; i < dy; i++) {
			y += yinc;
			cumul += dx;
			if (cumul > dy) {
				cumul -= dy;
				x += xinc;
			}
			__majMinMax(surface, x, y, xmin, xmax);
		}
	}

}
#else
void __calculerBornes(t_surface * surface, int xi, int yi, int xf, int yf, int *xmin, int *xmax, int ymin)
{

	double a, b;
	int i;

	if (xi != xf && yi != yf)	// segment oblique, calcul du coeff directeur de la droite affine passant par les deux points
	{
		a = ((double)(yf - yi)) / (xf - xi);
		b = yf - a * xf;

		for (i = MIN(yi, yf); i < MAX(yi, yf); i++) {
			__majMinMax(surface, (int)((i - b) / a), i, xmin, xmax);
		}
	} else if (xi == xf) {
		for (i = MIN(yi, yf); i < MAX(yi, yf); i++) {
			__majMinMax(surface, xi, i, xmin, xmax);
		}
	} else {
		for (i = MIN(xi, xf); i < MAX(xi, xf); i++) {
			__majMinMax(surface, i, yi, xmin, xmax);
		}
	}

}
#endif

void __afficherTriangle2d(t_triangle2d * triangle)
{
	printf("%d %d - %d %d - %d %d\n", triangle->t[0].x, triangle->t[0].y, triangle->t[1].x, triangle->t[1].y, triangle->t[2].x, triangle->t[2].y);
	fflush(stdout);
}

void remplirTriangle2d(t_surface * surface, t_triangle2d * triangle, Uint32 c)
{
	int ymin, ymax;
	int *xmin = t_surface_xmin(surface), *xmax = t_surface_xmax(surface);
	int y;			//, x;

	__ordonnerPointsTriangle(triangle);
//      __afficherTriangle2d(triangle);

	ymin = triangle->t[0].y;
	ymax = triangle->t[2].y;

#if 0
	// réalisé aux lignes 213 et 214...
	memset(xmax, 0, (size_t) t_surface_Y(surface) * sizeof(int));
	memset(xmin, t_surface_X(surface) - 1, (size_t) t_surface_Y(surface) * sizeof(int));
#endif

	__calculerBornes(surface, triangle->t[0].x, triangle->t[0].y, triangle->t[2].x, triangle->t[2].y, xmin, xmax, ymin);
	__calculerBornes(surface, triangle->t[0].x, triangle->t[0].y, triangle->t[1].x, triangle->t[1].y, xmin, xmax, ymin);
	__calculerBornes(surface, triangle->t[1].x, triangle->t[1].y, triangle->t[2].x, triangle->t[2].y, xmin, xmax, ymin);

	for (y = MAX(0, ymin); y <= MIN(t_surface_y(surface) - 1, ymax); y++) {
		if (xmin[y] < xmax[y]) {
			remplirLigneHorizontale(surface, xmin[y], y, xmax[y] - xmin[y], c);
		}
//              majEcran(surface);
		xmax[y] = 0;
		xmin[y] = t_surface_x(surface) - 1;
	}
}
