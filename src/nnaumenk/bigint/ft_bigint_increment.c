/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decrement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 23:52:03 by nnaumenk          #+#    #+#             */
/*   Updated: 2018/08/19 03:49:00 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bigint.h"

static void	ft_increment_8byte(void **memptr, size_t i, char *overflow)
{
	size_t		*mem64;
	size_t		sum64;

	mem64 = (size_t *)*memptr;
	while (i--)
	{
		sum64 = *mem64 + *overflow;
		if (sum64 < *mem64)
		{
			*overflow = 1;
			*mem64 = sum64;
		}
		else
		{
			*overflow = 0;
			*mem64 = sum64;
			break ;
		}
		mem64++;
	}
	*memptr = mem64;
}

static void	ft_increment_1byte(void **memptr, size_t i, char *overflow)
{
	unsigned char	*mem8;
	unsigned char	sum8;

	if (*overflow == 0)
		return ;
	mem8 = (unsigned char *)*memptr;
	while (i--)
	{
		sum8 = *mem8 + *overflow;
		if (sum8 < *mem8)
		{
			*overflow = 1;
			*mem8 = sum8;
		}
		else
		{
			*overflow = 0;
			*mem8 = sum8;
			break ;
		}
		mem8++;
	}
	*memptr = mem8;
}

void		ft_check_overflow(t_bigint *a, char overflow)
{
	t_bigint	new;

	if (overflow)
	{
		new.size = a->size + 1;
		new.value = (unsigned char *)malloc(new.size);
		ft_memcpy(new.value, a->value, a->size);
		new.value[new.size - 1] = 1;
		ft_bigint_del(a);
		*a = new;
	}
}

void		ft_bigint_increment(t_bigint *a)
{
	void		*memptr;
	char		overflow;

	overflow = 1;
	memptr = (void *)a->value;
	ft_increment_8byte(&memptr, a->size / sizeof(size_t), &overflow);
	ft_increment_1byte(&memptr, a->size % sizeof(size_t), &overflow);
	ft_check_overflow(a, overflow);
}
