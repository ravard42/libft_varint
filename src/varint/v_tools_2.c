/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_tools_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 04:38:00 by ravard            #+#    #+#             */
/*   Updated: 2020/01/22 04:38:25 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int64_t					v_maxbin_pow(t_varint v)
{
	int64_t	j;

	if (is_g_v(0, v))
		return (-1);
	j = V_BIT_LEN - 1;
	while (!(v.x[v.len - 1] >> j & 1))
		j--;
	j += (v.len > 1) ? (v.len - 1) * V_BIT_LEN : 0;
	return (j);
}

t_varint				v_inc(t_varint a)
{
	a = v_add(a, g_v[1]);
	return (a);
}

t_varint				v_dec(t_varint a)
{
	a = v_sub(a, g_v[1]);
	return (a);
}

t_varint				v_abs(t_varint v)
{
	v.sign = 1;
	return (v);
}

/*
** load a varint pseudo random number from /dev/urandom
*/

t_varint				v_rand_n(V_LEN_TYPE len)
{
	V_TYPE			rand_n[len];
	t_varint		n;

	ft_rand(rand_n, len * V_LEN);
	n = v_init(1, rand_n, len);
	return (n);
}
