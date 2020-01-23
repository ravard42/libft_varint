/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_check.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 04:39:02 by ravard            #+#    #+#             */
/*   Updated: 2020/01/23 01:56:02 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool				v_check_add(t_varint a, t_varint b)
{
	int64_t	mb_pow[2];
	int64_t	sup;

	mb_pow[0] = v_maxbin_pow(a);
	mb_pow[1] = v_maxbin_pow(b);
	sup = (mb_pow[0] >= mb_pow[1]) ? mb_pow[0] : mb_pow[1];
	if (1 + (sup + 1) / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_ADD_OVFL, KNRM))
		return (false);
	return (true);
}

static bool				v_check_mul(t_varint a, t_varint b)
{
	int64_t	mb_pow[2];

	mb_pow[0] = v_maxbin_pow(a);
	mb_pow[1] = v_maxbin_pow(b);
	if (1 + (mb_pow[0] + 1 + mb_pow[1] + 1) / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_MUL_OVFL, KNRM))
		return (false);
	return (true);
}

static bool				v_check_exp(t_varint v, t_varint e)
{
	int64_t		mb_pow[2];
	uint64_t	e64;
	int8_t		i;

	if (e.sign == -1
		&& ft_dprintf(2, "%s%s%s", KRED, V_NEG_POW, KNRM))
		return (false);
	if (e.len * sizeof(V_TYPE) > 8
		&& ft_dprintf(2, "%s%s%s", KRED, V_EXP_LIM, KNRM))
		return (false);
	e64 = 0;
	i = -1;
	while (++i < e.len)
		e64 += (uint64_t)e.x[i] << V_BIT_LEN * i;
	mb_pow[0] = v_maxbin_pow(v);
	mb_pow[1] = v_maxbin_pow(e);
	if (1 + ((mb_pow[0] + 1) * e64) / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_EXP_OVFL, KNRM))
		return (false);
	return (true);
}

static bool				v_check_div(t_varint dividend, t_varint divisor)
{
	int64_t	mb_pow[2];
	int64_t	sup;

	if (is_g_v(0, divisor)
		&& ft_dprintf(2, "%s%s%s", KRED, V_DIV_BY_0, KNRM))
		return (false);
	mb_pow[0] = v_maxbin_pow(dividend);
	mb_pow[1] = v_maxbin_pow(divisor);
	sup = (mb_pow[0] >= mb_pow[1]) ? mb_pow[0] : mb_pow[1];
	if (1 + (sup + 2) / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_DIV_OVFL, KNRM))
		return (false);
	return (true);
}

static bool				v_check_expmod(t_varint v, t_varint e, t_varint mod)
{
	int64_t	mb_pow[2];
	int64_t	sup;

	if (e.sign == -1
		&& ft_dprintf(2, "%s%s%s", KRED, V_NEG_POW, KNRM))
		return (false);
	if (is_g_v(0, mod)
		&& ft_dprintf(2, "%s%s%s", KRED, V_DIV_BY_0, KNRM))
		return (false);
	mb_pow[0] = 2 * (v_maxbin_pow(v) + 1);
	mb_pow[1] = 2 * (v_maxbin_pow(mod) + 1);
	sup = (mb_pow[0] > mb_pow[1]) ? mb_pow[0] : mb_pow[1];
	if (1 + (sup + 6) / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_EXPMOD_OVFL, KNRM))
		return (false);
	return (true);
}


static bool				v_len_check(t_varint v)
{
	V_LEN_TYPE		tmp;

	if ((v.len <= 0 || v.len > V_MAX_LEN)
		&& ft_dprintf(2, "%s%s%s", KRED, V_BAD_LEN, KNRM))
		return (false);
	tmp = v.len;
	v_len(&v);
	if (v.len != tmp)
		return (false);
	return (true);
}

/*
**	v_check verify that  a, b and m are valid varint variables:
**		1] sign == -1 or sign == 1
**		2] their len are consistent
**
**	morevover if op make sense:
**	v_check estimates if the resultat of op will not overflow V_MAX_LEN
**	and verify that the operation is well defined (ex: divison by 0)
*/

bool					v_check(t_varint a, t_varint b, t_varint m, char *op)
{
	if (is_g_v(3, a) || is_g_v(3, b) || is_g_v(3, m))
		return (false);
	if (!v_len_check(a) || !v_len_check(b) || !v_len_check(m))
		return (false);
	if (op && !ft_strcmp("add", op))
		return (v_check_add(a, b));
	if (op && !ft_strcmp("mul", op))
		return (v_check_mul(a, b));
	if (op && !ft_strcmp("exp", op))
		return (v_check_exp(a, b));
	if (op && !ft_strcmp("div", op))
		return (v_check_div(a, b));
	if (op && !ft_strcmp("expmod", op))
		return (v_check_expmod(a, b, m));
	return (true);
}
