#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MONEY_ROUNDING    /* Force rounding of doubles */
#define MONEY_DECIMALS  2   /* 2 decimals for money data */
#include "money.h"

#include "pop.h"

extern int errno;
extern FILE *stdout;

int main(int argc, char** argv)
{
  float x;
  long seed=-5123L;
  errno = 0;
  
  ran3(&seed);
  x=ran3(&seed);

  int err = printf("Hello Random World %f\n", x);

  if (err < 0) {
    return EXIT_FAILURE;
  }

  err = fflush(stdout);

  if (err < 0 || errno != 0) {
    return EXIT_FAILURE;
  } else {
    return EXIT_SUCCESS;
  }
}