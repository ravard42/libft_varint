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
**		     a|b   c|d
**            x  *  y
**
**	|sup = a * c||inf = b * d|
**	     |mid[0] = a * d|
**	     |mid[1] = b * c|
**
**	|----upper------lower----|
*/

static uint8_t		upper(uint8_t x, uint8_t y)
{
	uint8_t			abcd[4];
	uint8_t			sup;
	uint8_t			mid[2];
	uint8_t			inf;
	uint8_t			to_upper[2];

	abcd[0] = x >> V_BIT_LEN / 2;
	abcd[1] = x & V_MID_INF;
	abcd[2] = y >> V_BIT_LEN / 2;
	abcd[3] = y & V_MID_INF;
	sup = abcd[0] * abcd[2];
	mid[0] = abcd[0] * abcd[3];
	mid[1] = abcd[1] * abcd[2];
	inf = abcd[1] * abcd[3];
	to_upper[0] = (mid[0] >> V_BIT_LEN / 2)
		+ (mid[1] >> V_BIT_LEN / 2);
	to_upper[1] = ((mid[0] & V_MID_INF) + (mid[1] & V_MID_INF)
			+ (inf >> V_BIT_LEN / 2)) >> V_BIT_LEN / 2;
	return (sup + to_upper[0] + to_upper[1]);
}

///*
//** i : a index
//** j : b index <-> p_mul id <-> coincide with initial number of right 0 in p_mul
//*/
//
static void			partial_mul(t_varint *p_mul, t_varint a, uint8_t bxj)
{
	int16_t		i;
	uint8_t			tmp;
	uint8_t			upp;
	int8_t			carr;

	carr = 0;
	upp = 0;
	i = -1;
	while (++i < a.len)
	{
		tmp = a.x[i] * bxj;
		p_mul->x[p_mul->len] = tmp + upp + carr;
		p_mul->len++;
		carr = add_carry(tmp, upp, carr);
		upp = upper(a.x[i], bxj);
	}
	if ((tmp = upp + carr) > 0)
	{
		p_mul->x[p_mul->len] = tmp;
		p_mul->len += 1;
	}
	v_len(p_mul);
}

t_varint			v_mul(t_varint a, t_varint b, bool check)
{
	t_varint		ret;
	t_varint		p_mul;
	int16_t		j;
	int8_t			sign;
	

	if (check && !v_check(&a, &b, NULL, "mul"))
		return (g_v[3]);
	sign = a.sign * b.sign;
	a.sign = 1;
	b.sign = 1;
	ret = g_v[0];
	j = -1;
	while (++j < b.len)
	{
		p_mul = g_v[0];
		p_mul.len = j;
		partial_mul(&p_mul, a, b.x[j]);
		ret = v_add(ret, p_mul, false);
		if (is_g_v(3, &ret))
			return (ret);
	}
	ret.sign = sign;
	return (ret);
}

//static void	ft_mul_4byte(
//		unsigned int *mul32, unsigned int *a32, unsigned int *b32, size_t n)
//{
//	size_t			i;
//	size_t			product;
//	size_t			overflow;
//	unsigned int	buf;
//
//	overflow = 0;
//	i = n / sizeof(unsigned int);
//	while (i--)
//	{
//		product = (size_t)(*a32) * (size_t)(*b32) + overflow + *mul32;
//		overflow = product / 0x100000000;
//		*mul32 = product - overflow * 0x100000000;
//		mul32++;
//		b32++;
//	}
//	i = n % sizeof(unsigned int);
//	buf = 0;
//	ft_memcpy(&buf, b32, i);
//	product = (size_t)(*a32) * (size_t)(buf) + overflow + *mul32;
//	overflow = product / 0x100000000;
//	*mul32 = product - overflow * 0x100000000;
//	*++mul32 = overflow;
//}
//
//t_varint			v_mul(t_varint a, t_varint b, bool check)
//{
//	t_varint		ret;
//	int8_t			sign;
//
//	if (check && !v_check(&a, &b, NULL, "mul"))
//		return (g_v[3]);
//	sign = a.sign * b.sign;
//	a.sign = 1;
//	b.sign = 1;
//	ret = g_v[0];
//	ft_memset((uint8_t *)ret.x, 0, a.len * V_LEN + b.len * V_LEN + 4);
//
//	size_t			i;
//	unsigned int	*mul32;
//	unsigned int	*a32;
//	unsigned int	*b32;
//	unsigned int	buf;
//
//	mul32 = (unsigned int *)ret.x;
//	a32 = (unsigned int *)a.x;
//	b32 = (unsigned int *)b.x;
//	i = a.len / sizeof(unsigned int);
//	while (i--)
//	{
//		ft_mul_4byte(mul32, a32, b32, b.len);
//		mul32++;
//		a32++;
//	}
//	if ((i = a.len % sizeof(unsigned int)) == 0)
//	{	
//		v_len(&ret);
//		return ret;
//	}
//	buf = 0;
//	ft_memcpy(&buf, a32, i);
//	ft_mul_4byte(mul32, &buf, b32, b.len);
//
//
//	
//
//
//
//	ret.sign = sign;
//	v_len(&ret);
//	return (ret);
//}
//
//

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
