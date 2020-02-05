/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 23:52:03 by nnaumenk          #+#    #+#             */
/*   Updated: 2019/03/16 22:11:52 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bigint.h"

static void	ft_check_size(t_bigint *a, t_bigint *b)
{
	void	*newptr;

	if (b->size > a->size)
	{
		newptr = (void *)malloc(b->size + 1);
		ft_memcpy(newptr, a->value, a->size);
		ft_bzero(newptr + a->size, b->size + 1 - a->size);
		free(a->value);
		a->value = (unsigned char *)newptr;
		a->size = b->size + 1;
	}
}

static void	ft_overflow(t_bigint *a, t_bigint *b)
{
	unsigned char	*newptr;
	t_bigint		c;

	if (a->size == b->size)
	{
		newptr = (unsigned char *)malloc(a->size + 1);
		ft_memcpy(newptr, a->value, a->size);
		newptr[a->size++] = 1;
		free(a->value);
		a->value = newptr;
		return ;
	}
	c.value = a->value + b->size;
	c.size = a->size - b->size;
	ft_bigint_increment(&c);
}

static void	ft_add_8byte(void **mem1, void **mem2, size_t i, char *overflow)
{
	size_t			*val1;
	size_t			*val2;
	size_t			sum64;

	val1 = (size_t *)*mem1;
	val2 = (size_t *)*mem2;
	while (i--)
	{
		sum64 = *val1 + *val2 + *overflow;
		if (sum64 < *val1)
			*overflow = 1;
		else if (sum64 == *val1 && *overflow)
			*overflow = 1;
		else
			*overflow = 0;
		*val1 = sum64;
		val1++;
		val2++;
	}
	*mem1 = val1;
	*mem2 = val2;
}

static void	ft_add_1byte(void **mem1, void **mem2, size_t i, char *overflow)
{
	unsigned char	*val1;
	unsigned char	*val2;
	unsigned char	sum8;

	val1 = (unsigned char *)*mem1;
	val2 = (unsigned char *)*mem2;
	while (i--)
	{
		sum8 = *val1 + *val2 + *overflow;
		if (sum8 < *val1)
			*overflow = 1;
		else if (sum8 == *val1 && *overflow)
			*overflow = 1;
		else
			*overflow = 0;
		*val1 = sum8;
		val1++;
		val2++;
	}
	*mem1 = val1;
	*mem2 = val2;
}

void		ft_bigint_add(t_bigint *a, t_bigint *b)
{
	void			*val1;
	void			*val2;
	char			overflow;

	ft_check_size(a, b);
	val1 = a->value;
	val2 = b->value;
	overflow = 0;
	ft_add_8byte(&val1, &val2, b->size / sizeof(size_t), &overflow);
	ft_add_1byte(&val1, &val2, b->size % sizeof(size_t), &overflow);
	if (overflow)
		ft_overflow(a, b);
}
