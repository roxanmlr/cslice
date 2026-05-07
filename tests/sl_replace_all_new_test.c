// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_replace_all_new_test.c -o test_sl_replace_all_new
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

static void test_sl_replace_all_new(void)
{
    t_sl *s   = sl_from_str("aabbaa");
    t_sl *old = sl_from_str("aa");
    t_sl *nw  = sl_from_str("x");

    /* NULL inputs */
    ASSERT_OK(sl_replace_all_new(NULL, old, nw) == NULL);
    ASSERT_OK(sl_replace_all_new(s, NULL, nw)   == NULL);
    ASSERT_OK(sl_replace_all_new(s, old, NULL)  == NULL);

    /* replaces all occurrences: "aabbaa" -> "xbbx" */
    t_sl *r = sl_replace_all_new(s, old, nw);
    ASSERT_OK(r != NULL);
    ASSERT_OK(memcmp(r->str, "xbbx", r->len) == 0);
    ASSERT_OK(r->str[r->len] == '\0');
    sl_free(r);

    /* old not present -> clone of original */
    t_sl *absent = sl_from_str("z");
    t_sl *r2 = sl_replace_all_new(s, absent, nw);
    ASSERT_OK(r2 != NULL);
    ASSERT_OK(r2->len == s->len);
    sl_free(r2);
    sl_free(absent);

    sl_free(s); sl_free(old); sl_free(nw);
}

int main(void)
{
    test_sl_replace_all_new();
    fprintf(stderr, "All sl_replace_all_new tests passed.\n");
    return 0;
}
