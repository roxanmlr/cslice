// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_join_new_test.c -o test_sl_join_new
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

static void test_sl_join_new(void)
{
    /* NULL inputs */
    t_sl *sep = sl_from_str(", ");
    ASSERT_OK(sl_join_new(NULL, sep) == NULL);

    t_sl *a = sl_from_str("foo");
    t_sl *b = sl_from_str("bar");
    t_sl *c = sl_from_str("baz");
    const t_sl *arr[] = {a, b, c, NULL};

    /* normal join */
    t_sl *r = sl_join_new(arr, sep);
    ASSERT_OK(r != NULL);
    ASSERT_OK(memcmp(r->str, "foo, bar, baz", r->len) == 0);
    ASSERT_OK(r->str[r->len] == '\0');
    sl_free(r);

    /* join with empty separator */
    t_sl *nosep = sl_new(0);
    t_sl *r2 = sl_join_new(arr, nosep);
    ASSERT_OK(r2 != NULL);
    ASSERT_OK(memcmp(r2->str, "foobarbaz", r2->len) == 0);
    sl_free(r2);
    sl_free(nosep);

    /* single-element array */
    const t_sl *one[] = {a, NULL};
    t_sl *r3 = sl_join_new(one, sep);
    ASSERT_OK(r3 != NULL);
    ASSERT_OK(memcmp(r3->str, "foo", 3) == 0);
    sl_free(r3);

    sl_free(a); sl_free(b); sl_free(c); sl_free(sep);
}

int main(void)
{
    test_sl_join_new();
    fprintf(stderr, "All sl_join_new tests passed.\n");
    return 0;
}
