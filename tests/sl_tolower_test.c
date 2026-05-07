// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_tolower_test.c -o test_sl_tolower
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

static void test_sl_tolower(void)
{
    /* NULL must not crash */
    sl_tolower(NULL);
    ASSERT_OK(1);

    /* normal lowercasing */
    t_sl *s = sl_from_str("Hello World 123");
    sl_tolower(s);
    ASSERT_OK(memcmp(s->str, "hello world 123", s->len) == 0);
    ASSERT_OK(s->str[s->len] == '\0');
    sl_free(s);

    /* already lowercase -> unchanged */
    t_sl *s2 = sl_from_str("already");
    sl_tolower(s2);
    ASSERT_OK(memcmp(s2->str, "already", 7) == 0);
    sl_free(s2);

    /* empty slice */
    t_sl *empty = sl_new(0);
    sl_tolower(empty);
    ASSERT_OK(empty->len == 0);
    sl_free(empty);
}

int main(void)
{
    test_sl_tolower();
    fprintf(stderr, "All sl_tolower tests passed.\n");
    return 0;
}
