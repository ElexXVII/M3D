#include <stdio.h>
#include <stdlib.h>

#include "array.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

int main (int argc, char *argv[])
{
  //====================
  // GLOBAL VARIABLES
  //====================

  if (argc != 2)
  {
    printf("Pas de map donnée en paramètre\n");
    exit(EXIT_FAILURE);
  }

  char path[20];
  snprintf(path, 20, "%s",argv[1]);

  FILE *file;
  file = fopen(path, "r"); // read mode

  int nx = 0;
  int ny = 0;

  //====================
  // READING THE FILE
  //====================

  if (file == NULL)
  {
    perror("Error while opening the file.\n");
    exit(EXIT_FAILURE);
  }

  char c;
  while((c = (char)fgetc(file)) != EOF)
  {
    if (c!='\n' && ny == 0)
    {
      nx++;
    }

    if (c == '\n')
    {
      ny++;
    }
  }
  printf("%d - %d\n", nx, ny);

  rewind(file);

  //====================
  // MAKING THE COST MATRIX
  //====================

  int matCost[ny][nx];
  int matVect[ny][nx];

  int start[2];
  int end[2];

  for (int i=0; i<ny; i++)
  {
    for (int j=0; j<nx; j++)
    {
      if ((c = (char)fgetc(file)) != '\n' || (c = (char)fgetc(file)) != EOF)
      {
        if (c=='*')
        {
          matCost[i][j] = -1;
          matVect[i][j] = -1;
        }
        else
        {
          matCost[i][j] = 0;
          matVect[i][j] = 0;
        }

        if (c=='@')
        {
          start[0] = j;
          start[1] = i;
        }
        if (c=='?')
        {
          end[0] = j;
          end[1] = i;
        }
      }
    }
  }

  printf("Start : %d-%d | End : %d-%d\n", start[0], start[1], end[0], end[1]);

  for (int i=0; i<ny; i++)
  {
    for (int j=0; j<nx; j++)
    {
      printf("%d,",matCost[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  for (int i=0; i<ny; i++)
  {
    for (int j=0; j<nx; j++)
    {
      printf("%d,",matVect[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  fclose(file);

  //====================
  // FINDING THE BEST PATH
  //====================

  //Case to fill
  Array filling1X = NULL;
  Array filling1Y = NULL;

  //Case to fill the next loop
  Array filling2X = NULL;
  Array filling2Y = NULL;

  //Add the first case to fill : The start cell
  append(&filling1X,start[0]);
  append(&filling1Y,start[1]);

  //Filling the start cell
  matCost[start[1]][start[0]] = 1;

  // Filling cells of MatCost and MatVect
  // While the end cell is not filled, fill cells which are in the array up there
  // OR while filling arrays are not empty, if they are : No solution found
  int cellValue = 2;
  while(matCost[end[1]][end[0]] == 0 && filling1X != NULL)
  {
    for (int i=0; i<ny; i++)
    {
      for (int j=0; j<nx; j++)
      {
        printf("%d,",matCost[i][j]);
      }
      printf("\n");
    }
    printf("\n");

    for (int i=0; i<filling1X->len; i++)
    {
      //Top cell
      if (filling1Y->t[i]-1 >= 0 && matCost[filling1Y->t[i]-1][filling1X->t[i]] == 0)
      {
        matCost[filling1Y->t[i]-1][filling1X->t[i]] = cellValue;
        append(&filling2X,filling1X->t[i]);
        append(&filling2Y,filling1Y->t[i]-1);

        matVect[filling1Y->t[i]-1][filling1X->t[i]] = 2;
      }
      //Bottom cell
      if (filling1Y->t[i]+1 < ny && matCost[filling1Y->t[i]+1][filling1X->t[i]] == 0)
      {
        matCost[filling1Y->t[i]+1][filling1X->t[i]] = cellValue;
        append(&filling2X,filling1X->t[i]);
        append(&filling2Y,filling1Y->t[i]+1);

        matVect[filling1Y->t[i]+1][filling1X->t[i]] = 0;
      }
          //printf("%d - %d\n",i,filling2X->len);
      //Right cell
      if (filling1X->t[i]-1 >= 0 && matCost[filling1Y->t[i]][filling1X->t[i]-1] == 0)
      {
        matCost[filling1Y->t[i]][filling1X->t[i]-1] = cellValue;
        append(&filling2X,filling1X->t[i]-1);
        append(&filling2Y,filling1Y->t[i]);

        matVect[filling1Y->t[i]][filling1X->t[i]-1] = 1;
      }
      //Left cell
      if (filling1X->t[i]+1 < nx && matCost[filling1Y->t[i]][filling1X->t[i]+1] == 0)
      {
        matCost[filling1Y->t[i]][filling1X->t[i]+1] = cellValue;
        append(&filling2X,filling1X->t[i]+1);
        append(&filling2Y,filling1Y->t[i]);

        matVect[filling1Y->t[i]][filling1X->t[i]+1] = 3;
      }
    }

    // The next cost will be the current + 1
    cellValue++;

    // Empty the previous list of cells
    delete(&filling1X);
    delete(&filling1Y);

    // Filling the list with the next cells to fill
    for (int i=0; i<filling2X->len; i++)
    {
      append(&filling1X,filling2X->t[i]);
      append(&filling1Y,filling2Y->t[i]);
    }

    // Delete the saved list of cells, because it's now in filling1
    // We will refill it with the next list for the next itteration
    delete(&filling2X);
    delete(&filling2Y);
  }

  for (int i=0; i<ny; i++)
  {
    for (int j=0; j<nx; j++)
    {
      printf("%d,",matVect[i][j]);
  }
    printf("\n");
  }
  printf("\n");

  delete(&filling1X);
  delete(&filling1Y);

  //Filling the way

  Array wayX = NULL;
  Array wayY = NULL;

  append(&wayX, end[0]);
  append(&wayY, end[1]);

  int x = end[0];
  int y = end[1];

  //On trace le chemin sauf si la case de début est aussi la case d'arrivé
  int isDone = ((end[0] == start[0]) && (end[1] == start[1]));

  while (!isDone)
  {
    switch(matVect[y][x])
    {
      case 0:
        append(&wayX, x);
        append(&wayY, --y);
        break;
      case 1:
        append(&wayX, ++x);
        append(&wayY, y);
        break;
      case 2:
        append(&wayX, x);
        append(&wayY, ++y);
        break;
      case 3:
        append(&wayX, --x);
        append(&wayY, y);
        break;
    }

    //Si la case actuel est la case d'arrivé, alors on a le chemin
    isDone = ((x == start[0]) && (y == start[1]));
  }

  display(wayX);
  display(wayY);

  for (int i=0; i<wayX->len; i++)
  {
    matCost[wayY->t[i]][wayX->t[i]] = 777;
  }

  for (int i=0; i<ny; i++)
  {
    for (int j=0; j<nx; j++)
    {
      switch(matCost[i][j])
      {
        case -1:
          printf(RED"O"RESET);
          break;
        case 777:
          printf(BLUE"+"RESET);
          break;
        default:
          printf(CYAN"."RESET);
          break;
      }
    }
    printf("\n");
  }
  printf("\n");

  return 0;
}
