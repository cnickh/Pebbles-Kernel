/* The 15-410 kernel.
 * crt0.c
 *
 * The C runtime setup function
 *
 */

#include <stdlib.h>

extern int main(int argc, char *argv[]);

void _main(int argc, char *argv[])
{
  exit(main(argc, argv));
}
