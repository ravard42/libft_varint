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

/*
** binary decomposition
** a = 1 * 2^n +  a_n-1 * 2^(n - 1) + ... + 2^0 * a_0
** b = 1 * 2^m +  b_m-1 * 2^(m - 1) + ... + 2^0 * b_0
**
** msb_id(a) = (a != 0) ? n : -1
** msb_id(b) = (b != 0) ? m : -1
*/

/*
**	V_MUL OVFL NOTE
**
** msb_id(a * b) <= n + m
*/

bool			v_mul_check(t_varint *v[3])
{
	int64_t	msb[3];

	msb[0] = v_msb_id(v[0]);
	msb[1] = v_msb_id(v[1]);
	msb[2] = msb[0] + msb[1];
	if (1 + msb[2] / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_MUL_OVFL, KNRM))
		return (false);
	return (true);
}


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
**	V_EXP OVFL NOTE
**
**  v[0] -> v
**  v[1] -> e
**
**	NB : (2^a)^b = 2^(a * b)
**
**		v < 2^(msb_id(v) + 1)
**	=>	v^e < 2^((msb_id(v) + 1) * e)
**
**	NB:stack-overflow occured on mac-mini at V_MAX_LEN ~ 300000 (uint8_t)
**		300000*8 = 2100000 (~2^21 bits)
**
**	if e >= 2^16 an error is raised
** explanation:
**	if we set v = e = 2^16
**	(2^16)^(2^16) = 2^(16 * 2^16) = 2^(2^4 * 2^16) = 2^(2^20)
**	it's almost the mac-mini stack limit of 2^21 bits
*/

bool			v_exp_check(t_varint *v[3])
{
	int8_t		i;
	uint64_t	e64;
	int64_t		msb[2];

	if (v[1]->sign == -1
		&& ft_dprintf(2, "%s%s%s", KRED, V_NEG_POW, KNRM))
		return (false);
	if (v[1]->len > 2
		&& ft_dprintf(2, "%s%s%s", KRED, V_EXP_LIM, KNRM))
		return (false);
	e64 = 0;
	i = -1;
	while (++i < v[1]->len)
		e64 += (uint64_t)v[1]->x[i] << V_BIT_LEN * i;
	msb[0] = v_msb_id(v[0]);
	msb[1] = (msb[0] + 1) * e64;
	if (1 + msb[1] / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_EXP_OVFL, KNRM))
		return (false);
	return (true);
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
