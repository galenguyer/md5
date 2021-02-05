#include <stdio.h>
#include <string.h>
#include "md5.h"

int run_test(char* name, char* result, char* expected) {
    if (strcmp(expected, result) == 0) {
        printf("TEST PASSED: %s: expected %s, got %s\n", name, expected, result);
        return 1;
    } else {
        printf("TEST FAILED: %s: expected %s, got %s\n", name, expected, result);
        return 0;
    }
}

int main(int argc, char** argv) {
    int passed = 0, failed = 0;

    run_test("md5(\"\")", md5(""), "d41d8cd98f00b204e9800998ecf8427e") ? passed++ : failed++;
    run_test("md5(\"a\")", md5("a"), "0cc175b9c0f1b6a831c399e269772661") ? passed++ : failed++;
    run_test("md5(\"abc\")", md5("abc"), "900150983cd24fb0d6963f7d28e17f72") ? passed++ : failed++;
    run_test("md5(\"message digest\")", md5("message digest"), "f96b697d7cb7938d525a2f31aaf161d0") ? passed++ : failed++;
    run_test("md5(\"abcdefghijklmnopqrstuvwxyz\")", md5("abcdefghijklmnopqrstuvwxyz"), \
        "c3fcd3d76192e4007dfb496cca67e13b") ? passed++ : failed++;
    run_test("md5(\"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\")", \
        md5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"), \
        "d174ab98d277d9f5a5611c2c9f419d9f") ? passed++ : failed++;
    run_test("md5(\"12345678901234567890123456789012345678901234567890123456789012345678901234567890\")", \
        md5("12345678901234567890123456789012345678901234567890123456789012345678901234567890"), \
        "57edf4a22be3c955ac49da2e2107b67a") ? passed++ : failed++;

    printf("Tests Passed: %i\n", passed);
    printf("Tests Failed: %i\n", failed);
    return failed;
}