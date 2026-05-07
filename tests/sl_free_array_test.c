// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_free_array_test.c -o test_sl_free_array
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

/* Build a NULL-terminated t_sl** array manually */
static t_sl **make_array(const char **strs, size_t n)
{
    t_sl **arr = malloc(sizeof(t_sl *) * (n + 1));
    if (!arr)
        return NULL;
    for (size_t i = 0; i < n; i++)
        arr[i] = sl_from_str(strs[i]);
    arr[n] = NULL;
    return arr;
}

static void test_sl_free_array(void)
{
    /* NULL must not crash */
    sl_free_array(NULL);
    ASSERT_OK(1);

    /* array with multiple elements: ASAN verifies each element is fully freed
       (sl_free frees both the t_sl struct AND its inner str buffer;
        a plain free() would leak the inner buffer) */
    const char *words[] = {"foo", "bar", "baz"};
    t_sl **arr = make_array(words, 3);
    ASSERT_OK(arr != NULL);
    sl_free_array(arr);
    ASSERT_OK(1);

    /* array with one element */
    const char *one[] = {"only"};
    t_sl **arr2 = make_array(one, 1);
    ASSERT_OK(arr2 != NULL);
    sl_free_array(arr2);
    ASSERT_OK(1);
}

int main(void)
{
    test_sl_free_array();
    fprintf(stderr, "All sl_free_array tests passed.\n");
    return 0;
}
