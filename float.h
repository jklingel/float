// float.h - Header file for the float.o library, which adds
// some floating-point arithmetic to the cc65 compiler

// Jan Klingel, 11/2026, version 0.2

// Needed for a safe add function to prevent wrap-around when adding
// large numbers like 20000.0 + 20000.0
#define FIXED_MAX 0x7FFFFFFFL  // +32767.99998
#define FIXED_MIN (-0x7FFFFFFFL - 1L) // -32768.0

// Function declarations
int32_t to_fixed_int(const char *str);
void fixed_to_str(int32_t fixed, char *buffer, size_t bufsize);
int32_t fixed_add(int32_t a, int32_t b);
int32_t fixed_qadd(int32_t a, int32_t b);
int32_t fixed_sub(int32_t a, int32_t b);
int32_t fixed_mul(int32_t a, int32_t b);
