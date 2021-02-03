#include <stdio.h>
#include "md5.c"

int run_test(char* name, long expected, long result) {
    if (expected == result) {
        printf("TEST PASSED: %s: expected %li, got %li\n", name, expected, result);
        return 1;
    } else {
        printf("TEST FAILED: %s: expected %li, got %li\n", name, expected, result);
        return 0;
    }
}

/* 
The REFERENCE_ fuctions are licensed under the following license.

Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.
 */

#define REFERENCE_F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define REFERENCE_G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define REFERENCE_H(x, y, z) ((x) ^ (y) ^ (z))
#define REFERENCE_I(x, y, z) ((y) ^ ((x) | (~z)))
#define REFERENCE_ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#define REFERENCE_FF(a, b, c, d, x, s, ac) ( \
    (a) += REFERENCE_F ((b), (c), (d)) + (x) + (unsigned long int)(ac), \
    (a) = REFERENCE_ROTATE_LEFT ((a), (s)), \
    (a) += (b) \
)

int main(int argc, char** argv) {
    int passed = 0, failed = 0;
    // compare core steps against RFC implementation
    run_test("step F", F(1, 2, 3), REFERENCE_F(1, 2, 3)) ? passed++ : failed++;
    run_test("step G", G(1, 2, 3), REFERENCE_G(1, 2, 3)) ? passed ++ : failed++;
    run_test("step H", H(1, 2, 3), REFERENCE_H(1, 2, 3)) ? passed++ : failed++;
    run_test("step I", I(1, 2, 3), REFERENCE_I(1, 2, 3)) ? passed++ : failed++;

    // compare ROTATE_LEFT against RFC implementation
    run_test("rotate_left", ROTATE_LEFT(24, 2), REFERENCE_ROTATE_LEFT(24, 2)) ? passed++ : failed++;

    // compare steps
    int a = 1;
    int ref_a = 1;
    //run_test("FF", STEP(F, a, 2, 3, 4, 5, 6, 7), REFERENCE_FF(ref_a, 2, 3, 4, 5, 6, 7)) ? passed++ : failed++;

    printf("Tests Passed: %i\n", passed);
    printf("Tests Failed: %i\n", failed);
    return failed;
}