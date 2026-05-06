/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cslice.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 11:28:14 by lmilando          #+#    #+#             */
/*   Updated: 2026/05/07 01:02:29 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cslice.h"
#include <sys/param.h>

/*Creation and destruction*/
t_sl*	sl_new(size_t cap)
{
	t_sl * r = malloc(sizeof(t_sl));
	if (!r)
		return NULL;
	r->cap = cap;
	r->str = malloc(sizeof(char) * (r->cap + 1));
	if (!r->str)
		return (free(r), NULL);
	r->len = 0;
	(r->str)[r->len] = '\0';
	return (r);
}

bool	sl_resize_cap(t_sl *s, size_t cap)
{
	if (!s)
		return false;
	char *new_str = malloc(sizeof(char) *(cap + 1));
	if (!new_str)
		return false;
	s->cap = cap;
	s->len = MIN(cap, s->len);
	for (size_t i = 0; i < s->len; ++i)
		new_str[i] = (s->str)[i];
	new_str[s->len] = '\0';
	free(s->str);
	s->str = new_str;
	return true;
}

void	sl_free(t_sl *s)
{
	if (!s)
		return ;
	free(s->str);
	free(s);
}

void	sl_free_array(t_sl **arr)
{
	if (!arr)
		return ;
	for (size_t i = 0; arr[i]; ++i)
		free(arr[i]);
	free(arr);
}

/*Creation from existing data*/
t_sl*	sl_clone_new(t_sl const *b)
{
	if (!b)
		return NULL;
	t_sl *r = sl_new(b->cap);
	if (!r)
		return NULL;
	r->cap = b->cap;
	r->len = b->len;
	(r->str)[r->len] = '\0';
	for (size_t i = 0; i < b->len; ++i)
		(r->str)[i] = (b->str)[i];
	return r;
}

t_sl*	sl_sub_new(t_sl const *b, size_t start, size_t maxlen)
{
	if (!b)
		return NULL;
	t_sl sl_null = {.str = "", .cap = 0, .len = 0};
	size_t cap = 0;
	if (b->len > start)
		cap = MIN(start -  b->len, maxlen);
	if (cap == 0)
		return sl_clone_new(&sl_null);
	t_sl *r = sl_new(cap);
	if (!r)
		return NULL;
	for (r->len = 0; r->len < cap; ++(r->len))
		(r->str)[r->len] = (b->str)[start + r->len];
	(r->str)[r->len] = '\0';
	return (r);
}

t_sl*	sl_concat_new(t_sl const *a, t_sl const *b)
{
	if (!a || !b)
		return NULL;
	t_sl *r = sl_new(a->len + b->len);
	if (!r)
		return NULL;
	for (r->len = 0; r->len < a->len; ++(r->len))	
		(r->str)[r->len] = (a->str)[r->len];
	for (size_t siz = 0; siz < b->len; ++(r->len), ++siz)
		(r->str)[r->len] = (b->str)[siz];
	(r->str)[r->len] = '\0';
	return r;
}

t_sl*	sl_repeat_new(t_sl const *a, size_t n)
{
	if (!a)
		return NULL;
	t_sl *r = sl_new(a->len * n);
	if (!r)
		return NULL;
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t siz = 0;siz < a->len; ++(r->len), ++siz)
			(r->str)[r->len] = (a->str)[siz];
	}
	(r->str)[r->len] = '\0';
	return r;
}

/*Mutation*/
size_t	sl_copy(t_sl *dest, t_sl const *src, size_t maxlen)
{
	if (!dest || !src || !maxlen)
		return 0;
	maxlen = MIN(maxlen, MIN(dest->cap, src->len));
	for (dest->len = 0; dest->len < maxlen; ++(dest->len))
		(dest->str)[dest->len] = (src->str)[dest->len];
	(dest->str)[dest->len] = '\0';
	return (dest->len - 1);
}
/* Cut */
ssize_t sl_cut(t_sl const *s, char sep, t_sl **before, t_sl **after)
{
	if (!s)
		return -1;
	ssize_t pos = sl_indexof(s, sep, 0, s->cap);	
	if (!before)
	{
		sl_free(*before);
		if (pos == -1)
			*before = sl_clone_new(s);
		else
			*before = sl_sub_new(s, 0, (size_t)pos);
	}
	if (!after)
	{
		sl_free(*after);
		if (pos == -1)
			*after = sl_clone_new(&(t_sl){.str = "", .cap = 0, .len = 0});
		else
			*after = sl_sub_new(s, (size_t)(pos + 1), s->len);
	}
	return pos;
}
ssize_t sl_cut_sl(t_sl const *b, t_sl const *sep, t_sl **before, t_sl **after);


/*Search and compare*/
ssize_t sl_indexof(t_sl const *b, char c, size_t start, size_t maxlen)
{
	if (!b)
		return (-1);
	size_t i = start;
	for (; i < b->len && i < maxlen && (b->str)[i] != c; ++i);
	return ((b->str)[i] == c) ? (ssize_t) i : -1;
}

ssize_t	sl_indexof_sl(t_sl const *haystack, t_sl const *needle);
ssize_t sl_count(t_sl const *b, char c, size_t start, size_t maxlen);
ssize_t sl_lastindexof(t_sl const *b, char c, size_t minindex);
int		sl_compare(t_sl const *a, t_sl const *b, size_t maxlen);
bool	sl_contains_sl(t_sl const *a, t_sl const *b, size_t maxlen);
bool	sl_equal(t_sl const *a, t_sl const *b);
bool	sl_hasprefix(t_sl const *a, t_sl const *b);
bool	sl_hassuffix(t_sl const *a, t_sl const *b);

/*Split and Join */
t_sl**	sl_split(t_sl const *b, t_sl const *sep, size_t start, size_t maxlen);
t_sl*	sl_join(t_sl const **s, t_sl const *sep);
