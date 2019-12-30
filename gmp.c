#include <emscripten.h>
#include <gmp.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

mpz_t *result = NULL;

mpz_t *allocate_result() {
    if (!result) {
        mpz_clear(*result);
        free(result);
    }
    result = (mpz_t *) malloc(sizeof(mpz_t));
    mpz_init(*result);
    return result;
}

EMSCRIPTEN_KEEPALIVE
char *get_result() {
    if (!result) {
        return NULL;
    }

    char *str = mpz_get_str(NULL, 10, *result);

    mpz_clear(*result);
    free(result);
    result = NULL;

    return str;
}

EMSCRIPTEN_KEEPALIVE
void naive_factorial(size_t nth) {
    allocate_result();

    mpz_set_ui(*result, 1);

    for (size_t i = 2; i <= nth; ++i) {
        mpz_mul_ui(*result, *result, i);
    }
}

EMSCRIPTEN_KEEPALIVE
void factorial(size_t nth) {
    allocate_result();

    mpz_fac_ui(*result, nth);
}

EMSCRIPTEN_KEEPALIVE
void naive_fibonacci(size_t nth) {
    allocate_result();

    mpz_t next, t;
    mpz_init(next);
    mpz_init(t);

    mpz_set_ui(*result, 0);
    mpz_set_ui(next, 1);

    for (size_t i = 0; i < nth; ++i) {
        mpz_add(t, *result, next);
        mpz_set(*result, next);
        mpz_set(next, t);
    }

    mpz_clear(t);
    mpz_clear(next);
}


EMSCRIPTEN_KEEPALIVE
void fibonacci(size_t nth) {
    allocate_result();

    mpz_fib_ui(*result, nth);
}

#ifdef __cplusplus
}
#endif
