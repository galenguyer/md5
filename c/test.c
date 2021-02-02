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

int main(int argc, char** argv) {
    int passed = 0, failed = 0;
    run_test("step F", F(1, 2, 3), (((1) & (2)) | ((~1) & (3)))) ? passed++ : failed++;
    run_test("step G", G(1, 2, 3), (((1) & (3)) | ((2) & (~3)))) ? passed ++ : failed++;
    run_test("step H", H(1, 2, 3), ((1) ^ (2) ^ (3))) ? passed++ : failed++;
    run_test("step I", I(1, 2, 3), ((2) ^ ((1) | (~3)))) ? passed++ : failed++;

    run_test("rotate_left", ROTATE_LEFT(24, 2), (((24) << (2)) | ((24) >> (32-(2))))) ? passed++ : failed++;

    printf("Tests Passed: %i\n", passed);
    printf("Tests Failed: %i\n", failed);
    return failed;
}