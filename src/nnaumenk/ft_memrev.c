/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 00:05:08 by nnaumenk          #+#    #+#             */
/*   Updated: 2018/11/15 15:26:21 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memrev(void *mem, size_t num)
{
	size_t			i;
	unsigned char	*mem_start;
	unsigned char	*mem_end;
	unsigned char	buf;

	mem_start = mem;
	mem_end = mem_start + num - 1;
	i = num / 2;
	while (i--)
	{
		buf = *mem_start;
		*mem_start++ = *mem_end;
		*mem_end-- = buf;
	}
}
