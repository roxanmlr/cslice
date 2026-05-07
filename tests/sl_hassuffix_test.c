// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_hassuffix_test.c -o test_sl_hassuffix
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

static void test_sl_hassuffix(void)
{
    /* NULL inputs */
    t_sl *s = sl_from_str("foobar");
    t_sl *suf = sl_from_str("bar");
    ASSERT_OK(sl_hassuffix(NULL, suf) == false);
    ASSERT_OK(sl_hassuffix(s, NULL) == false);

    /* has suffix */
    ASSERT_OK(sl_hassuffix(s, suf) == true);

    /* does not have suffix */
    t_sl *wrong = sl_from_str("foo");
    ASSERT_OK(sl_hassuffix(s, wrong) == false);
    sl_free(wrong);

    /* empty suffix -> true */
    t_sl *empty = sl_new(0);
    ASSERT_OK(sl_hassuffix(s, empty) == true);
    sl_free(empty);

    /* suffix longer than string -> false */
    t_sl *longer = sl_from_str("xxxfoobar");
    ASSERT_OK(sl_hassuffix(s, longer) == false);
    sl_free(longer);

    sl_free(s);
    sl_free(suf);
}

int main(void)
{
    test_sl_hassuffix();
    fprintf(stderr, "All sl_hassuffix tests passed.\n");
    return 0;
}
