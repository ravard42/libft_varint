/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_mul_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 03:59:40 by ravard            #+#    #+#             */
/*   Updated: 2020/01/30 06:44:51 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			process(t_varint *ret, uint32_t *u32[2], int16_t len[2])
{
	int16_t		i;
	int16_t		j;
	int16_t		k;
	uint64_t		*u64;
	uint64_t		carry;

	j = -1;
	while (++j < len[1])
	{
		i = -1;
		while (++i < len[0])
		{
			u64 = (uint64_t *)((uint32_t *)ret->x + i + j);
			carry = *u64;
			*u64 += (uint64_t)(*(u32[0] + i)) * (uint64_t)(*(u32[1] + j));
			carry = (carry > *u64) ? 1 : 0;
			if (carry && !(k = 0))
				while ((*((uint8_t *)(u64 + 1) + k) += carry) == 0)
					++k;
		}
	}
	v_len(ret, (len[0] + len[1]) * 4);
}

t_varint			v_mul(t_varint a, t_varint b, bool check)
{
	uint32_t		*u32[2];
	int16_t		len[2];
	t_varint		ret;

	if (check && !v_check(&a, &b, NULL, "mul"))
		return (g_v[3]);
	u32[0] = (uint32_t *)a.x;
	u32[1] = (uint32_t *)b.x;
	len[0] = a.len / (ssize_t)sizeof(uint32_t);
	len[0] += (a.len % (ssize_t)sizeof(uint32_t)) ? 1 : 0;
	len[1] = b.len / (ssize_t)sizeof(uint32_t);
	len[1] += (b.len % (ssize_t)sizeof(uint32_t)) ? 1 : 0;
	ret = g_v[0];
	ret.sign = a.sign * b.sign;
	process(&ret, u32, len);
	return (ret);
}

/*
** i : varint index
** j : bit index
*/

t_varint			v_exp(t_varint v, t_varint e)
{
	int16_t					i;
	int8_t						j;
	t_varint					ret;

	if (!v_check(&v, &e, NULL, "exp"))
		return (g_v[3]);
	if (is_g_v(0, &e))
		return (g_v[1]);
	j = V_BIT_LEN - 1;
	while (!(e.x[e.len - 1] >> j & 1))
		j--;
	ret = v;
	i = e.len;
	while (--i >= 0)
	{
		j = (i == e.len - 1) ? j : V_BIT_LEN;
		while (--j >= 0)
		{
			ret = v_mul(ret, ret, false);
			if (e.x[i] >> j & 1)
				ret = v_mul(ret, v, false);
		}
	}
	return (ret);
}
