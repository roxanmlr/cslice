/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cslice.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 11:28:14 by lmilando          #+#    #+#             */
/*   Updated: 2026/04/24 16:58:25 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSLICE_H
# define CSLICE_H
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_sl {
	char *str;
	size_t siz;
	size_t cap;
}	t_sl;

t_sl *sl_alloc(size_t siz);
void  sl_free(t_sl *b);
t_sl *sl_clone(t_sl *b);
t_sl *sl_sub(t_sl *b, size_t start, size_t maxlen);
t_sl *sl_copy(t_sl *dest, t_sl *src, size_t maxsiz);
ssize_t sl_indexof(t_sl *b, char c, size_t start, size_t maxlen);
ssize_t sl_cut(t_sl *b, char c, t_sl **before, t_sl **after);
t_sl **sl_split(t_sl *b, char c, size_t start, size_t maxlen);

#endif
