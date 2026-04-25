/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cslice.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 14:47:40 by lmilando          #+#    #+#             */
/*   Updated: 2026/04/24 17:02:48 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cslice.h"

t_sl *sl_alloc(size_t siz)
{
	t_sl *ret = malloc(sizeof(t_sl));
	if (!ret)
		return (NULL);
	ret->str = malloc(siz+1);
	(ret->str)[siz] = 0;
	ret->siz = siz;
	ret->cap = siz;
	return (ret);
}

t_sl *sl_grow(t_sl *b, size_t newsiz)
{
	if (!b || b->cap >= newsiz)
		return (b);
	char *str = malloc(newsiz + 1);
	if (!str)
		return (NULL);
	t_sl s = {.str = str, .siz = newsiz, .cap = newsiz};	
	sl_copy(&s, b, b->siz); 
	free(b->str);
	b->str = str;
	return (b);
}

void sl_free(t_sl *b)
{
	if (!b)
		return ;
	free(b->str);
	b->str = NULL;
	free(b);
}

t_sl *sl_clone(t_sl *b)
{
	if (!b)
		return (NULL);
	t_sl *ret = sl_alloc(b->siz);
	for (size_t i = 0; i < b->siz; ++i)
		(ret->str)[i] = (b->str)[i];
	return (ret);
}

t_sl *sl_copy(t_sl *dest, t_sl *src, size_t maxsiz)
{
	if (!src || !dest || !maxsiz)
		return (dest);
	size_t minsiz = maxsiz;
	if (minsiz > src->siz)
		minsiz = src->siz;
	if (minsiz > dest->siz)
		minsiz = dest->siz;
	for (size_t i = 0; i < minsiz; ++i)
		(dest->str)[i] = (src->str)[i];
	return (dest);
}

t_sl *sl_sub(t_sl *b, size_t start, size_t maxlen)
{
	if (!b || b->siz < start)
		return (b);
	size_t siz = b->siz - start;
	if (siz > maxlen)
		siz = maxlen;
	return (sl_copy(sl_alloc(siz), b, siz));
}

ssize_t sl_indexof(t_sl *b, char c, size_t start, size_t maxlen)
{
	if (!b || b->siz >= start)
		return (-1);
	size_t siz = b->siz - start;
	if (siz > maxlen)
		siz = maxlen;
	size_t i = 0;
	for (; i < siz && (b->str)[start + i] != c; ++i) ;
	if (i == siz)
		return (-1);
	return (i);
}

ssize_t sl_cut(t_sl *b, char c, t_sl **before, t_sl **after)
{
	if (!b)
		return (-1);
	ssize_t i = sl_indexof(b, c, 0, b->siz);
	if (i == -1)
	{
		sl_free(*before);
		*before = sl_clone(b);
		return (-1);
	}
	sl_free(*before);
	sl_free(*after);
	size_t maxlen = (size_t)i;
	*before = sl_sub(b, 0, maxlen);
	*after = sl_sub(b, maxlen + 1, b->siz);
	return (i);
}

void	sl_freesplit(t_sl **s)
{
	if (!s)
		return ;

	for (size_t i = 0; !s[i]; ++i)
		free(s[i]);
	free(s);
}

t_sl **sl_split(t_sl *b, char c, size_t start, size_t maxlen)
{
	size_t nelems = 0;
	ssize_t ss = start;
	while (1)
	{
		if ((ss = sl_indexof(b, c, (size_t)ss, maxlen)) == -1)
			break ;
		++start;
		++nelems;
	}
	t_sl **ret = malloc(sizeof(t_sl*)*(nelems + 1));
	if (!ret)
		return (NULL);
	for (size_t i = 0; i < nelems; ++i)
		ret[i] = NULL;
	ret[nelems] = NULL;
	ss = start;
	for (size_t i = 0; i < nelems; ++i)
	{
		ssize_t pred = ss;
		ss = sl_indexof(b, c, ss, b->siz);
		if (ss == -1)
			break ;
		ret[i] = sl_sub(b, (size_t)pred, (size_t)ss);
		if (!ret[i])
			return (sl_freesplit(ret), NULL);
		++ss;
	}
	return (ret);
}
