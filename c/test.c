#include <stdio.h>
#include <string.h>
#include "md5.h"

int run_test(char* name, char* result, char* expected) {
    if (strcmp(expected, result)) {
        printf("TEST PASSED: %s: expected %s, got %s\n", name, expected, result);
        return 1;
    } else {
        printf("TEST FAILED: %s: expected %s, got %s\n", name, expected, result);
        return 0;
    }
}

/* 
The RFC_ fuctions are licensed under the following license.

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

#define RFC_F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define RFC_G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define RFC_H(x, y, z) ((x) ^ (y) ^ (z))
#define RFC_I(x, y, z) ((y) ^ ((x) | (~z)))
#define RFC_ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#define RFC_FF(a, b, c, d, x, s, ac) ( \
    (a) += RFC_F ((b), (c), (d)) + (x) + (unsigned long int)(ac), \
    (a) = RFC_ROTATE_LEFT ((a), (s)), \
    (a) += (b) \
)
#define RFC_GG(a, b, c, d, x, s, ac) ( \
    (a) += RFC_G ((b), (c), (d)) + (x) + (unsigned long int)(ac), \
    (a) = RFC_ROTATE_LEFT ((a), (s)), \
    (a) += (b) \
)
#define RFC_HH(a, b, c, d, x, s, ac) ( \
    (a) += RFC_H ((b), (c), (d)) + (x) + (unsigned long int)(ac), \
    (a) = RFC_ROTATE_LEFT ((a), (s)), \
    (a) += (b) \
)
#define RFC_II(a, b, c, d, x, s, ac) ( \
    (a) += RFC_I ((b), (c), (d)) + (x) + (unsigned long int)(ac), \
    (a) = RFC_ROTATE_LEFT ((a), (s)), \
    (a) += (b) \
)

/*
 * The PLUMB_ fuctions are licensed under the following license.
 *
 * This code implements the MD5 message-digest algorithm.
 * The algorithm is due to Ron Rivest.  This code was
 * written by Colin Plumb in 1993, no copyright is claimed.
 * This code is in the public domain; do with it what you wish.
 *
 * Equivalent code is available from RSA Data Security, Inc.
 * This code has been tested against that, and is equivalent,
 * except that you don't need to include two pages of legalese
 * with every copy.
 *
 * To compute the message digest of a chunk of bytes, declare an
 * MD5Context structure, pass it to MD5Init, call MD5Update as
 * needed on buffers full of bytes, and then call MD5Final, which
 * will fill a supplied 16-byte array with the digest.
 */
#define PLUMB_F1(x, y, z) (z ^ (x & (y ^ z)))
#define PLUMB_F2(x, y, z) PLUMB_F1(z, x, y)
#define PLUMB_F3(x, y, z) (x ^ y ^ z)
#define PLUMB_F4(x, y, z) (y ^ (x | ~z))
// NOTE: data = x + ac
#define PLUMB_MD5STEP(f, w, x, y, z, data, s) \
	( w += f(x, y, z) + data,  w = w<<s | w>>(32-s),  w += x )


int main(int argc, char** argv) {
    int passed = 0, failed = 0;
/*     run_test("INT_SIZE", sizeof(unsigned int)*8, 32) ? passed++ : failed++;
    puts("RFC Tests");
    // compare core steps against RFC implementation
    run_test("RFC_F", F(1, 2, 3), RFC_F(1, 2, 3)) ? passed++ : failed++;
    run_test("RFC_G", G(1, 2, 3), RFC_G(1, 2, 3)) ? passed ++ : failed++;
    run_test("RFC_H", H(1, 2, 3), RFC_H(1, 2, 3)) ? passed++ : failed++;
    run_test("RFC_I", I(1, 2, 3), RFC_I(1, 2, 3)) ? passed++ : failed++;

    // compare ROTATE_LEFT against RFC implementation
    run_test("RFC_ROTATE_LEFT", ROTATE_LEFT(24, 2), RFC_ROTATE_LEFT(24, 2)) ? passed++ : failed++;

    // compare steps
    int a = 1;
    int ref_a = 1;
    run_test("RFC_FF", STEP(F, a, 2, 3, 4, 5, 6, 7), RFC_FF(ref_a, 2, 3, 4, 5, 6, 7)) ? passed++ : failed++;
    run_test("RFC_GG", STEP(G, a, 2, 3, 4, 5, 6, 7), RFC_GG(ref_a, 2, 3, 4, 5, 6, 7)) ? passed++ : failed++;
    run_test("RFC_HH", STEP(H, a, 2, 3, 4, 5, 6, 7), RFC_HH(ref_a, 2, 3, 4, 5, 6, 7)) ? passed++ : failed++;
    run_test("RFC_II", STEP(I, a, 2, 3, 4, 5, 6, 7), RFC_II(ref_a, 2, 3, 4, 5, 6, 7)) ? passed++ : failed++;

    puts("Colin Plumb Tests");
    // compare core steps against Colin Plumb implementation
    run_test("PLUMB_F/F1", F(1, 2, 3), PLUMB_F1(1, 2, 3)) ? passed++ : failed++;
    run_test("PLUMB_G/F2", G(1, 2, 3), PLUMB_F2(1, 2, 3)) ? passed ++ : failed++;
    run_test("PLUMB_H/F3", H(1, 2, 3), PLUMB_F3(1, 2, 3)) ? passed++ : failed++;
    run_test("PLUMB_I/F4", I(1, 2, 3), PLUMB_F4(1, 2, 3)) ? passed++ : failed++;

    // Colin Plumb does not implement ROTATE_LEFT, it is implemented within the STEP function
    a = 1;
    int plumb_a  = 1;
    run_test("PLUMB_FF", STEP(F, a, 2, 3, 4, 5, 6, 7), PLUMB_MD5STEP(PLUMB_F1, plumb_a, 2, 3, 4, 5 + 7, 6)) ? passed++ : failed++;
    run_test("PLUMB_GG", STEP(G, a, 2, 3, 4, 5, 6, 7), PLUMB_MD5STEP(PLUMB_F2, plumb_a, 2, 3, 4, 5 + 7, 6)) ? passed++ : failed++;
    run_test("PLUMB_HH", STEP(H, a, 2, 3, 4, 5, 6, 7), PLUMB_MD5STEP(PLUMB_F3, plumb_a, 2, 3, 4, 5 + 7, 6)) ? passed++ : failed++;
    run_test("PLUMB_II", STEP(I, a, 2, 3, 4, 5, 6, 7), PLUMB_MD5STEP(PLUMB_F4, plumb_a, 2, 3, 4, 5 + 7, 6)) ? passed++ : failed++;
 */

    // Full tests
    char* test_str = "";
    struct md5_context context;
    struct md5_digest digest;

    md5_init(&context);
    md5_update(&context, test_str, (unsigned long)strlen(test_str));
    md5_finalize(&context, &digest);
    printf("md5(\"%s\") = ", test_str);
    for(int i=0; i<sizeof(digest); i++)
    {
        printf("%2.2x", digest.bytes[i]);
    }
    puts(" should be d41d8cd98f00b204e9800998ecf8427e");


    test_str = "a";
    
    md5_init(&context);
    md5_update(&context, test_str, (unsigned long)strlen(test_str));
    md5_finalize(&context, &digest);
    printf("md5(\"%s\") = ", test_str);
    for(int i=0; i<sizeof(digest); i++)
    {
        printf("%2.2x", digest.bytes[i]);
    }
    puts(" should be 0cc175b9c0f1b6a831c399e269772661");

    test_str = "abc";
    md5_init(&context);
    md5_update(&context, test_str, (unsigned long)strlen(test_str));
    md5_finalize(&context, &digest);
    printf("md5(\"%s\") = ", test_str);
    for(int i=0; i<sizeof(digest); i++)
    {
        printf("%2.2x", digest.bytes[i]);
    }
    puts(" should be 900150983cd24fb0d6963f7d28e17f72");

    test_str = "message digest";
    md5_init(&context);
    md5_update(&context, test_str, (unsigned long)strlen(test_str));
    md5_finalize(&context, &digest);
    printf("md5(\"%s\") = ", test_str);
    for(int i=0; i<sizeof(digest); i++)
    {
        printf("%2.2x", digest.bytes[i]);
    }
    puts(" should be f96b697d7cb7938d525a2f31aaf161d0");

    test_str = "abcdefghijklmnopqrstuvwxyz";
    md5_init(&context);
    md5_update(&context, test_str, (unsigned long)strlen(test_str));
    md5_finalize(&context, &digest);
    printf("md5(\"%s\") = ", test_str);
    for(int i=0; i<sizeof(digest); i++)
    {
        printf("%2.2x", digest.bytes[i]);
    }
    puts(" should be c3fcd3d76192e4007dfb496cca67e13b");

    test_str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    md5_init(&context);
    md5_update(&context, test_str, (unsigned long)strlen(test_str));
    md5_finalize(&context, &digest);
    printf("md5(\"%s\") = ", test_str);
    for(int i=0; i<sizeof(digest); i++)
    {
        printf("%2.2x", digest.bytes[i]);
    }
    puts(" should be d174ab98d277d9f5a5611c2c9f419d9f");

    test_str = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
    md5_init(&context);
    md5_update(&context, test_str, (unsigned long)strlen(test_str));
    md5_finalize(&context, &digest);
    printf("md5(\"%s\") = ", test_str);
    for(int i=0; i<sizeof(digest); i++)
    {
        printf("%2.2x", digest.bytes[i]);
    }
    puts(" should be 57edf4a22be3c955ac49da2e2107b67a");

    //printf("Tests Passed: %i\n", passed);
    //printf("Tests Failed: %i\n", failed);
    return failed;
}