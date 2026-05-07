// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_compare_test.c -o test_sl_compare
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

static void test_sl_compare(void)
{
    /* NULL inputs */
    t_sl *a = sl_from_str("abc");
    ASSERT_OK(sl_compare(NULL, a, 3) < 0 || sl_compare(NULL, a, 3) > 0 || sl_compare(NULL, a, 3) == 0);
    /* (implementation-defined for NULL; at minimum must not crash) */

    t_sl *b = sl_from_str("abc");
    t_sl *c = sl_from_str("abd");
    t_sl *d = sl_from_str("abb");

    /* equal */
    ASSERT_OK(sl_compare(a, b, a->len) == 0);

    /* a < c */
    ASSERT_OK(sl_compare(a, c, a->len) < 0);

    /* a > d */
    ASSERT_OK(sl_compare(a, d, a->len) > 0);

    /* maxlen=0 -> equal */
    ASSERT_OK(sl_compare(a, c, 0) == 0);

    /* maxlen limits comparison */
    ASSERT_OK(sl_compare(a, c, 2) == 0);

    sl_free(a); sl_free(b); sl_free(c); sl_free(d);
}

int main(void)
{
    test_sl_compare();
    fprintf(stderr, "All sl_compare tests passed.\n");
    return 0;
}
