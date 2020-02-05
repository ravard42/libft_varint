/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:45:35 by nnaumenk          #+#    #+#             */
/*   Updated: 2019/03/15 09:54:06 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_is_even(t_bigint *r, t_bigint *mod)
{
	t_bigint	mul;
	t_bigint	integer;
	t_bigint	remainder;

	ft_bigint_mul(&mul, r, r);
	ft_bigint_normalize(&mul);
	ft_bigint_del(r);
	ft_bigint_div(&integer, &remainder, &mul, mod);
	*r = remainder;
	ft_bigint_del(&integer);
	ft_bigint_del(&mul);
}

static void	ft_is_odd(t_bigint *r, t_bigint *num, t_bigint *mod)
{
	t_bigint	mul;
	t_bigint	integer;
	t_bigint	remainder;

	ft_bigint_div(&integer, &remainder, num, mod);
	ft_bigint_mul(&mul, &remainder, r);
	ft_bigint_del(&integer);
	ft_bigint_del(&remainder);
	ft_bigint_del(r);
	ft_bigint_div(&integer, &remainder, &mul, mod);
	ft_bigint_del(&integer);
	ft_bigint_del(&mul);
	*r = remainder;
}

static void	ft_algor(t_bigint *r, t_bigint *num, t_bigint *pow, t_bigint *mod)
{
	if (ft_bigint_isnull(pow))
	{
		r->size = 1;
		r->value = (unsigned char *)malloc(1);
		r->value[0] = 1;
		return ;
	}
	else if ((pow->value[0] & 0x01) == 0)
	{
		ft_bigint_shr(pow, 1);
		ft_algor(r, num, pow, mod);
		ft_is_even(r, mod);
		return ;
	}
	else
	{
		ft_bigint_decrement(pow);
		ft_algor(r, num, pow, mod);
		ft_is_odd(r, num, mod);
		return ;
	}
}

void		ft_pow_mod(t_bigint *r, t_bigint *num, t_bigint *pow, t_bigint *mod)
{
	t_bigint	buf;

	buf = ft_bigint_dup(pow);
	ft_algor(r, num, pow, mod);
	ft_bigint_del(pow);
	*pow = buf;
}
