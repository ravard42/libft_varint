/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_check.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 04:39:02 by ravard            #+#    #+#             */
/*   Updated: 2020/01/25 02:31:21 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** theoretical v_'op'_ovfl implementation (waiting that ASan bug is fixed)
**
*/

static bool				v_add_ovfl(t_varint a, t_varint b)
{
	int64_t	mb_pow[3];

	mb_pow[0] = v_maxbin_pow(a);
	mb_pow[1] = v_maxbin_pow(b);
	mb_pow[2] = (mb_pow[0] >= mb_pow[1]) ? mb_pow[0] : mb_pow[1];
	mb_pow[2] += a.sign == b.sign ? 1 : 0;
	for (int i = 0; i < 3; i++)
		ft_printf("mb_pow[%d] = %ld\n", i, mb_pow[i]);
	if (1 + (mb_pow[2]) / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_ADD_OVFL, KNRM))
		return (false);
	return (true);
}

static bool				v_mul_ovfl(t_varint a, t_varint b)
{
	int64_t	mb_pow[3];

	mb_pow[0] = v_maxbin_pow(a);
	mb_pow[1] = v_maxbin_pow(b);
	mb_pow[2] = mb_pow[0] + mb_pow[1];
//	for (int i = 0; i < 3; i++)
//		ft_printf("mb_pow[%d] = %ld\n", i, mb_pow[i]);
	if (1 + (mb_pow[2]) / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_MUL_OVFL, KNRM))
		return (false);
	return (true);
}

static bool				v_exp_ovfl(t_varint v, t_varint e)
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

static bool				v_div_ovfl(t_varint dividend, t_varint divisor)
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

static bool				v_expmod_ovfl(t_varint v, t_varint e, t_varint mod)
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
	if (v.len != tmp && ft_dprintf(2, "%s%s%s\n", KRED, V_COR_LEN, KNRM))
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
	bool ret;

	ft_printf("%sIN v_check_%s%s\n", KGRN, op, KNRM);
	if (is_g_v(3, a) || is_g_v(3, b) || is_g_v(3, m))
		ret = false;
	else if (!v_len_check(a) || !v_len_check(b) || !v_len_check(m))
		ret = false;
	else if (op && !ft_strcmp("add", op))
		ret = v_add_ovfl(a, b);
	else if (op && !ft_strcmp("mul", op))
		ret = v_mul_ovfl(a, b);
	else if (0 && op && !ft_strcmp("exp", op))
		ret = v_exp_ovfl(a, b);
	else if (0 && op && !ft_strcmp("div", op))
		ret = v_div_ovfl(a, b);
	else if (0 && op && (!ft_strcmp("expmod", op)
				|| !ft_strcmp("crt", op)))
		ret = v_expmod_ovfl(a, b, m);
	else
		ret = true;
	ft_printf("%sOUT v_check_%s%s\n", KYEL, op, KNRM);
	return (ret);
}
