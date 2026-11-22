// float.c - Functions to deal with float numbers, which cc65 does
// not support. The numbers are encoded in fixed Q16.16 format using
// ARM Q notation..
// Framework written by Google Gemini
// Error correction and functions fixed_add, fixed_qadd, and
// fixed_sub by Jan Klingel, 11/2026
// Version 0.2

// Q16.16 has a maximum range of -32768.0 to +32767.99998
// (−2^m−1 to +2^m−1 − 2^−n)

// Note that cc65 does not suport the data types int64_t, uint64_t

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "float.h"

// Convert a decimal string to fixed-point (Q16.16)
int32_t to_fixed_int(const char *str) {
    int sign = 1;
    int32_t integer_part = 0;
    int32_t fractional_part = 0;
    int frac_digits = 0;
    int32_t fixed_int;
    int32_t fixed_frac = 0;
    int32_t scale = 1;
    int i;

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        integer_part = integer_part * 10 + (*str - '0');
        str++;
    }
    fixed_int = integer_part << 16; // times 65536

    if (*str == '.') {
        str++;
        // Limit to 4 fractional digits so (fractional_part * 65536) fits
        // in int32_t
        while (*str >= '0' && *str <= '9' && frac_digits < 4) {
            fractional_part = fractional_part * 10 + (*str - '0');
            frac_digits++;
            str++;
        }
    }

    if (frac_digits > 0) {
        for (i = 0; i < frac_digits; i++) {
            scale *= 10;
        }
        // fixed_frac = (fractional_part * 65536L) / scale;
        // Above line would not round the fractional part, the next
        // line does this
        fixed_frac = (fractional_part * 65536L + (scale / 2)) / scale;
    }

    return sign * (fixed_int + fixed_frac);
}

// Convert fixed-point (Q16.16) to decimal string
void fixed_to_str(int32_t fixed, char *buffer, size_t bufsize) {
    int32_t integer_part;
    uint32_t fractional_part;
    uint32_t frac_scaled;
    int sign = 1;

    if (fixed < 0) {
        sign = -1;
        fixed = -fixed;
    }

    integer_part = fixed >> 16;
    fractional_part = fixed & 0xFFFF;

    // Multiply by 10000 instead of 1000000 to prevent 32-bit overflow
    // (65535 * 10000 < 2^32)
    frac_scaled = (fractional_part * 10000UL) / 65536UL;

    if (sign < 0) {
        snprintf(buffer, bufsize, "-%ld.%04lu",
                 (long)integer_part, (unsigned long)frac_scaled);
    } else {
        snprintf(buffer, bufsize, "%ld.%04lu",
                 (long)integer_part, (unsigned long)frac_scaled);
    }
}

// 32-bit safe Q16.16 addition
int32_t fixed_add(int32_t a, int32_t b) {
  if (b > 0 && a > FIXED_MAX - b) {
    return FIXED_MAX;
  }
  if (b < 0 && a < FIXED_MIN - b) {
    return FIXED_MIN;
  }
  return(a + b);
}

// 32-bit quick Q16.16 addition - will wrap-around when adding large
// numbers!
int32_t fixed_qadd(int32_t a, int32_t b) {
  return(a + b);
}

// 32-bit Q16.16 subtraction
int32_t fixed_sub(int32_t a, int32_t b) {
  return(a - b);
}

// 32-bit safe Q16.16 multiplication using 16-bit partial products
int32_t fixed_mul(int32_t a, int32_t b) {
    int sign = 1;
    uint32_t ua, ub;
    uint32_t a_hi, a_lo, b_hi, b_lo;
    uint32_t res;

    if (a < 0) {
      sign = -sign;
      ua = (uint32_t)(-a);
    }
    else
      ua = (uint32_t)a;
    if (b < 0) {
      sign = -sign;
      ub = (uint32_t)(-b);
    }
    else
      ub = (uint32_t)b;

    // x >> 1 = int / 2; x << 1 = int * 2
    // unsigned 1 << 16 = 65536
    // unsigned 1 >> 16 = 0
    a_hi = ua >> 16;
    a_lo = ua & 0xFFFF; // 65535
    b_hi = ub >> 16;
    b_lo = ub & 0xFFFF;

    // (a_hi*2^16 + a_lo) * (b_hi*2^16 + b_lo) >> 16
    res = ((a_hi * b_hi) << 16) +
          (a_hi * b_lo) +
          (a_lo * b_hi) +
          ((a_lo * b_lo) >> 16);

    return (sign < 0) ? -(int32_t)res : (int32_t)res;
}
