/** @file verify_test.c
 *
 * Test output format for the traceback function
 *
 * This test calls a few functions to test a bunch
 * of different outputs.
 *
 * @author Michael Ashley-Rollman(mpa)
 */

#include "traceback.h"

//#define FAKE_OUTPUT

void f4(int i, float f)
{
  traceback(stdout);
}

void f3(char c, char *str)
{
  f4(5, 35.0);
}

void f2(void)
{
  f3('k', "test");
}

void f1(char ** array)
{
  f2();
}

void print_sample_output()
{
  printf("Function f4(int i=5, float f=35.000000), in\n");
  printf("Function f3(char c='k', char *str=\"test\"), in\n");
  printf("Function f2(void), in\n");
  printf("Function f1(char **array = {\"foo\", \"bar\", \"baz\"}), in\n");
}

int main()
{
#ifdef FAKE_OUTPUT
  print_sample_output();
#else
  char *arg[] = {"foo", "bar", "baz", "bletch"};
 // char *arg[] = {"foo", "bar", (char *)NULL};

  f1(arg);
#endif

  return 0;
}
