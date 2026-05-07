// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_clone_new_test.c -o test_sl_clone_new
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

static void test_sl_clone_new(void)
{
    /* NULL input */
    ASSERT_OK(sl_clone_new(NULL) == NULL);

    /* normal clone */
    t_sl *s = sl_from_str("hello");
    t_sl *c = sl_clone_new(s);
    ASSERT_OK(c != NULL);
    ASSERT_OK(c->str != s->str);           /* deep copy, not same buffer */
    ASSERT_OK(c->len == s->len);
    ASSERT_OK(c->cap == s->cap);
    ASSERT_OK(memcmp(c->str, s->str, s->len) == 0);
    ASSERT_OK(c->str[c->len] == '\0');
    sl_free(s);
    sl_free(c);

    /* empty slice */
    t_sl *empty = sl_new(0);
    t_sl *ce = sl_clone_new(empty);
    ASSERT_OK(ce != NULL);
    ASSERT_OK(ce->len == 0);
    ASSERT_OK(ce->str[0] == '\0');
    sl_free(empty);
    sl_free(ce);
}

int main(void)
{
    test_sl_clone_new();
    fprintf(stderr, "All sl_clone_new tests passed.\n");
    return 0;
}
