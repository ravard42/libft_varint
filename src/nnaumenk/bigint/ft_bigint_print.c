/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_big_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:45:35 by nnaumenk          #+#    #+#             */
/*   Updated: 2019/02/20 16:53:13 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bigint.h"

static void	ft_big_int(char *name, t_bigint *a)
{
	size_t			i;
	unsigned char	*byte;

	byte = a->value + a->size;
	ft_printf("%s\n    %.2hhx:", name, *--byte);
	i = 0;
	while (++i < a->size - 1)
	{
		if (i % 15 == 0)
			ft_printf("\n    ");
		ft_printf("%.2hhx:", *--byte);
	}
	if (i % 15 == 0)
		ft_printf("\n    ");
	ft_printf("%.2hhx\n", *--byte);
}

void		ft_bigint_print(char *name, t_bigint *a)
{
	size_t	number;

	if (a->size > 8)
		ft_big_int(name, a);
	else
	{
		number = 0;
		ft_memcpy(&number, a->value, a->size);
		ft_printf("%s %lu (0x%lx)\n", name, number, number);
	}
}
