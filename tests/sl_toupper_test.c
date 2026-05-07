// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_toupper_test.c -o test_sl_toupper
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

static void test_sl_toupper(void)
{
    /* NULL must not crash */
    sl_toupper(NULL);
    ASSERT_OK(1);

    /* normal uppercasing */
    t_sl *s = sl_from_str("Hello World 123");
    sl_toupper(s);
    ASSERT_OK(memcmp(s->str, "HELLO WORLD 123", s->len) == 0);
    ASSERT_OK(s->str[s->len] == '\0');
    sl_free(s);

    /* already uppercase -> unchanged */
    t_sl *s2 = sl_from_str("ALREADY");
    sl_toupper(s2);
    ASSERT_OK(memcmp(s2->str, "ALREADY", 7) == 0);
    sl_free(s2);

    /* empty slice */
    t_sl *empty = sl_new(0);
    sl_toupper(empty);
    ASSERT_OK(empty->len == 0);
    sl_free(empty);
}

int main(void)
{
    test_sl_toupper();
    fprintf(stderr, "All sl_toupper tests passed.\n");
    return 0;
}
