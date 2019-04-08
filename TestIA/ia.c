#include <stdio.h>
#include <stdlib.h>

#include "array.h"

int main()
{
  //====================
  // GLOBAL VARIABLES
  //====================

  char path[20];
  snprintf(path, 20, "map");

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
        }
        else
        {
          matCost[i][j] = 0;
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

  fclose(file);

  //====================
  // FINDING THe BEST PATH
  //====================

  Array s;
  display(s);

  return 0;
}
