// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_sub_new_test.c -o test_sl_sub_new
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

static void test_sl_sub_new(void)
{
    /* NULL input */
    ASSERT_OK(sl_sub_new(NULL, 0, 5) == NULL);

    t_sl *s = sl_from_str("hello world");

    /* normal sub: "world" */
    t_sl *sub = sl_sub_new(s, 6, 5);
    ASSERT_OK(sub != NULL);
    ASSERT_OK(sub->len == 5);
    ASSERT_OK(memcmp(sub->str, "world", 5) == 0);
    ASSERT_OK(sub->str[sub->len] == '\0');
    sl_free(sub);

    /* start beyond len -> empty result */
    t_sl *oob = sl_sub_new(s, 100, 5);
    ASSERT_OK(oob != NULL);
    ASSERT_OK(oob->len == 0);
    sl_free(oob);

    /* maxlen=0 -> empty result */
    t_sl *z = sl_sub_new(s, 0, 0);
    ASSERT_OK(z != NULL);
    ASSERT_OK(z->len == 0);
    sl_free(z);

    sl_free(s);
}

int main(void)
{
    test_sl_sub_new();
    fprintf(stderr, "All sl_sub_new tests passed.\n");
    return 0;
}
