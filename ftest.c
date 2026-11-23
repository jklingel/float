// ftest.c -- testing the float.o library
// Jan Klingel, 11/2026

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "float.h"

int main(void) {
  char input1[33], input2[33], output[33]; // 32 bit plus '\0'
  int32_t fixed1, fixed2, fixed_result;

  printf("Enter first floating point number: ");
  if (!fgets(input1, sizeof(input1), stdin)) {
    printf("Error: no input!\n");
    return(1);
  }
  printf("Enter second floating point number: ");
  if (!fgets(input2, sizeof(input2), stdin)) {
    printf("Error: no input!\n");
    return(1);
  }

  fixed1 = to_fixed_int(input1);
  fixed2 = to_fixed_int(input2);

  // Let's do a multiplication of input1 times input2
  fixed_result = fixed_mul(fixed1, fixed2);

  fixed_to_str(fixed_result, output, sizeof(output));
  printf("Result as 32-bit binary number: %032b\n", fixed_result);
  printf("Result as a string: %s\n", output);

  return(0);
}
