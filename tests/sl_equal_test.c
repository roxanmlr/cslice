// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_equal_test.c -o test_sl_equal
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

static void test_sl_equal(void)
{
    /* NULL inputs */
    t_sl *a = sl_from_str("hello");
    ASSERT_OK(sl_equal(NULL, a, 5) == false);
    ASSERT_OK(sl_equal(a, NULL, 5) == false);

    /* equal */
    t_sl *b = sl_from_str("hello");
    ASSERT_OK(sl_equal(a, b, a->len) == true);

    /* not equal */
    t_sl *c = sl_from_str("world");
    ASSERT_OK(sl_equal(a, c, a->len) == false);

    /* maxlen=0 -> equal (no bytes compared) */
    ASSERT_OK(sl_equal(a, c, 0) == true);

    /* different lengths -> not equal (full compare) */
    t_sl *d = sl_from_str("hell");
    ASSERT_OK(sl_equal(a, d, 10) == false);

    sl_free(a); sl_free(b); sl_free(c); sl_free(d);
}

int main(void)
{
    test_sl_equal();
    fprintf(stderr, "All sl_equal tests passed.\n");
    return 0;
}
