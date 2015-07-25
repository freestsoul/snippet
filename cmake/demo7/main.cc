#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#if not defined HAVE_POW
#include "math/MathFunctions.h"
#else
#include <math.h>
#endif

int main(int argc, char *argv[]) {
  printf("%s Version %d.%d\n",
         argv[0],
         DEMO_VERSION_MAJOR,
         DEMO_VERSION_MINOR);
  if (argc < 3) {
    printf("usage: %s base exponent.\n", argv[0]);
    return 1;
  }

  double base = atof(argv[1]);
  int exponent = atoi(argv[2]);

#if defined HAVE_POW
  printf("Now we use our own math library\n");
  double result = pow(base, exponent);
#else
  printf("Now we use the standard library\n");
  double result = power(base, exponent);
#endif
  printf("%g^%d is %g\n", base, exponent, result);
  
  return 0;
}
