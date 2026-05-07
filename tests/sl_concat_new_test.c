// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_concat_new_test.c -o test_sl_concat_new
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

static void test_sl_concat_new(void)
{
    /* NULL inputs */
    t_sl *a = sl_from_str("hello");
    ASSERT_OK(sl_concat_new(NULL, a) == NULL);
    ASSERT_OK(sl_concat_new(a, NULL) == NULL);

    /* normal concat */
    t_sl *b = sl_from_str(" world");
    t_sl *c = sl_concat_new(a, b);
    ASSERT_OK(c != NULL);
    ASSERT_OK(c->len == 11);
    ASSERT_OK(memcmp(c->str, "hello world", 11) == 0);
    ASSERT_OK(c->str[c->len] == '\0');
    sl_free(c);

    /* concat with empty */
    t_sl *empty = sl_new(0);
    t_sl *c2 = sl_concat_new(a, empty);
    ASSERT_OK(c2 != NULL);
    ASSERT_OK(c2->len == a->len);
    ASSERT_OK(memcmp(c2->str, "hello", 5) == 0);
    sl_free(c2);

    sl_free(a);
    sl_free(b);
    sl_free(empty);
}

int main(void)
{
    test_sl_concat_new();
    fprintf(stderr, "All sl_concat_new tests passed.\n");
    return 0;
}
