// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_trim_space_new_test.c -o test_sl_trim_space_new
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

static void test_sl_trim_space_new(void)
{
    /* NULL input */
    ASSERT_OK(sl_trim_space_new(NULL) == NULL);

    /* spaces, tabs, \n, \r */
    t_sl *s = sl_from_str("  \t hello \n\r ");
    t_sl *r = sl_trim_space_new(s);
    ASSERT_OK(r != NULL);
    ASSERT_OK(r->len == 5);
    ASSERT_OK(memcmp(r->str, "hello", 5) == 0);
    ASSERT_OK(r->str[r->len] == '\0');
    sl_free(r);
    sl_free(s);

    /* already trimmed */
    t_sl *clean = sl_from_str("hello");
    t_sl *r2 = sl_trim_space_new(clean);
    ASSERT_OK(r2 != NULL);
    ASSERT_OK(r2->len == 5);
    sl_free(r2);
    sl_free(clean);

    /* all whitespace -> empty */
    t_sl *ws = sl_from_str("   \t\n");
    t_sl *r3 = sl_trim_space_new(ws);
    ASSERT_OK(r3 != NULL);
    ASSERT_OK(r3->len == 0);
    ASSERT_OK(r3->str[0] == '\0');
    sl_free(r3);
    sl_free(ws);
}

int main(void)
{
    test_sl_trim_space_new();
    fprintf(stderr, "All sl_trim_space_new tests passed.\n");
    return 0;
}
