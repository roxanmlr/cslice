// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_new_test.c -o test_sl_new
#include "../cslice.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT_OK(expr) \
    do { \
        assert(expr); \
        fprintf(stderr, "[OK] %s\n", #expr); \
    } while (0)

static void test_sl_new(void)
{
    t_sl *s0 = sl_new(0);
    ASSERT_OK(s0 != NULL);
    ASSERT_OK(s0->str != NULL);
    ASSERT_OK(s0->len == 0);
    ASSERT_OK(s0->cap == 0);
    ASSERT_OK(s0->str[0] == '\0');
    sl_free(s0);

    t_sl *s = sl_new(32);
    ASSERT_OK(s != NULL);
    ASSERT_OK(s->str != NULL);
    ASSERT_OK(s->len == 0);
    ASSERT_OK(s->cap == 32);
    ASSERT_OK(s->str[s->len] == '\0');
    sl_free(s);
}

int main(void)
{
    test_sl_new();
    fprintf(stderr, "All sl_new tests passed.\n");
    return 0;
}
