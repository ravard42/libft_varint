/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_add_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 03:57:53 by ravard            #+#    #+#             */
/*   Updated: 2020/01/25 02:23:05 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_varint		v_add_pos(t_varint a, t_varint b)
{
	uint64_t		*u64[2];
	int16_t		len;
	int16_t		i;
	uint64_t		tmp;
	uint8_t		carry;
	
	u64[0] = (uint64_t *)a.x;
	u64[1] = (uint64_t *)b.x;
	len = a.len / (ssize_t)sizeof(uint64_t);
	len += (a.len % (ssize_t)sizeof(uint64_t)) ? 1 : 0;
	carry = 0;
	i = -1;
	while (++i < len)
	{
		tmp = *u64[0];
		*u64[0] += *u64[1] + carry;
		carry = (tmp > *u64[0]) ? 1 : 0;
		u64[0]++;
		u64[1]++;
	}
	*u64[0] += carry;
	v_len(&a, 8 * len + carry);
	return (a);
}

/*
** a >= b >= 0 (cf v_sort in v_add)
*/

t_varint				v_sub_pos(t_varint a, t_varint b)
{
	uint64_t		*u64[2];
	int16_t		len;
	int16_t		i;
	uint8_t		carry[2];

	u64[0] = (uint64_t *)a.x;
	u64[1] = (uint64_t *)b.x;
	len = a.len / (ssize_t)sizeof(uint64_t);
	len += (a.len % (ssize_t)sizeof(uint64_t)) ? 1 : 0;
	carry[0] = 0;
	i = -1;
	while (++i < len)
	{
		carry[1] = (*u64[0] >= *u64[1] + carry[0]) ? 0 : 1;
		*u64[0] -= *u64[1] + carry[0];
		carry[0] = carry[1];
		u64[0]++;
		u64[1]++;
	}
	v_len(&a, len * 8);
	return (a);
}

/*
** note that v_sort here is in absolute mode (cf v_tools.c)
*/

t_varint			v_add(t_varint a, t_varint b, bool check)
{
	int8_t		sign[2];

	if (check && !v_check(&a, &b, NULL, "add"))
		return (g_v[3]);
	v_sort(&a, &b, sign, false);
	if (sign[0] == sign[1])
		a = v_add_pos(a, b);
	else
		a = v_sub_pos(a, b);
	a.sign = sign[0];
	return (a);
}

t_varint			v_sub(t_varint a, t_varint b, bool check)
{
	int8_t		sign[2];

	b.sign *= -1;
	if (check && !v_check(&a, &b, NULL, "add"))
		return (g_v[3]);
	v_sort(&a, &b, sign, false);
	if (sign[0] == sign[1])
		a = v_add_pos(a, b);
	else
		a = v_sub_pos(a, b);
	a.sign = sign[0];
	return (a);
}
