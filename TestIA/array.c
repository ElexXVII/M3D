#include "array.h"

void append(Array* a, int e)
{
  a->len++;

  if (a->len == 1)
  {
    a->t = malloc(sizeof(int)*a->len);
  }
  else
  {
    a->t = realloc(sizeof(int)*a->len);
  }

  a->t[a->len-1] = e;
}

void display(Array a)
{
  printf("Array :");

  for (int i=0; i<a->len; i++)
  {
    printf(" %d",a->t[i]);
    if (i < a->len-1)
    {
      printf(",");
    }
  }

  printf(" End \n");
}
