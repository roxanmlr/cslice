// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_count_test.c -o test_sl_count
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

static void test_sl_count(void)
{
    /* NULL input */
    ASSERT_OK(sl_count(NULL, 'a', 0, 10) == -1);

    t_sl *s = sl_from_str("banana");

    /* count 'a': 3 occurrences */
    ASSERT_OK(sl_count(s, 'a', 0, s->len) == 3);

    /* count from start=1: still 3 (positions 1,3,5) */
    ASSERT_OK(sl_count(s, 'a', 1, s->len) == 3);

    /* count from start=2: 2 occurrences */
    ASSERT_OK(sl_count(s, 'a', 2, s->len) == 2);

    /* maxlen limits the window */
    ASSERT_OK(sl_count(s, 'a', 0, 2) == 1);

    /* char not present */
    ASSERT_OK(sl_count(s, 'z', 0, s->len) == 0);

    sl_free(s);
}

int main(void)
{
    test_sl_count();
    fprintf(stderr, "All sl_count tests passed.\n");
    return 0;
}
