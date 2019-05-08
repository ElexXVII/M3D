#include <stdio.h>
#include <stdlib.h>

#include "array.h"

int main()
{
  //====================
  // GLOBAL VARIABLES
  //====================

  char path[20];
  snprintf(path, 20, "map2");

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

  // Filling cells of MatCost and MatVect
  // While the end cell is not filled, fill cells which are in the array up there
  // OR while filling arrays are not empty, if they are : No solution found
  while(matCost[end[1]][end[0]] == 0 && filling1X != NULL)
  {
    matCost[]
  }

  return 0;
}
