/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint_div_safe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 23:52:03 by nnaumenk          #+#    #+#             */
/*   Updated: 2019/03/16 22:29:11 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bigint.h"

void	ft_bigint_div_safe(t_bigint *in, t_bigint *rm, t_bigint *a, t_bigint *b)
{
	if (ft_bigint_isvalue(b, 0))
	{
		in->size = 1;
		in->value = (unsigned char *)malloc(1);
		in->value[0] = 0;
		rm->size = 1;
		rm->value = (unsigned char *)malloc(1);
		rm->value[0] = 0;
		return ;
	}
	if (ft_bigint_smaller(a, b))
	{
		in->size = 1;
		in->value = (unsigned char *)malloc(1);
		in->value[0] = 0;
		*rm = ft_bigint_dup(a);
		return ;
	}
	ft_bigint_div(in, rm, a, b);
}
