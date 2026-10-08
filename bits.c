/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
#include "bits.h"

// P1
/*
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  int x = 0;
  x = (~x) << 31;
  return x;
}

// P2
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  int result;
  result = ~((~((~x) & y)) & (~(x & (~y))));
  return result;
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x) {
  int result;
  result = ~((x >> 31) & x) + 1;
  return result;
}

// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes
 * unchanged Bytes are numbered from 0 (least significant) to 3 (most
 * significant). You can assume 0 <= src <= 3 and 0 <= dst <= 3. Example:
 * copyByteWithin(0x11223344, 0, 2) = 0x11443344 Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int result, temp, temp2;
  temp = (x >> (src << 3)) & 255;
  temp2 = (~(255 << (dst << 3))) & x;
  result = temp2 | (temp << (dst << 3));
  return result;
}

// P5
/*
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int result;
  result = (x >> n) & (~(((1 << 31) >> n) << 1));

  return result;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int x1, x2, result;
  x1 = (((((15 << 8) | 15) << 8) | 15) << 8) | 15;
  x2 = (((((240 << 8) | 240) << 8) | 240) << 8) | 240;
  result = (x1 & x) << 4 | (((x2 & x) >> 4) & x1);
  return result;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second
 * least significant 0 bit Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4,
 * secondLowestZeroBit(0x7FFFFFFF) = 0 secondLowestZeroBit(-1) = 0 Legal ops: !
 * ~ & ^ | + << >> Max ops: 8 Rating: 4
 */
int secondLowestZeroBit(int x) {
  int result, y, z;
  y = ~x;
  z = y & (y + ~0);
  result = z & ((~z) + 1);
  return result;
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then
 * the return 1, otherwise return 0. Examples: oddParity(5) = 1, oddParity(7) =
 * 0 Legal ops: ! ~ & ^ | + << >> Max ops: 56 Rating: 5
 */
int oddParity(int x) {
  int result, x1, x2, x3, x4;

  x1 = ((x >> 16) ^ x) & (~((~0) << 16));
  x2 = ((x1 >> 8) ^ x1) & (~((~0) << 8));
  x3 = ((x2 >> 4) ^ x2) & (~((~0) << 4));
  x4 = ((x3 >> 2) ^ x3) & (~((~0) << 2));
  result = ((x4 >> 1) ^ x4) & (~((~0) << 1));
  return !result;
}

// P9
/*
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int x1 = x << (32 - n);
  int x2 = (x >> n) & ~((~0) << (32 - n));
  int result = x1 | x2;
  return result;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int result, t, s;
  t = x + ~((~0) << (n - 1));
  s = 1 & (x >> n);
  result = ((t + s) >> n) << n;
  return result;
}

// P11
/*
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int s1, s2, result, sx, sy;
  s1 = 1 & x;
  s2 = 1 & y;
  sx = (x >> 31) + 1;
  sy = (y >> 31) + 1;
  result =
      ((x >> 1) + (y >> 1)) + (s1 & s2) +
      ((s1 ^ s2) & (((((x + (~y) + 1) >> 31) + 1) & ((sx ^ sy) + (~0)) & 1) |
                    (sx & (sx ^ sy))));
  return result;
}

// P12
/*
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int sx, xa, xb;
  int da, db, la, lb, result;
  sx = x >> 31;
  xa = x ^ a;
  xb = x ^ b;
  da = xa >> 31;
  db = xb >> 31;
  la = (da & sx) | (~da & ((x + ~a + 1) >> 31));
  lb = (db & sx) | (~db & ((x + ~b + 1) >> 31));
  result = ((!la) ^ (!lb)) | !xa | !xb;
  return result;
}

// P13
/*
 * mul5Sat - return x*5, and if x*5 overflow, change the result to
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int s;
  int x1, x2, x3, result;
  int s0, s1, s2, s3;
  int over;
  int sat;
  s = (~0) << 31;
  s0 = x & s;
  x1 = x << 1;
  x2 = x << 2;
  x3 = x2 + x;
  s1 = x1 & s;
  s2 = x2 & s;
  s3 = x3 & s;
  over = ((s1 ^ s0) | (s2 ^ s0) | (s3 ^ s0)) >> 31;
  sat = (~s) + ((s0 >> 31) & 1);
  result = (x3 & ~over) | (over & sat);
  return result;
}

// P14
/*
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int s = (~0) << 31;
  int sx = x & s, sy = y & s, sz = z & s;
  int xy = x + y, sxy = xy & s;
  int xyz = x + y + z, sxyz = xyz & s;
  int result;
  int d1 = sx ^ sy, d2 = sxy ^ sx, d3 = sxy ^ sz, d4 = sxy ^ sxyz;
  int d5 =
      (((d1 & (~d3) & d4) | ((~d1) & (((d2 ^ d4) & (~d3)) | (d3 & d2)))) & s) >>
      31;
  result = d5 & (~(sxyz + (~d1 & d2 & d3 & d4)) >> 30);
  return result;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned s = uf & 0x80000000, exp_ = (uf >> 23) & 0xFF, frac = uf & 0x7FFFFF;
  unsigned M;
  int base_exp;

  if (exp_ == 0xFF)
    return uf;
  if (exp_ == 0 && frac == 0)
    return uf;
  if (exp_ == 0) {
    M = frac;
    base_exp = -150;
  } else {
    M = (1 << 23) | frac;
    base_exp = (int)exp_ - 151;
  }
  unsigned N = M * 3;
  int L = 31;
  while (!(N & (1u << L)))
    L--;
  int E = L + base_exp;
  if (E >= -126) {
    int exp_new = E + 127;
    if (exp_new >= 255) {

      return s | 0x7F800000;
    }
    int shift = L - 23;
    unsigned Q = N >> shift;
    unsigned R = N & ((1u << shift) - 1);
    unsigned half = 1u << (shift - 1);
    if (R > half || (R == half && (Q & 1))) {
      Q++;
    }
    if (Q == (1u << 24)) {
      Q = 1u << 23;
      exp_new++;
      if (exp_new >= 255) {
        return s | 0x7F800000;
      }
    }
    unsigned frac_new = Q & 0x7FFFFF;
    return s | (exp_new << 23) | frac_new;
  } else {
    unsigned Q = N >> 1;
    unsigned R = N & 1;
    if (R && (Q & 1)) {
      Q++;
    }
    return s | Q;
  }
}
// P16
/*
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned s = uf & 0x80000000, exp_ = (uf >> 23) & 0xFF, frac = uf & 0x7FFFFF;
  unsigned e = exp_ - 127, d = 23 - e;
  unsigned q = (1 << e) | (frac >> d), r = frac & ((1 << d) - 1),
           half = 1 << (d - 1);
  if (exp_ == 255)
    return uf;
  if (exp_ <= 125)
    return s;
  else if (exp_ == 126) {
    if (frac == 0)
      return s;
    else
      return s | 0x3F800000;
  } else if (exp_ >= 150) {
    return uf;
  } else {
    if (r > half || (r == half && (q & 1))) {
      q++;
    }
    if (q == (1 << (e + 1))) {
      exp_ = e + 1 + 127;
      frac = 0;
    } else {
      exp_ = e + 127;
      frac = (q - (1 << e)) << (23 - e);
    }

    return s | (exp_ << 23) | frac;
  }
  return 16;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned s, exp_ = 31, frac;
  unsigned a = (x < 0) ? -(unsigned)x : (unsigned)x;
  unsigned point = 0x80000000, fracp = 0x3FFFFF80;
  unsigned result;
  if (x == 0)
    return 0;
  if (x == 0x80000000)
    return 0xCF000000;
  s = x & point;
  point = point >> 1;
  while ((point & a) == 0) {
    a = a << 1;
    exp_--;
  }
  if ((a & 0x40) && ((a & 0x3F) || (a & 0x80))) {
    a += 0x40;
  }
  if (((a >> 1) & point) != 0) {
    a = a >> 1;
    exp_++;
  }
  frac = (a & fracp) >> 7;
  exp_ = (exp_ + 126) << 23;
  result = s | frac | exp_;
  return result;
}

// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int result, point1, point2;
  point1 = 0x11;
  point2 = 0xF;
  point1 = (point1 << 8) | point1;
  point1 = (point1 << 16) | point1;
  result = ((x >> 1) & point1) + ((x >> 2) & point1) + ((x >> 3) & point1) +
           (x & point1);
  result = ((result >> 4) & point2) + ((result >> 8) & point2) +
           ((result >> 12) & point2) + ((result >> 16) & point2) +
           ((result >> 20) & point2) + ((result >> 24) & point2) +
           ((result >> 28) & point2) + (result & point2);
  return result;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x) {
  int m1, m2, m3, m4, m5;
  int result;
  m1 = 0xFF | (0xFF << 8);
  m2 = 0xFF | (0xFF << 16);
  m3 = m2 ^ (m2 << 4);
  m4 = m3 ^ (m3 << 2);
  m5 = m4 ^ (m4 << 1);
  x = ((x & m5) << 1) | ((x >> 1) & m5);
  x = ((x & m4) << 2) | ((x >> 2) & m4);
  x = ((x & m3) << 4) | ((x >> 4) & m3);
  x = ((x & m2) << 8) | ((x >> 8) & m2);
  result = (x << 16) | ((x >> 16) & m1);
  return result;
}
