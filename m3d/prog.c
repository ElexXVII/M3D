#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "lib_scene3d.h"

#define N_CAMERA 3
#define DUREE 10*60
#define CIBLE_FPS 60

SDL_Event event;
int x = 0, y = 0;
t_scene3d *camera_active, *cams[N_CAMERA];
t_bool is_button_down = false;
const Uint8 *currentKeyStates = NULL;

#if 0
void handle_events()
{
#if 0
	if (event.type == SDL_MOUSEMOTION && is_button_down) {
		int xd, yd;
		t_point3d *centre = definirPoint3d(0, 0, 0);

		xd = event.motion.x;
		yd = event.motion.y;

		//rotation de la camra active
		// definition : 100px = rotation de 90Â° sur un axe
		rotationScene3d(camera_active, centre, 0, 90.0 * (xd - x) / 100.0, 0);
		rotationScene3d(camera_active, centre, 90.0 * (yd - y) / 100.0, 0, 0);

		x = xd;
		y = yd;

		free(centre);

	} else if (event.type == SDL_MOUSEBUTTONDOWN) {
		is_button_down = true;
		x = event.motion.x;
		y = event.motion.y;
	} else if (event.type == SDL_MOUSEBUTTONUP) {
		is_button_down = false;
	} else {
	collect2: ld a retourné 1 code d'état d'exécution
make: *** [prog] Erreur 1
ariviere@abe-a-03:~/travail/M3D/m3d$ 
	const Uint8 *currentKeyStates = SDL_GetKeyState(NULL);
		if (currentKeyStates[SDLK_UP]) {
			t_point3d *deplacement = definirVecteur3d(0, 0, -10);
			translationScene3d(camera_active, deplacement);
			free(deplacement);
		} else if (currentKeyStates[SDLK_DOWN]) {
			t_point3d *deplacement = definirVecteur3d(0, 0, 10);
			translationScene3d(camera_active, deplacement);
			free(deplacement);
		} else if (currentKeyStates[SDLK_z]) {
			t_point3d *deplacement = definirVecteur3d(0, 10, 0);
			translationScene3d(camera_active, deplacement);
			free(deplacement);
		} else if (currentKeyStates[SDLK_s]) {
			t_point3d *deplacement = definirVecteur3d(0, -10, 0);
			translationScene3d(camera_active, deplacement);
			free(deplacement);
		} else if (currentKeyStates[SDLK_LEFT]) {
			t_point3d *deplacement = definirVecteur3d(-10, 0, 0);
			translationScene3d(camera_active, deplacement);
			free(deplacement);
		} else if (currentKeyStates[SDLK_RIGHT]) {
			t_point3d *deplacement = definirVecteur3d(10, 0, 0);
			translationScene3d(camera_active, deplacement);
			free(deplacement);
		} else if (currentKeyStates[SDLK_j]) {
			camera_active = cams[0];
		} else if (currentKeyStates[SDLK_k]) {
			camera_active = cams[1];
		} else if (currentKeyStates[SDLK_l]) {
			camera_active = cams[2];
		}

	}
#else
	float rotX = 0, rotY = 0;
	float dX = 0, dY = 0, dZ = 0;
	t_point3d *origine = definirPoint3d(0, 0, 0);

	SDL_PumpEvents();

	if (event.type == SDL_MOUSEMOTION && is_button_down) {
		int xd, yd;

		xd = event.motion.x;
		yd = event.motion.y;

		//rotation de la camra active
		// definition : 100px = rotation de 90Â° sur un axe
		rotX = 90.0F * (float)(yd - y) / 100.0F;
		rotY = 90.0F * (float)(xd - x) / 100.0F;

		x = xd;
		y = yd;

	} else if (event.type == SDL_MOUSEBUTTONDOWN) {
		is_button_down = true;
		x = event.motion.x;
		y = event.motion.y;
	} else if (event.type == SDL_MOUSEBUTTONUP) {
		is_button_down = false;
	}

	if (currentKeyStates[SDL_SCANCODE_UP]) {
		dZ--;
	} else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		dZ++;
	}

	if (currentKeyStates[SDL_SCANCODE_Z]) {
		dY++;
	} else if (currentKeyStates[SDL_SCANCODE_S]) {
		dY--;
	}

	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		dX--;
	} else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		dX++;
	}

	if (currentKeyStates[SDL_SCANCODE_J]) {
		camera_active = cams[0];
	} else if (currentKeyStates[SDL_SCANCODE_K]) {
		camera_active = cams[1];
	} else if (currentKeyStates[SDL_SCANCODE_L]) {
		camera_active = cams[2];
	}

	t_point3d *deplacement = definirVecteur3d(dX * 10, dY * 10, dZ * 10);

	translationScene3d(camera_active, deplacement);
	rotationScene3d(camera_active, origine, rotX, rotY, 0);

	libererPoint3d(deplacement);
	libererPoint3d(origine);

#endif

}
#endif

/**
 * partie specifique algo_c_1
 */
#define NB_FRAME_POUR_UN_DEMI_DEPLACEMENT	40
static size_t i_depl = 0;
static char depl[] = "SESNEES";	// ajouter S au début pour la premiere orientation //SESNEESNEESSSESSSEESE
char calculer_nouvelle_orientation(void)
{
	i_depl = i_depl + 1;
	return depl[i_depl];
}

t_bool niveau_termine(void)
{
	return i_depl == strlen(depl);
}

/**
 * /fin
 */

int main(int argc, char **argv)
{
	t_surface *surface = NULL;
	int cpt = 0;
	Uint32 timestart, oldtime;
	char buf[50];

	int i;

	t_point3d *origine = definirPoint3d(0, 0, 0);

	t_objet3d *laby = objet_fichier("./lab1.obj", BLANC, MAUVE);
	homothetieObjet3d(laby, 10, 10, 10);

	t_objet3d *tez = objet_fichier("./tezeus.obj", NOIR, VERTC);
	homothetieObjet3d(tez, 3, 3, 3);

	t_objet3d *sol = damier(1000, 1000, 30, 20);

	t_scene3d *scn_sol = definirScene3d(sol);
	t_scene3d *scn_laby = ajouter_relation(scn_sol, laby);
	translationScene3d(scn_laby, definirVecteur3d(50, 0, 0));	// position de depart de tezeus

	t_scene3d *scn_tez = ajouter_relation(scn_sol, tez);
	translationScene3d(scn_tez, definirVecteur3d(-450, 0, -350));	// position de depart de tezeus

	cams[0] = ajouter_relation(scn_sol, camera(1.0, 1.0, -100, -1000, -200));	// une camera sur le sol
	translationScene3d(cams[0], definirVecteur3d(0, 600, 0));	// position vue de dessus
	rotationScene3d(cams[0], origine, 270, 0, 0);

	cams[1] = ajouter_relation(scn_tez, camera(1.0, 1.0, -100, -1000, -700));	// une camera sur l'epaule
	translationScene3d(cams[1], definirVecteur3d(0, 50, -120));
	rotationScene3d(cams[1], origine, 0, 180, 0);

	cams[2] = ajouter_relation(scn_laby, camera(1.0, 1.0, -100, -1000, -300));	// une camera a la sortie
	translationScene3d(cams[2], definirVecteur3d(450, 50, 350));	// translation a adapter afin de la positionner sur la sortie du labyrinthe
	rotationScene3d(cams[2], origine, 0, 90, 0);

	printf("%d faces\n", nb_faces);

	camera_active = cams[1];

	//currentKeyStates = SDL_GetKeyboardState(NULL);
	surface = creerFenetre(RX, RY);
	timestart = SDL_GetTicks();
	oldtime = timestart;

	t_point3d *tez_tout_droit = definirVecteur3d(0, 0, 100. / NB_FRAME_POUR_UN_DEMI_DEPLACEMENT);
	char orientation_actuelle = 'S', orientation_precedente = '@';	// orientation vers le sud au départ

	i = 0;
	while (!niveau_termine() && event.type != SDL_QUIT)	// DUREE " * 60FPS
	{
		effacerEcran(surface);

	//	if (SDL_PollEvent(&event)) {
	//		handle_events();
	//	}
		// toutes les 2 secondes on tourne sur 1" puis deplacement sur 1"
		if (i % (NB_FRAME_POUR_UN_DEMI_DEPLACEMENT * 2) < NB_FRAME_POUR_UN_DEMI_DEPLACEMENT) {
			// novuelle paire de seconde, on recalcule l'orientation
			if (i % (NB_FRAME_POUR_UN_DEMI_DEPLACEMENT * 2) == 0) {
				orientation_precedente = orientation_actuelle;
				orientation_actuelle = calculer_nouvelle_orientation();
			}
			// et on fait la rotation
			switch (orientation_actuelle) {
			case 'N':
				if (orientation_precedente == 'S') {
					rotationScene3d(scn_tez, origine, 0, 180. / NB_FRAME_POUR_UN_DEMI_DEPLACEMENT, 0);
				} else if (orientation_precedente == 'E') {
					rotationScene3d(scn_tez, origine, 0, 90. / NB_FRAME_POUR_UN_DEMI_DEPLACEMENT, 0);
				} else if (orientation_precedente == 'W') {
					rotationScene3d(scn_tez, origine, 0, -90. / NB_FRAME_POUR_UN_DEMI_DEPLACEMENT, 0);
				}
				break;
			case 'S':
				if (orientation_precedente == 'N') {
					rotationScene3d(scn_tez, origine, 0, 180. / NB_FRAME_POUR_UN_DEMI_DEPLACEMENT, 0);
				} else if (orientation_precedente == 'E') {
					rotationScene3d(scn_tez, origine, 0, -90. / NB_FRAME_POUR_UN_DEMI_DEPLACEMENT, 0);
				} else if (orientation_precedente == 'W') {
					rotationScene3d(scn_tez, origine, 0, 90. / NB_FRAME_POUR_UN_DEMI_DEPLACEMENT, 0);
				}
				break;
			case 'E':
				if (orientation_precedente == 'N') {
					rotationScene3d(scn_tez, origine, 0, -90. / NB_FRAME_POUR_UN_DEMI_DEPLACEMENT, 0);
				} else if (orientation_precedente == 'S') {
					rotationScene3d(scn_tez, origine, 0, 90. / NB_FRAME_POUR_UN_DEMI_DEPLACEMENT, 0);
				} else if (orientation_precedente == 'W') {
					rotationScene3d(scn_tez, origine, 0, 180. / NB_FRAME_POUR_UN_DEMI_DEPLACEMENT, 0);
				}
				break;
			case 'W':
				if (orientation_precedente == 'N') {
					rotationScene3d(scn_tez, origine, 0, 90. / NB_FRAME_POUR_UN_DEMI_DEPLACEMENT, 0);
				} else if (orientation_precedente == 'S') {
					rotationScene3d(scn_tez, origine, 0, -90. / NB_FRAME_POUR_UN_DEMI_DEPLACEMENT, 0);
				} else if (orientation_precedente == 'E') {
					rotationScene3d(scn_tez, origine, 0, 180. / NB_FRAME_POUR_UN_DEMI_DEPLACEMENT, 0);
				}
				break;
			}
		} else {
			// dans la seconde moitie on avance tout droit...
			translationScene3d(scn_tez, tez_tout_droit);	// tez avance tout droit sur le reste de la seconde
		}

		dessinerScene3d(surface, camera_active);

		majEcran(surface);

		/* Framerate fixe a env 60 FPS max */
		SDL_Delay((1000 / CIBLE_FPS) - MIN((1000 / CIBLE_FPS), (SDL_GetTicks() - oldtime)));
		oldtime = SDL_GetTicks();

		cpt++;
		snprintf(buf, sizeof(buf), "%d FPS", (int)(cpt * 1000.0 / (oldtime - timestart)));
		// petite fuite de memoire lors de cet appel, non resolue pour le moment...
		definirTitreFenetre(surface, buf);

		i = i + 1;
	}

	SDL_Delay(1000);

	libererScene3d(scn_sol);	//scn_sol est la racine de l'arbre
	libererFenetre(surface);

	usage_lib_3d();
	usage_lib_objet_3d();
	usage_lib_scene_3d();

	return 0;
}
