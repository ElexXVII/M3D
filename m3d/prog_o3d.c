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

	t_point3d *position_o3d = definirPoint3d(0, 0, -100);	/* rotation par rapport au referentiel de l'objet */

	t_objet3d *o = parallelepipede(50, 50, 50);
	translationObjet3d(o, position_o3d);

	t_objet3d *cam = camera(1, 1, -50, -500, -100);	/* aspect l,h, distance near, far et screen */

	surface = creerFenetre(RX, RY);
	timestart = SDL_GetTicks();
	oldtime = timestart;

	i = 0;
	while (event.type != SDL_QUIT) {
		effacerEcran(surface);

		SDL_PollEvent(&event);

		rotationObjet3d(o, position_o3d, 0, 5, 0);

		dessinerObjet3d(surface, o, cam);

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

	libererPoint3d(position_o3d);
	libererObjet3d(o);

	libererFenetre(surface);

	usage_lib_3d();
	usage_lib_objet_3d();
	usage_lib_scene_3d();

	return 0;
}
