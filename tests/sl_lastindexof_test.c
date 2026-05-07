// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_lastindexof_test.c -o test_sl_lastindexof
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

static void test_sl_lastindexof(void)
{
    /* NULL input */
    ASSERT_OK(sl_lastindexof(NULL, 'a', 0) == -1);

    t_sl *s = sl_from_str("banana");

    /* last 'a' is at index 5 */
    ASSERT_OK(sl_lastindexof(s, 'a', 0) == 5);

    /* last 'n' is at index 4 */
    ASSERT_OK(sl_lastindexof(s, 'n', 0) == 4);

    /* minindex beyond last occurrence -> not found */
    ASSERT_OK(sl_lastindexof(s, 'b', 1) == -1);

    /* char not present */
    ASSERT_OK(sl_lastindexof(s, 'z', 0) == -1);

    sl_free(s);
}

int main(void)
{
    test_sl_lastindexof();
    fprintf(stderr, "All sl_lastindexof tests passed.\n");
    return 0;
}
