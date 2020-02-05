/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint_mul.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 23:52:03 by nnaumenk          #+#    #+#             */
/*   Updated: 2019/03/17 00:24:06 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bigint.h"

static void	ft_mul_4byte(
		unsigned int *mul32, unsigned int *a32, unsigned int *b32, size_t n)
{
	size_t			i;
	size_t			product;
	size_t			overflow;
	unsigned int	buf;

	overflow = 0;
	i = n / sizeof(unsigned int);
	while (i--)
	{
		product = (size_t)(*a32) * (size_t)(*b32) + overflow + *mul32;
		overflow = product / 0x100000000;
		*mul32 = product - overflow * 0x100000000;
		mul32++;
		b32++;
	}
	i = n % sizeof(unsigned int);
	buf = 0;
	ft_memcpy(&buf, b32, i);
	product = (size_t)(*a32) * (size_t)(buf) + overflow + *mul32;
	overflow = product / 0x100000000;
	*mul32 = product - overflow * 0x100000000;
	*++mul32 = overflow;
}

static void	ft_mul_algor(t_bigint *mul, t_bigint *a, t_bigint *b)
{
	size_t			i;
	unsigned int	*mul32;
	unsigned int	*a32;
	unsigned int	*b32;
	unsigned int	buf;

	mul32 = (unsigned int *)mul->value;
	a32 = (unsigned int *)a->value;
	b32 = (unsigned int *)b->value;
	i = a->size / sizeof(unsigned int);
	while (i--)
	{
		ft_mul_4byte(mul32, a32, b32, b->size);
		mul32++;
		a32++;
	}
	if ((i = a->size % sizeof(unsigned int)) == 0)
		return ;
	buf = 0;
	ft_memcpy(&buf, a32, i);
	ft_mul_4byte(mul32, &buf, b32, b->size);
}

void		ft_bigint_mul(t_bigint *mul, t_bigint *a, t_bigint *b)
{
	mul->size = a->size + b->size + 4;
	mul->value = (unsigned char *)malloc(mul->size);
	ft_bzero(mul->value, mul->size);
	ft_mul_algor(mul, a, b);
	ft_bigint_normalize(mul);
}
