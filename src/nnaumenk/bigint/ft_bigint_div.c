/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint_div.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 23:52:03 by nnaumenk          #+#    #+#             */
/*   Updated: 2019/02/26 18:57:23 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bigint.h"

static void	ft_get_first_block(t_bigint *block, t_bigint *a, t_bigint *b)
{
	block->size = 1;
	block->value = a->value + a->size - 1;
	while (ft_bigint_smaller(block, b))
	{
		block->size++;
		block->value--;
	}
}

void		ft_bigint_div(t_bigint *in, t_bigint *rm, t_bigint *a, t_bigint *b)
{
	t_bigint		block;
	unsigned char	integer_part;

	*rm = ft_bigint_dup(a);
	ft_get_first_block(&block, rm, b);
	in->value = (unsigned char *)malloc(a->size);
	in->size = 0;
	while (block.value >= rm->value)
	{
		integer_part = 0;
		while (ft_bigint_equ_bigger(&block, b))
		{
			ft_bigint_sub(&block, b);
			++integer_part;
		}
		in->value[in->size++] = integer_part;
		block.size++;
		block.value--;
	}
	ft_memrev(in->value, in->size);
	ft_bigint_normalize(in);
	ft_bigint_normalize(rm);
}
