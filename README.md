# float
Simple Q16.16 float library for cc65 compiler

The cross-compiler cc65 has one big disadvantage: there is no floating point arithmetic implemented. In other words, neither the data type 'float' has been implemented nor the format specifier '%f' works. With knowing that, it is clear that floating point variables in double length are also not implemented. 

As a result, programs compiled with cc65 can use signed and unsigned integers (like in -2, -1, 0, 1, 2...) up to a width of 32 bits (unsigned 0..65536 times two in decimal). A floating point variable like '3.14' is not supported. This is a major roadblock for even simple programs in which the fractional part of an integer is important, e.g. when calculating with the constant Pi (~3.14159).

I wrote a small library that takes two floating point numbers as strings and converts them to a Q16.16 fixed format in ARM Q notation. Q16.16 means that the floating point variable is represented by 16-1 bit for the integert part and 16 bit for the fractional part. ARM Q notation means that the very first bit is the sign (+/0 or -/1) and part of the notation. The converted, fixed numbers can now be added, subtracted, and multiplied. The result returned by the library is again a fixed Q16.16 integer that can be converted to a string for printing. "Fixed" means that the period '.' separating the integer from the fractional part always stays at the same place

See https://janklingel.de/2026/11/22/a-simple-c-float-library-for-cc65/ for more details.

Version 0.2 as of 11/22/2026
