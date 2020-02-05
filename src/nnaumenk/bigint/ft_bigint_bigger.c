/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint_bigger.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 23:52:03 by nnaumenk          #+#    #+#             */
/*   Updated: 2019/02/20 20:28:44 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bigint.h"

static int	ft_iszero(void *memptr, size_t num)
{
	size_t			i;
	size_t			*str64;
	unsigned char	*str8;

	str64 = (size_t *)memptr;
	i = num / sizeof(size_t);
	while (i--)
		if (*str64++ != 0)
			return (0);
	str8 = (unsigned char *)str64;
	i = num % sizeof(size_t);
	while (i--)
		if (*str8++ != 0)
			return (0);
	return (1);
}

static int	ft_mem_bigger(unsigned char *val1, unsigned char *val2, size_t n)
{
	size_t			*val64_1;
	size_t			*val64_2;
	size_t			i;

	val64_1 = (size_t *)(val1 + n);
	val64_2 = (size_t *)(val2 + n);
	i = n / sizeof(size_t);
	while (i--)
	{
		if (*--val64_1 > *--val64_2)
			return (1);
		if (*val64_1 < *val64_2)
			return (0);
	}
	val1 = (unsigned char *)val64_1;
	val2 = (unsigned char *)val64_2;
	i = n % sizeof(size_t);
	while (i--)
	{
		if (*--val1 > *--val2)
			return (1);
		if (*val1 < *val2)
			return (0);
	}
	return (0);
}

int			ft_bigint_bigger(t_bigint *a, t_bigint *b)
{
	if (a->size == b->size)
		return (ft_mem_bigger(a->value, b->value, a->size));
	if (a->size < b->size)
	{
		if (ft_iszero(b->value + a->size, b->size - a->size))
			return (ft_mem_bigger(a->value, b->value, a->size));
		return (0);
	}
	if (a->size > b->size)
	{
		if (ft_iszero(a->value + b->size, a->size - b->size))
			return (ft_mem_bigger(a->value, b->value, b->size));
		return (1);
	}
	return (0);
}
