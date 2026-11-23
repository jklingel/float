// circle.c -- testing the float.o library with equations used to
// calculate measurements involving circles
// Jan Klingel, 11/2026

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "float.h"

#define PI "3.14159"

int main(void) {
  char radius[33], output[33]; // 32 bit plus '\0'
  int32_t fixradius, fixpi, fixed_result;

  // Define radius R
  strcpy(radius,"5.0"); // Radius of the circle is 5.0 cm
  printf("The radius r of the circle is 5.0 cm\n");

  fixradius = to_fixed_int(radius);
  fixpi = to_fixed_int(PI);

  // Calculate area A = PI * Radius r²
  fixed_result = fixed_mul(fixradius, fixradius);
  fixed_result = fixed_mul(fixed_result,fixpi);

  fixed_to_str(fixed_result, output, sizeof(output));
  printf("The area A of the circle is %s cm²\n", output);

  // Calculate circumference C = PI * Radius r * 2
  fixed_result = fixed_mul(fixpi,fixradius);
  fixed_result = fixed_mul(fixed_result,2*65536);

  fixed_to_str(fixed_result, output, sizeof(output));
  printf("The circumference C of the circle is %s cm\n", output);

  return(0);
}
