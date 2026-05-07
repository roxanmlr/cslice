// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_repeat_new_test.c -o test_sl_repeat_new
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

static void test_sl_repeat_new(void)
{
    /* NULL input */
    ASSERT_OK(sl_repeat_new(NULL, 3) == NULL);

    t_sl *ab = sl_from_str("ab");

    /* repeat 3 times */
    t_sl *r = sl_repeat_new(ab, 3);
    ASSERT_OK(r != NULL);
    ASSERT_OK(r->len == 6);
    ASSERT_OK(memcmp(r->str, "ababab", 6) == 0);
    ASSERT_OK(r->str[r->len] == '\0');
    sl_free(r);

    /* repeat 0 times -> empty */
    t_sl *r0 = sl_repeat_new(ab, 0);
    ASSERT_OK(r0 != NULL);
    ASSERT_OK(r0->len == 0);
    ASSERT_OK(r0->str[0] == '\0');
    sl_free(r0);

    /* repeat 1 time -> same content */
    t_sl *r1 = sl_repeat_new(ab, 1);
    ASSERT_OK(r1 != NULL);
    ASSERT_OK(r1->len == 2);
    ASSERT_OK(memcmp(r1->str, "ab", 2) == 0);
    sl_free(r1);

    sl_free(ab);
}

int main(void)
{
    test_sl_repeat_new();
    fprintf(stderr, "All sl_repeat_new tests passed.\n");
    return 0;
}
