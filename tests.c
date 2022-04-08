#include <stdio.h>
#include <stdlib.h>
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

int run_tests() {
    int passed = 0, failed = 0;

    run_test("md5(\"\")", md5(""), "d41d8cd98f00b204e9800998ecf8427e") ? passed++ : failed++;
    run_test("md5(\"a\")", md5("a"), "0cc175b9c0f1b6a831c399e269772661") ? passed++ : failed++;
    run_test("md5(\"abc\")", md5("abc"), "900150983cd24fb0d6963f7d28e17f72") ? passed++ : failed++;
    run_test("md5(\"message digest\")", md5("message digest"), "f96b697d7cb7938d525a2f31aaf161d0") ? passed++ : failed++;
    run_test("md5(\"abcdefghijklmnopqrstuvwxyz\")", \
        md5("abcdefghijklmnopqrstuvwxyz"), \
        "c3fcd3d76192e4007dfb496cca67e13b") ? passed++ : failed++;
    run_test("md5(\"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\")", \
        md5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"), \
        "d174ab98d277d9f5a5611c2c9f419d9f") ? passed++ : failed++;
    run_test("md5(\"12345678901234567890123456789012345678901234567890123456789012345678901234567890\")", \
        md5("12345678901234567890123456789012345678901234567890123456789012345678901234567890"), \
        "57edf4a22be3c955ac49da2e2107b67a") ? passed++ : failed++;

    char *str = "the quick brown fox jumped over the lazy dog.\n"
        "the quick brown fox jumped over the lazy dog.\n"
        "the quick brown fox jumped over the lazy dog.\n"
        "the quick brown fox jumped over the lazy dog.\n"
        "the quick brown fox jumped over the lazy dog.\n"
        "the quick brown fox jumped over the lazy dog.\n";

    run_test(str, md5(str), "590769b959d6d65ccb16c7fb0decc950") ? passed++ : failed++;

    printf("Tests Passed: %i\n", passed);
    printf("Tests Failed: %i\n", failed);
    return failed;
}

int run_benchmarks(int test_count) {
    printf("starting %d iterations of md5\n", test_count);
    char* buffer = (char*) malloc(32);
    for(int i = 0; i < test_count; i++) {
        md5((char*)buffer);
    }
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("md5 test options:\n\t-t | --test\n\t-b | --bench\n");
        return 0;
    }
    if (argc == 2 && (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "--test") == 0)) {
        return run_tests();
    }
    if (argc == 2 && (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "--bench") == 0)) {
        return run_benchmarks(1000000);
    }
}
