// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_resize_cap_test.c -o test_sl_resize_cap
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

static void test_sl_resize_cap(void)
{
    /* NULL input */
    ASSERT_OK(sl_resize_cap(NULL, 10) == false);

    /* grow */
    t_sl *s = sl_from_str("hello");
    ASSERT_OK(sl_resize_cap(s, 20) == true);
    ASSERT_OK(s->cap == 20);
    ASSERT_OK(s->len == 5);
    ASSERT_OK(memcmp(s->str, "hello", 5) == 0);
    ASSERT_OK(s->str[s->len] == '\0');

    /* shrink: len should be clamped to new cap */
    ASSERT_OK(sl_resize_cap(s, 3) == true);
    ASSERT_OK(s->cap == 3);
    ASSERT_OK(s->len == 3);
    ASSERT_OK(s->str[s->len] == '\0');

    /* shrink to zero */
    ASSERT_OK(sl_resize_cap(s, 0) == true);
    ASSERT_OK(s->cap == 0);
    ASSERT_OK(s->len == 0);
    ASSERT_OK(s->str[0] == '\0');

    sl_free(s);
}

int main(void)
{
    test_sl_resize_cap();
    fprintf(stderr, "All sl_resize_cap tests passed.\n");
    return 0;
}
