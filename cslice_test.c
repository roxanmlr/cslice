#include "cslice.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define ASSERT_OK(expr) 							\
		do {										\
			assert(expr);  							\
			fprintf(stderr, "[OK] %s\n", #expr);	\
		} while (0)									\

void test_sl_new(size_t cap)
{
	t_sl *s = sl_new(cap);
	ASSERT_OK(s);
	ASSERT_OK(!s->len);
	ASSERT_OK(s->str);
	ASSERT_OK(!(s->str)[s->len]);
	ASSERT_OK(s->cap >= cap);
	sl_free(s);
}

void test_sl_resize_existing_sl(t_sl *s, size_t newcap)
{
	if (!s)
		return ;
	char *str_dup = malloc(sizeof(char) * (s->len + 1));
	if (!str_dup)
		return ;
	memmove(str_dup, s->str, s->len + 1);
	sl_resize_cap(s, newcap);
	ASSERT_OK(!memcmp(str_dup, s->str, s->len));
	free(str_dup);
}

void test_sl_clone_new(size_t cap)
{
	t_sl *s = sl_new(cap);
	ASSERT_OK(s);
	for (size_t i = 0; i < cap; ++i, ++(s->len))
		(s->str)[i] = rand() % 0x100;
	t_sl *clone = sl_clone_new(s);
	ASSERT_OK(clone);
	ASSERT_OK(!memcmp(s->str, clone->str, clone->len));
	ASSERT_OK(clone->cap >= s->cap);
	ASSERT_OK(clone->len == s->len);
	sl_free(s);
	sl_free(clone);
}

void test_sl_resize_new_sl(size_t cap1, size_t cap2)
{
	t_sl *s = sl_new(cap1);
	if (!s)
		return ;
	sl_resize_cap(s, cap2);
	ASSERT_OK(s);
	ASSERT_OK(s->str);
	ASSERT_OK(!(s->str)[s->len]);
	ASSERT_OK(s->cap >= cap2);
	sl_free(s);
}

#define STR "01234567890ABCDEFGHIJKL"
int main(void)
{
	test_sl_new(0);
	test_sl_new(10);
	test_sl_new(1024);
	test_sl_resize_new_sl(0, 5);
	test_sl_resize_new_sl(10, 12);
	test_sl_resize_new_sl(13, 11);
	test_sl_resize_new_sl(1024, 0);
	t_sl *s = sl_new(strlen(STR));
	if (!s)
		return EXIT_FAILURE;
	memmove(s->str, STR, strlen(STR) + 1);
	s->len = strlen(STR);
	s->cap = s->len;
	test_sl_resize_existing_sl(s, strlen(STR) + 1);
	test_sl_resize_existing_sl(s, strlen(STR)-1);
	sl_free(s);
	test_sl_clone_new(10);
	test_sl_clone_new(2042);
	test_sl_clone_new(0);
}
