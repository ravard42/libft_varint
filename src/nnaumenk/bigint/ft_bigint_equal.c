/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint_equal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 23:52:03 by nnaumenk          #+#    #+#             */
/*   Updated: 2019/02/20 20:28:59 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bigint.h"

static int	ft_iszero(void *memptr, size_t num)
{
	size_t			i;
	size_t			*mem64;
	unsigned char	*mem8;

	mem64 = (size_t *)memptr;
	i = num / sizeof(size_t);
	while (i--)
		if (*mem64++ != 0)
			return (0);
	mem8 = (unsigned char *)mem64;
	i = num % sizeof(size_t);
	while (i--)
		if (*mem8++ != 0)
			return (0);
	return (1);
}

static int	ft_mem_equal(void *mem1, void *mem2, size_t n)
{
	size_t			i;
	size_t			*mem1_64;
	size_t			*mem2_64;
	unsigned char	*mem1_8;
	unsigned char	*mem2_8;

	mem1_64 = (size_t *)mem1;
	mem2_64 = (size_t *)mem2;
	i = n / sizeof(size_t);
	while (i--)
		if (*mem1_64++ != *mem2_64++)
			return (0);
	mem1_8 = (unsigned char *)mem1_64;
	mem2_8 = (unsigned char *)mem2_64;
	i = n % sizeof(size_t);
	while (i--)
		if (*mem1_8++ != *mem2_8++)
			return (0);
	return (1);
}

int			ft_bigint_equal(t_bigint *a, t_bigint *b)
{
	if (a->size == b->size)
		return (ft_mem_equal(a->value, b->value, a->size));
	if (a->size < b->size)
	{
		if (ft_iszero(b->value + a->size, b->size - a->size))
			return (ft_mem_equal(a->value, b->value, a->size));
		return (0);
	}
	if (a->size > b->size)
	{
		if (ft_iszero(a->value + b->size, a->size - b->size))
			return (ft_mem_equal(a->value, b->value, b->size));
		return (0);
	}
	return (0);
}
