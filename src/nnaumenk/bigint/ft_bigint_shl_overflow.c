/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint_shl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 23:52:03 by nnaumenk          #+#    #+#             */
/*   Updated: 2019/02/20 20:29:16 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bigint.h"

static void	ft_copy_1byte(void *memptr, size_t shift, size_t n)
{
	size_t			i;
	unsigned char	*src8;
	unsigned char	*dst8;

	if (shift == 0)
		return ;
	src8 = (unsigned char *)memptr + n - shift;
	dst8 = (unsigned char *)memptr + n;
	i = shift - 1;
	while (++i < n)
		*--dst8 = *--src8;
	ft_bzero(memptr, shift);
}

static void	ft_shift_1byte(void *memptr, size_t shift, size_t n)
{
	unsigned char	overflow;
	unsigned char	buf;
	unsigned char	*mem8;

	if (shift == 0)
		return ;
	overflow = 0;
	mem8 = (unsigned char *)memptr;
	while (n--)
	{
		buf = (*mem8 >> (8 - shift));
		*mem8 = (*mem8 << shift) | overflow;
		overflow = buf;
		mem8++;
	}
}

void		ft_bigint_shl_overflow(t_bigint *a, size_t shift)
{
	t_bigint	new;
	const char	overflow[] = {0x0, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE};

	if (shift >= 8)
	{
		new.size = a->size + (shift + 7) / 8;
		new.value = (unsigned char *)malloc(new.size);
		ft_memcpy(new.value, a->value, a->size);
		ft_bzero(new.value + a->size, new.size - a->size);
		ft_bigint_del(a);
		*a = new;
	}
	else if (a->value[a->size - 1] & overflow[shift])
	{
		new.size = a->size + 1;
		new.value = (unsigned char *)malloc(new.size);
		ft_memcpy(new.value, a->value, a->size);
		ft_bzero(new.value + a->size, 1);
		ft_bigint_del(a);
		*a = new;
	}
	ft_copy_1byte(a->value, shift / 8, a->size);
	ft_shift_1byte(a->value, shift % 8, a->size);
}
