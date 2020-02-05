/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint_isnull.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 23:52:03 by nnaumenk          #+#    #+#             */
/*   Updated: 2019/02/27 18:31:07 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bigint.h"

int		ft_bigint_isnull(t_bigint *a)
{
	size_t			i;
	size_t			*mem64;
	unsigned char	*mem8;

	mem64 = (size_t *)a->value;
	i = a->size / sizeof(size_t);
	while (i--)
		if (*mem64++ != 0)
			return (0);
	mem8 = (unsigned char *)mem64;
	i = a->size % sizeof(size_t);
	while (i--)
		if (*mem8++ != 0)
			return (0);
	return (1);
}
