/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cslice.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 11:28:14 by lmilando          #+#    #+#             */
/*   Updated: 2026/05/06 15:29:17 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSLICE_H
# define CSLICE_H
#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_sl {
	char*	str; /* owned buffer; str[len] is guaranteed '\0'*/
	size_t	len; /* number of meaningful bytes, excluding sentinel */
	size_t	cap; /* number of usable bytes excluding sentinel byte; alloc_size = cap + 1*/
}	t_sl;

/*Creation and destruction*/
t_sl*	sl_new(size_t cap);
bool	sl_resize_cap(t_sl *s, size_t cap);
void  	sl_free(t_sl *b);
void	sl_free_array(t_sl **arr);

/*Creation from existing data*/
t_sl*	sl_clone_new(t_sl const *b);
t_sl*	sl_sub_new(t_sl const *b, size_t start, size_t maxlen);
t_sl*	sl_concat_new(t_sl const *a, t_sl const *b);
t_sl*	sl_repeat_new(t_sl const *a, size_t n);

/*Mutation*/
size_t	sl_copy(t_sl *dest, t_sl const *src, size_t maxlen);

/* Cut */
ssize_t sl_cut(t_sl const *b, char sep, t_sl **before, t_sl **after);
ssize_t sl_cut_sl(t_sl const *b, t_sl const *sep, t_sl **before, t_sl **after);


/*Search and compare*/
ssize_t sl_indexof(t_sl const *b, char c, size_t start, size_t maxlen);
ssize_t	sl_indexof_sl(t_sl const *haystack, t_sl const *needle);
ssize_t sl_count(t_sl const *b, char c, size_t start, size_t maxlen);
ssize_t sl_lastindexof(t_sl const *b, char c, size_t minindex);
int		sl_compare(t_sl const *a, t_sl const *b);
bool	sl_contains_sl(t_sl const *a, t_sl const *b);
bool	sl_equal(t_sl const *a, t_sl const *b);
bool	sl_hasprefix(t_sl const *a, t_sl const *b);
bool	sl_hassuffix(t_sl const *a, t_sl const *b);

/*Split and Join */
t_sl**	sl_split(t_sl const *b, t_sl const *sep, size_t start, size_t maxlen);
t_sl*	sl_join(t_sl const **s, t_sl const *sep);

#endif
