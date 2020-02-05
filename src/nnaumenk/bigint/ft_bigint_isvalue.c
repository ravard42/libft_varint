/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint_isvalue.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 23:52:03 by nnaumenk          #+#    #+#             */
/*   Updated: 2019/02/27 18:39:59 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bigint.h"

static int	ft_bigint_big_size(t_bigint *a, size_t value)
{
	size_t	value2;

	value2 = 0;
	ft_memcpy(&value2, a->value, 8);
	if (value2 == value)
	{
		a->value += 8;
		a->size -= 8;
		if (ft_bigint_isnull(a))
		{
			a->value -= 8;
			a->size += 8;
			return (1);
		}
		a->value -= 8;
		a->size += 8;
	}
	return (0);
}

static int	ft_bigint_small_size(t_bigint *a, size_t value)
{
	size_t	value2;

	value2 = 0;
	ft_memcpy(&value2, a->value, a->size);
	if (value2 == value)
		return (1);
	return (0);
}

int			ft_bigint_isvalue(t_bigint *a, size_t value)
{
	if (a->size <= 8)
	{
		if (ft_bigint_small_size(a, value))
			return (1);
	}
	else
	{
		if (ft_bigint_big_size(a, value))
			return (1);
	}
	return (0);
}
