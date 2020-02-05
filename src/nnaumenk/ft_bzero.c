/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 23:52:03 by nnaumenk          #+#    #+#             */
/*   Updated: 2018/08/19 03:49:00 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	size_t			*str64;
	unsigned char	*str8;

	str64 = (size_t *)s;
	i = n / sizeof(size_t);
	while (i--)
		*str64++ = 0;
	str8 = (unsigned char *)str64;
	i = n % sizeof(size_t);
	while (i--)
		*str8++ = 0;
}
