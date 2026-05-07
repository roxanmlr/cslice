// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_hasprefix_test.c -o test_sl_hasprefix
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

static void test_sl_hasprefix(void)
{
    /* NULL inputs */
    t_sl *s = sl_from_str("foobar");
    t_sl *pre = sl_from_str("foo");
    ASSERT_OK(sl_hasprefix(NULL, pre) == false);
    ASSERT_OK(sl_hasprefix(s, NULL) == false);

    /* has prefix */
    ASSERT_OK(sl_hasprefix(s, pre) == true);

    /* does not have prefix */
    t_sl *wrong = sl_from_str("bar");
    ASSERT_OK(sl_hasprefix(s, wrong) == false);
    sl_free(wrong);

    /* empty prefix -> true (every string has empty prefix) */
    t_sl *empty = sl_new(0);
    ASSERT_OK(sl_hasprefix(s, empty) == true);
    sl_free(empty);

    /* prefix longer than string -> false */
    t_sl *longer = sl_from_str("foobarxxx");
    ASSERT_OK(sl_hasprefix(s, longer) == false);
    sl_free(longer);

    sl_free(s);
    sl_free(pre);
}

int main(void)
{
    test_sl_hasprefix();
    fprintf(stderr, "All sl_hasprefix tests passed.\n");
    return 0;
}
