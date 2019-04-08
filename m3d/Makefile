# LIBSDL=SDL ou LIBSDL=SDL2 a definir lors de l'appel :
# LIBSDL=SDL make
# LIBSDL=SDL2 make

LIBSDL=SDL

OPT=-g -O0
#OPT=-Ofast
#OPT=-O3

# gnu11 au lieu de c11 permet d'avoir (entre autre) la definition de M_PI
OPT_NORME=-Wall -Werror -Wextra -Wconversion -Wno-unused-parameter 

prog_${LIBSDL}: prog.o fonctions.c lib_2d.o lib_mat.o lib_surface_${LIBSDL}.o lib_3d_etu.o lib_objet3d_etu.o lib_scene3d_etu.o PA_3d.o PA_objet3d.o PA_scene3d.o
	gcc ${OPT} ${OPT_NORME} -D COMPIL_${LIBSDL} -march=native prog.o fonctions.c lib_2d.o lib_mat.o lib_surface_${LIBSDL}.o lib_3d_etu.o lib_objet3d_etu.o lib_scene3d_etu.o PA_3d.o PA_objet3d.o PA_scene3d.o -o prog_${LIBSDL} -lm -l${LIBSDL}

prog_t3d: prog_t3d.o fonctions.c lib_2d.o lib_mat.o lib_surface_${LIBSDL}.o lib_3d_etu.o lib_objet3d_etu.o lib_scene3d_etu.o PA_3d.o PA_objet3d.o PA_scene3d.o
	gcc ${OPT} ${OPT_NORME} -D COMPIL_${LIBSDL} -march=native prog_t3d.o fonctions.c lib_2d.o lib_mat.o lib_surface_${LIBSDL}.o lib_3d_etu.o lib_objet3d_etu.o lib_scene3d_etu.o PA_3d.o PA_objet3d.o PA_scene3d.o -o prog_t3d -lm -l${LIBSDL}

prog_o3d: prog_o3d.o fonctions.c lib_2d.o lib_mat.o lib_surface_${LIBSDL}.o lib_3d_etu.o lib_objet3d_etu.o lib_scene3d_etu.o PA_3d.o PA_objet3d.o PA_scene3d.o
	gcc ${OPT} ${OPT_NORME} -D COMPIL_${LIBSDL} -march=native prog_o3d.o fonctions.c lib_2d.o lib_mat.o lib_surface_${LIBSDL}.o lib_3d_etu.o lib_objet3d_etu.o lib_scene3d_etu.o PA_3d.o PA_objet3d.o PA_scene3d.o -o prog_o3d -lm -l${LIBSDL}

################### Fichiers a completer
prog.o: prog.c
	gcc ${OPT} ${OPT_NORME} -D COMPIL_${LIBSDL} -c -march=native prog.c

prog_t3d.o: prog_t3d.c
	gcc ${OPT} ${OPT_NORME} -D COMPIL_${LIBSDL} -c -march=native prog_t3d.c

prog_o3d.o: prog_o3d.c
	gcc ${OPT} ${OPT_NORME} -D COMPIL_${LIBSDL} -c -march=native prog_o3d.c

lib_3d_etu.o: lib_3d_etu.c lib_3d.h
	gcc ${OPT} ${OPT_NORME} -D COMPIL_${LIBSDL} -c -march=native lib_3d_etu.c

lib_objet3d_etu.o: lib_objet3d_etu.c lib_objet3d.h
	gcc ${OPT} ${OPT_NORME} -D COMPIL_${LIBSDL} -c -march=native lib_objet3d_etu.c

lib_scene3d_etu.o: lib_scene3d_etu.c lib_scene3d.h
	gcc ${OPT} ${OPT_NORME} -D COMPIL_${LIBSDL} -c -march=native lib_scene3d_etu.c

################### Fichiers a ne pas modifier (a priori)
lib_surface_${LIBSDL}.o: lib_surface_${LIBSDL}.c lib_surface.h
	gcc ${OPT} ${OPT_NORME} -D COMPIL_${LIBSDL} -fPIC -c -march=native lib_surface_${LIBSDL}.c

lib_2d.o: lib_2d.c lib_2d.h
	gcc ${OPT} ${OPT_NORME} -D COMPIL_${LIBSDL} -c -march=native lib_2d.c

lib_mat.o: lib_mat.c lib_mat.h lib_3d.h
	gcc ${OPT} ${OPT_NORME} -D COMPIL_${LIBSDL} -c -march=native lib_mat.c

###################
clean:
	rm -f lib_*.o prog_SDL prog_SDL2 prog_t3d *~

###################

