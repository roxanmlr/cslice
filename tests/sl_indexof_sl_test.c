// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_indexof_sl_test.c -o test_sl_indexof_sl
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

static void test_sl_indexof_sl(void)
{
    t_sl *hay = sl_from_str("hello world");
    t_sl *needle = sl_from_str("world");

    /* NULL inputs */
    ASSERT_OK(sl_indexof_sl(NULL, needle, 100) == -1);
    ASSERT_OK(sl_indexof_sl(hay, NULL, 100) == -1);

    /* found */
    ASSERT_OK(sl_indexof_sl(hay, needle, hay->len) == 6);

    /* not found */
    t_sl *missing = sl_from_str("xyz");
    ASSERT_OK(sl_indexof_sl(hay, missing, hay->len) == -1);
    sl_free(missing);

    /* maxlen cuts the search area */
    ASSERT_OK(sl_indexof_sl(hay, needle, 5) == -1);

    /* empty needle -> found at 0 */
    t_sl *empty = sl_new(0);
    ASSERT_OK(sl_indexof_sl(hay, empty, hay->len) == 0);
    sl_free(empty);

    sl_free(hay);
    sl_free(needle);
}

int main(void)
{
    test_sl_indexof_sl();
    fprintf(stderr, "All sl_indexof_sl tests passed.\n");
    return 0;
}
