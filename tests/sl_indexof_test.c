// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_indexof_test.c -o test_sl_indexof
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

static void test_sl_indexof(void)
{
    /* NULL input */
    ASSERT_OK(sl_indexof(NULL, 'a', 0, 10) == -1);

    t_sl *s = sl_from_str("hello world");

    /* found at start */
    ASSERT_OK(sl_indexof(s, 'h', 0, s->len) == 0);

    /* found in middle */
    ASSERT_OK(sl_indexof(s, 'o', 0, s->len) == 4);

    /* search after position of first match -> finds next */
    ASSERT_OK(sl_indexof(s, 'o', 5, s->len) == 7);

    /* not found */
    ASSERT_OK(sl_indexof(s, 'z', 0, s->len) == -1);

    /* maxlen cuts search short */
    ASSERT_OK(sl_indexof(s, 'o', 0, 3) == -1);

    /* start == len (at sentinel) -> not found */
    ASSERT_OK(sl_indexof(s, 'h', s->len, s->len) == -1);

    sl_free(s);
}

int main(void)
{
    test_sl_indexof();
    fprintf(stderr, "All sl_indexof tests passed.\n");
    return 0;
}
