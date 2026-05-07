// gcc -Wall -Wextra -g -fsanitize=address,undefined ../cslice.c sl_split_new_test.c -o test_sl_split_new
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

static void test_sl_split_new(void)
{
    /* NULL inputs */
    t_sl *sep = sl_from_str(",");
    ASSERT_OK(sl_split_new(NULL, sep, 0, 100) == NULL);
    t_sl *s = sl_from_str("a,b,c");
    ASSERT_OK(sl_split_new(s, NULL, 0, s->len) == NULL);

    /* normal split on "," */
    t_sl **parts = sl_split_new(s, sep, 0, s->len);
    ASSERT_OK(parts != NULL);
    ASSERT_OK(parts[0] != NULL && memcmp(parts[0]->str, "a", 1) == 0);
    ASSERT_OK(parts[1] != NULL && memcmp(parts[1]->str, "b", 1) == 0);
    ASSERT_OK(parts[2] != NULL && memcmp(parts[2]->str, "c", 1) == 0);
    ASSERT_OK(parts[3] == NULL);  /* NULL-terminated */
    sl_free_array(parts);

    /* separator not present -> array with one element = full string */
    t_sl *nosep = sl_from_str("hello");
    t_sl *sep2 = sl_from_str(",");
    t_sl **one = sl_split_new(nosep, sep2, 0, nosep->len);
    ASSERT_OK(one != NULL);
    ASSERT_OK(one[0] != NULL);
    ASSERT_OK(one[1] == NULL);
    sl_free_array(one);

    sl_free(s); sl_free(sep); sl_free(nosep); sl_free(sep2);
}

int main(void)
{
    test_sl_split_new();
    fprintf(stderr, "All sl_split_new tests passed.\n");
    return 0;
}
