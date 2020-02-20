/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_op_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 06:47:21 by ravard            #+#    #+#             */
/*   Updated: 2020/01/30 06:55:29 by ravard           ###   ########.fr       */
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
** a.sign == b.sign
** msb_id(a + b) <= sup(n, m) + 1
**
** a.sign != b.sign
** msb_id(a + b) <= sup(n, m)
*/

bool			v_add_check(t_varint *v[3])
{
	int64_t	msb[3];

	msb[0] = v_msb_id(v[0]);
	msb[1] = v_msb_id(v[1]);
	msb[2] = (msb[0] >= msb[1]) ? msb[0] : msb[1];
	msb[2] += v[0]->sign == v[1]->sign ? 1 : 0;
	if (1 + msb[2] / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_ADD_OVFL, KNRM))
		return (false);
	return (true);
}

/*
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

/*
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
** v[0] -> dividend
** v[1] -> divisor
**
**	can't overflow in div or mod
**	endeed quotient and modulus are always <= dividend
*/

bool			v_div_check(t_varint *v[3])
{
	if (is_g_v(0, v[1])
		&& ft_dprintf(2, "%s%s%s", KRED, V_DIV_BY_0, KNRM))
		return (false);
	return (true);
}

/*
** with a = v[0]
**      b = v[1]
**      n = v[2]
**
** a^b mod(n) = (a mod(n))^b mod(n)
**
** expmod reduce a to a mod(n) from the entry of the function
**	so for overflow checking we only need to check that n * n don't overflow
*/

bool			v_expmod_check(t_varint *v[3])
{
	int64_t	msb[2];

	if (v[1]->sign == -1
		&& ft_dprintf(2, "%s%s%s", KRED, V_NEG_POW, KNRM))
		return (false);
	if (is_g_v(0, v[2])
		&& ft_dprintf(2, "%s%s%s", KRED, V_DIV_BY_0, KNRM))
		return (false);
	msb[0] = v_msb_id(v[2]);
	msb[1] = msb[0] * 2;
	if (1 + msb[1] / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_EXPMOD_OVFL, KNRM))
		return (false);
	return (true);
}
