// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_free_test.c -o test_sl_free
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

static t_sl *sl_from_str(const char *str)
{
    size_t len = strlen(str);
    t_sl *s = sl_new(len);
    if (!s)
        return NULL;
    memcpy(s->str, str, len + 1);
    s->len = len;
    return s;
}

static void test_sl_free(void)
{
    /* NULL must not crash */
    sl_free(NULL);
    ASSERT_OK(1);

    /* normal free: ASAN will catch leaks/double-free */
    t_sl *s = sl_from_str("hello");
    ASSERT_OK(s != NULL);
    sl_free(s);
    ASSERT_OK(1);

    /* free zero-cap slice */
    t_sl *empty = sl_new(0);
    ASSERT_OK(empty != NULL);
    sl_free(empty);
    ASSERT_OK(1);
}

int main(void)
{
    test_sl_free();
    fprintf(stderr, "All sl_free tests passed.\n");
    return 0;
}
