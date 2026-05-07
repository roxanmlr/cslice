// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_contains_sl_test.c -o test_sl_contains_sl
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

static void test_sl_contains_sl(void)
{
    /* NULL inputs */
    t_sl *hay = sl_from_str("hello world");
    t_sl *needle = sl_from_str("world");
    ASSERT_OK(sl_contains_sl(NULL, needle, 100) == false);
    ASSERT_OK(sl_contains_sl(hay, NULL, 100) == false);

    /* contained */
    ASSERT_OK(sl_contains_sl(hay, needle, hay->len) == true);

    /* not contained */
    t_sl *absent = sl_from_str("xyz");
    ASSERT_OK(sl_contains_sl(hay, absent, hay->len) == false);
    sl_free(absent);

    /* maxlen cuts the haystack */
    ASSERT_OK(sl_contains_sl(hay, needle, 5) == false);

    /* empty needle -> true */
    t_sl *empty = sl_new(0);
    ASSERT_OK(sl_contains_sl(hay, empty, hay->len) == true);
    sl_free(empty);

    sl_free(hay);
    sl_free(needle);
}

int main(void)
{
    test_sl_contains_sl();
    fprintf(stderr, "All sl_contains_sl tests passed.\n");
    return 0;
}
