/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 22:12:53 by nnaumenk          #+#    #+#             */
/*   Updated: 2019/03/16 22:19:55 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BIGINT_H
# define FT_BIGINT_H

# include "libft.h"
# include "ft_bigint_struct.h"

t_bigint	ft_bigint_dup(t_bigint *a);
t_bigint	ft_bigint_dup_value(size_t value, size_t size);
void		ft_bigint_del(t_bigint *a);
void		ft_bigint_print(char *name, t_bigint *a);

int			ft_bigint_isnull(t_bigint *a);
int			ft_bigint_isvalue(t_bigint *a, size_t value);

void		ft_bigint_normalize(t_bigint *a);

int			ft_bigint_equ_bigger(t_bigint *a, t_bigint *b);
int			ft_bigint_bigger(t_bigint *a, t_bigint *b);
int			ft_bigint_smaller(t_bigint *a, t_bigint *b);
int			ft_bigint_equal(t_bigint *a, t_bigint *b);

void		ft_bigint_increment(t_bigint *a);
void		ft_bigint_decrement(t_bigint *a);

void		ft_bigint_shl(t_bigint *a, size_t shift);
void		ft_bigint_shl_overflow(t_bigint *a, size_t shift);
void		ft_bigint_shr(t_bigint *a, size_t shift);

void		ft_bigint_add(t_bigint *a, t_bigint *b);
void		ft_bigint_sub(t_bigint *a, t_bigint *b);

void		ft_bigint_mul(t_bigint *mul, t_bigint *a, t_bigint *b);
void		ft_bigint_div(t_bigint *in, t_bigint *rm, t_bigint *a, t_bigint *b);
void		ft_bigint_div_safe(t_bigint *in, t_bigint *rm, t_bigint *a,
			t_bigint *b);

#endif
