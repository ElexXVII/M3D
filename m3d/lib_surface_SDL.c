#include "lib_surface.h"

/**
 * L'utilisation de _Generic est moins importante car ces #define n'ont de portee que ce fichier .c : undef en fin de .c
 */
#define t_surface_ecran(this) ((this)->ecran)

t_surface *creerFenetre(int x, int y)
{
	t_surface *S;

	S = (t_surface *) malloc(sizeof(t_surface));

	if (S != NULL) {
		t_surface_x(S) = x;
		t_surface_y(S) = y;

		t_surface_ecran(S) = SDL_SetVideoMode(t_surface_x(S), t_surface_y(S), 32, SDL_HWSURFACE);

		if (t_surface_ecran(S) == NULL) {
			libererFenetre(S);
			S = NULL;
		}
		t_surface_xmin(S) = (int *)malloc((size_t) t_surface_y(S) * sizeof(int));
		t_surface_xmax(S) = (int *)malloc((size_t) t_surface_y(S) * sizeof(int));

		if (t_surface_xmin(S) == NULL || t_surface_xmax(S) == NULL) {
			libererFenetre(S);
		} else {
			memset(t_surface_xmax(S), 0, (size_t) t_surface_y(S) * sizeof(int));
			memset(t_surface_xmin(S), t_surface_x(S) - 1, (size_t) t_surface_y(S) * sizeof(int));
		}
	}
	return S;
}

void libererFenetre(t_surface * surface)
{
	free(t_surface_xmin(surface));
	free(t_surface_xmax(surface));
	free(t_surface_ecran(surface));
	free(surface);
}

void effacerEcran(t_surface * surface)
{
	SDL_FillRect(t_surface_ecran(surface), NULL, 0);
}

void majEcran(t_surface * surface)
{
	SDL_Flip(t_surface_ecran(surface));
}

void definirTitreFenetre(t_surface * surface, const char *titre)
{
	SDL_WM_SetCaption(titre, NULL);
}

void remplirPixel(t_surface * surface, int x, int y, Uint32 pixel)
{
	unsigned char *p;
	SDL_Surface *ecran = t_surface_ecran(surface);
	int bpp = ecran->format->BytesPerPixel;
	p = (unsigned char *)ecran->pixels + y * ecran->pitch + x * bpp;
	*(Uint32 *) p = pixel;
}

void remplirLigneHorizontale(t_surface * surface, int x, int y, int l, Uint32 pixel)
{
#if 0				// la version SDL est plus rapide...
	int i;
	for (i = 0; i < l; i++) {
		remplirPixel(surface, x + i, y, pixel);
	}
#else
	SDL_Rect rect = { (Sint16) x, (Sint16) y, (Uint16) l, 1U };
	SDL_FillRect(t_surface_ecran(surface), &rect, pixel);
#endif
}

Uint32 arc_en_ciel(int z)	// z \in [0, 1275]
{
	if (z < 255) {
		return couleur_entre(100 * z / 255, ROUGEC, JAUNEC);
	} else if (z < 510) {
		return couleur_entre(100 * z / 255, JAUNEC, VERTC);
	} else if (z < 765) {
		return couleur_entre(100 * z / 255, VERTC, PALEC);
	} else if (z < 1020) {
		return couleur_entre(100 * z / 255, PALEC, BLEUC);
	} else {
		return couleur_entre(100 * z / 255, JAUNEC, VERTC);
	}
}

Uint32 couleur_entre(int z, Uint32 a, Uint32 b)	// z \in [0, 100]
{
	Uint8 ra = COULEUR_Uint32_R(a), ga = COULEUR_Uint32_G(a), ba = COULEUR_Uint32_B(a);
	Uint8 rb = COULEUR_Uint32_R(b), gb = COULEUR_Uint32_G(b), bb = COULEUR_Uint32_B(b);
	Uint8 rc = (Uint8) (ra + (z / 100.0) * (rb - ra)), gc = (Uint8) (ga + (z / 100.0) * (gb - ga)), bc = (Uint8) (ba + (z / 100.0) * (bb - ba));
	Uint32 c = COULEUR_RGB_Uint32(rc, gc, bc);
	return c;
}

void affiche_hexa(Uint32 c)
{				/* affiche la chaine 0x.... correspondant à c */
	Uint8 a = (Uint8) ((c >> 24) & 0xFF), r = COULEUR_Uint32_R(c), g = COULEUR_Uint32_G(c), b = COULEUR_Uint32_B(c);
	printf("|0x|%02x|%02x|%02x|%02x|", a, r, g, b);
}

#undef t_surface_ecran
