// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_trim_suffix_new_test.c -o test_sl_trim_suffix_new
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

static void test_sl_trim_suffix_new(void)
{
    /* NULL inputs */
    t_sl *suf = sl_from_str("bar");
    ASSERT_OK(sl_trim_suffix_new(NULL, suf) == NULL);
    t_sl *s = sl_from_str("foobar");
    ASSERT_OK(sl_trim_suffix_new(s, NULL) == NULL);

    /* suffix present -> stripped */
    t_sl *r = sl_trim_suffix_new(s, suf);
    ASSERT_OK(r != NULL);
    ASSERT_OK(r->len == 3);
    ASSERT_OK(memcmp(r->str, "foo", 3) == 0);
    ASSERT_OK(r->str[r->len] == '\0');
    sl_free(r);

    /* suffix absent -> clone of original */
    t_sl *wrong = sl_from_str("baz");
    t_sl *r2 = sl_trim_suffix_new(s, wrong);
    ASSERT_OK(r2 != NULL);
    ASSERT_OK(r2->len == s->len);
    ASSERT_OK(memcmp(r2->str, s->str, s->len) == 0);
    sl_free(r2);
    sl_free(wrong);

    /* empty suffix -> clone of original */
    t_sl *empty = sl_new(0);
    t_sl *r3 = sl_trim_suffix_new(s, empty);
    ASSERT_OK(r3 != NULL);
    ASSERT_OK(r3->len == s->len);
    sl_free(r3);
    sl_free(empty);

    sl_free(s); sl_free(suf);
}

int main(void)
{
    test_sl_trim_suffix_new();
    fprintf(stderr, "All sl_trim_suffix_new tests passed.\n");
    return 0;
}
