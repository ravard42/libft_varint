/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putchar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 12:44:32 by ravard            #+#    #+#             */
/*   Updated: 2019/06/28 12:44:49 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putchar(char c)
{
	write(1, &c, 1);
}

void			ft_putnchar(char *ptr, size_t len)
{
	write(1, ptr, len);
}

void			ft_putstr(char *str)
{
	int	i;

	i = -1;
	if (str)
		while (str[++i])
			ft_putchar(str[i]);
}
