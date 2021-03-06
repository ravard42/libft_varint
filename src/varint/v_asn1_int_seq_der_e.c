/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_asn1_int_seq_der_e.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 04:39:29 by ravard            #+#    #+#             */
/*   Updated: 2020/05/12 03:30:37 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	about h[1 + nb_varint][6]:
**	index 0 for sequence header, and others for integer headers
**	h[x][0] = header len
**	h[x][1:4] = header
**  h[x][5] = add sign byte (or not) between header and value
*/

int8_t			put_der_header(uint8_t *h, uint8_t type, unsigned int len)
{
	if (len > 0xffff
		&& ft_dprintf(2, g_v_sterr[V_ERR_DER_2BIG], KRED, KNRM))
		return (-1);
	ft_memset((char *)h, 0, 5);
	h[1] = type;
	if (len < 0x80)
	{
		h[0] = 2;
		h[2] = len;
	}
	else if (len <= 0xff)
	{
		h[0] = 3;
		h[2] = 0x81;
		h[3] = len;
	}
	else if (len <= 0xffff)
	{
		h[0] = 4;
		h[2] = 0x82;
		h[3] = len >> 8;
		h[4] = len & 0xff;
	}
	return (0);
}

static int		set_sub_header(uint8_t *h, t_varint v)
{
	uint8_t	mask;
	int		tot_len;

	mask = 0x80;
	h[5] = v.x[v.len - 1] & mask ? 1 : 0;
	if (put_der_header(h, 0x02, h[5] + v.len) == -1)
		return (-1);
	tot_len = h[0] + h[5] + v.len;
	return (tot_len);
}

void			write_data(t_read *r, uint8_t h[][6], t_varint *v,
		int nb_varint)
{
	int				i;

	ft_memcpy(r->msg, h[0] + 1, h[0][0]);
	r->len = h[0][0];
	i = -1;
	while (++i < nb_varint)
	{
		ft_memcpy(r->msg + r->len, h[i + 1] + 1, h[i + 1][0]);
		r->len += (h[i + 1][5]) ? h[i + 1][0] + 1 : h[i + 1][0];
		ft_memrcpy(r->msg + r->len, v[i].x, v[i].len);
		r->len += v[i].len;
	}
}

/*
** der encode nb_varint from *v and write it in *r
**	NB: *r must be blank (r->msg not allocated)
*/

bool			v_asn1_int_seq_der_e(t_read *r, t_varint *v, int nb_varint)
{
	unsigned int	seq_len;
	int				i;
	int				tmp;
	uint8_t			h[1 + nb_varint][6];

	seq_len = 0;
	tmp = 0;
	i = -1;
	while (++i < nb_varint
		&& (tmp = set_sub_header(h[i + 1], v[i])) != -1)
		seq_len += tmp;
	if (tmp == -1 || put_der_header(h[0], 0x30, seq_len) == -1)
		return (false);
	if (!(r->msg = (char *)ft_memalloc(sizeof(char) * (h[0][0] + seq_len + 1)))
		&& ft_dprintf(2, "%smalloc error%s\n", KRED, KNRM))
		return (false);
	write_data(r, h, v, nb_varint);
	return (true);
}
