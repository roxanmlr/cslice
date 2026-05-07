// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_cut_test.c -o test_sl_cut
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

static void test_sl_cut(void)
{
    /* NULL slice */
    t_sl *before = NULL, *after = NULL;
    ASSERT_OK(sl_cut(NULL, ':', &before, &after) == -1);

    t_sl *s = sl_from_str("key:value");

    /* separator found: returns position */
    ssize_t pos = sl_cut(s, ':', &before, &after);
    ASSERT_OK(pos == 3);

    /* before should contain "key" */
    ASSERT_OK(before != NULL);
    ASSERT_OK(before->len == 3);
    ASSERT_OK(memcmp(before->str, "key", 3) == 0);

    /* after should contain "value" */
    ASSERT_OK(after != NULL);
    ASSERT_OK(after->len == 5);
    ASSERT_OK(memcmp(after->str, "value", 5) == 0);

    sl_free(before); before = NULL;
    sl_free(after);  after = NULL;
    sl_free(s);

    /* separator not found: before = full string, after = empty */
    t_sl *s2 = sl_from_str("nosep");
    ssize_t pos2 = sl_cut(s2, ':', &before, &after);
    ASSERT_OK(pos2 == -1);
    ASSERT_OK(before != NULL);
    ASSERT_OK(before->len == 5);
    ASSERT_OK(after != NULL);
    ASSERT_OK(after->len == 0);
    sl_free(before);
    sl_free(after);
    sl_free(s2);
}

int main(void)
{
    test_sl_cut();
    fprintf(stderr, "All sl_cut tests passed.\n");
    return 0;
}
