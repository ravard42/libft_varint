/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 04:22:35 by ravard            #+#    #+#             */
/*   Updated: 2020/01/30 07:06:34 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool			is_g_v(int8_t i, t_varint *v)
{
	if (i == 3)
	{
		if (v->sign != -1 && v->sign != 1
			&& ft_dprintf(2, "%s%s%s", KRED, V_ERR, KNRM))
			return (true);
		return (false);
	}
	if (v->len == 1)
	{
		if ((v->sign == 1 || v->sign == -1)
			&& v->x[0] == (uint8_t)i && (v->sign = 1))
			return (true);
		if (v->sign == 1 && v->len == 1 && v->x[0] == (uint8_t)i)
			return (true);
	}
	return (false);
}

void			v_len(t_varint *v)
{
	int16_t		i;

	i = V_MAX_LEN;
	while (--i > 0)
		if (v->x[i])
			break ;
	v->len = i + 1;
}

/*
** load len uint8_t from uint8_t *src in a varint variable n and return it
*/

t_varint		v_init(char sign, uint8_t *src, int16_t len)
{
	t_varint		v;
	int16_t		i;

	if (sign != -1 && sign != 1
		&& ft_dprintf(2, "%s%s%s", KRED, V_BAD_SIGN, KNRM))
		return (g_v[3]);
	if ((len <= 0 || len > V_MAX_LEN)
		&& ft_dprintf(2, "%s%s%s", KRED, V_BAD_LEN, KNRM))
		return (g_v[3]);
	v = g_v[0];
	v.sign = sign;
	i = -1;
	while (++i < len)
		v.x[i] = src[i];
	v_len(&v);
	is_g_v(0, &v);
	return (v);
}

void			v_sort(t_varint *a, t_varint *b, bool check)
{
	t_varint	tmp;

	if (check && !v_check(a, b, NULL, "sort"))
		return ;
	if (v_cmp(a, "-lt", b, false))
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

void			v_print(char *name, t_varint *v)
{
	int16_t		i;
	int8_t		j;

	if (!v_check(v, NULL, NULL, "print"))
		return ;
	ft_printf("%s|%hhd|%hd:\n", name, v->sign, v->len);
	i = v->len - 1;
	while (i >= 0)
	{
		ft_printf("    ");
		j = -1;
		while (++j < 15 && i - j >= 0)
		{
			ft_printf("%02x", v->x[i - j]);
			if (i - (j + 1) >= 0)
				ft_printf(":");
		}
		i -= 15;	
		ft_printf("\n");
	}
}
