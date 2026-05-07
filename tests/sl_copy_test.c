// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_copy_test.c -o test_sl_copy
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

static void test_sl_copy(void)
{
    /* NULL inputs */
    t_sl *src = sl_from_str("hello");
    t_sl *dst = sl_new(10);
    ASSERT_OK(sl_copy(NULL, src, 5) == 0);
    ASSERT_OK(sl_copy(dst, NULL, 5) == 0);
    ASSERT_OK(sl_copy(dst, src, 0) == 0);

    /* normal copy: copies min(maxlen, dest->cap, src->len) */
    size_t n = sl_copy(dst, src, 100);
    ASSERT_OK(dst->len == src->len);
    ASSERT_OK(memcmp(dst->str, "hello", 5) == 0);
    ASSERT_OK(dst->str[dst->len] == '\0');
    (void)n;

    /* copy limited by maxlen */
    t_sl *dst2 = sl_new(10);
    sl_copy(dst2, src, 3);
    ASSERT_OK(dst2->len == 3);
    ASSERT_OK(memcmp(dst2->str, "hel", 3) == 0);
    ASSERT_OK(dst2->str[dst2->len] == '\0');
    sl_free(dst2);

    /* copy into smaller cap: limited by dest->cap */
    t_sl *small = sl_new(2);
    sl_copy(small, src, 100);
    ASSERT_OK(small->len == 2);
    ASSERT_OK(small->str[small->len] == '\0');
    sl_free(small);

    sl_free(src);
    sl_free(dst);
}

int main(void)
{
    test_sl_copy();
    fprintf(stderr, "All sl_copy tests passed.\n");
    return 0;
}
