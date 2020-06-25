#include <stdio.h>
#include "traceback.h"

void bar(int x, int y)
{
  traceback(stdout);
}

void foo(void *lookma) {
  bar (5,17);
}

int main (int argc, char **argv)
{
  foo( (void*) NULL );
  return 0;
}
