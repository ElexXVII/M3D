#include <stdio.h>
#include <stdlib.h>

struct array
{
  int* t;
  int len;
};
typedef struct array Array;

void append(Array*, int);
void display(Array a);
