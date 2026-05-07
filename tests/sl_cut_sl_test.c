// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_cut_sl_test.c -o test_sl_cut_sl
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

static void test_sl_cut_sl(void)
{
    t_sl *sep = sl_from_str("::");
    t_sl *before = NULL, *after = NULL;

    /* NULL slice */
    ASSERT_OK(sl_cut_sl(NULL, sep, &before, &after) == -1);

    t_sl *s = sl_from_str("key::value");

    /* separator found */
    ssize_t pos = sl_cut_sl(s, sep, &before, &after);
    ASSERT_OK(pos == 3);
    ASSERT_OK(before != NULL && memcmp(before->str, "key", 3) == 0);
    ASSERT_OK(after  != NULL && memcmp(after->str, "value", 5) == 0);
    sl_free(before); before = NULL;
    sl_free(after);  after  = NULL;

    /* separator not found */
    t_sl *nosep = sl_from_str("nosep");
    ssize_t pos2 = sl_cut_sl(nosep, sep, &before, &after);
    ASSERT_OK(pos2 == -1);
    ASSERT_OK(before != NULL);
    ASSERT_OK(after  != NULL && after->len == 0);
    sl_free(before);
    sl_free(after);

    sl_free(s); sl_free(sep); sl_free(nosep);
}

int main(void)
{
    test_sl_cut_sl();
    fprintf(stderr, "All sl_cut_sl tests passed.\n");
    return 0;
}
