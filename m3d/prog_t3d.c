#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "lib_scene3d.h"

#define N_CAMERA 3
#define DUREE 10*60
#define CIBLE_FPS 60

SDL_Event event;

int main(int argc, char **argv)
{
	t_surface *surface = NULL;
	int cpt = 0;
	Uint32 timestart, oldtime;
	char buf[50];

	int i;

	t_point3d *origine = definirPoint3d(0, 0, -150);
	t_point3d *a = definirPoint3d(0, 0, -150);
	t_point3d *b = definirPoint3d(150, 0, -150);
	t_point3d *c = definirPoint3d(0, 150, -150);

	t_triangle3d *t = definirTriangle3d(a, b, c);

	surface = creerFenetre(RX, RY);
	timestart = SDL_GetTicks();
	oldtime = timestart;

	i = 0;
	while (event.type != SDL_QUIT) {
		effacerEcran(surface);

		SDL_PollEvent(&event);

		rotationTriangle3d(t, origine, 0, 5, 0);

		/* attention dans cet exemple il n'y a pas de controle particulier sur l'affichabilite du point par rapport a la camera */
		remplirTriangle3d(surface, t, ROUGEC, 1, 1, -30);

		majEcran(surface);

		/* Framerate fixe a env 60 FPS max */
		//SDL_Delay((1000 / CIBLE_FPS) - MIN((1000 / CIBLE_FPS), (SDL_GetTicks() - oldtime)));
		SDL_Delay(100);
		oldtime = SDL_GetTicks();

		cpt++;
		snprintf(buf, sizeof(buf), "%d FPS", (int)(cpt * 1000.0 / (oldtime - timestart)));
		// petite fuite de memoire lors de cet appel, non resolue pour le moment...
		definirTitreFenetre(surface, buf);

		i = i + 1;
	}

	libererPoint3d(origine);
	libererPoint3d(a);
	libererPoint3d(b);
	libererPoint3d(c);
	libererTriangle3d(t);

	libererFenetre(surface);

	usage_lib_3d();
	usage_lib_objet_3d();
	usage_lib_scene_3d();

	return 0;
}
