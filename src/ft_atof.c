/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 21:31:53 by ravard            #+#    #+#             */
/*   Updated: 2017/02/26 21:32:55 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool		in09(char c)
{
	return (c >= '0' && c <= '9');
}

bool			ft_is_float(char *s)
{
	int	i;
	int	k;

	if (s && (in09(s[0]) || (s[0] == '-' && in09(s[1]))))
	{
		k = 0;
		i = 0;
		while (s[++i])
		{
			if (s[i] == '.' && (k += 1))
				continue;
			if (!(in09(s[i])))
				return (0);
		}
		if (k > 1 || !in09(s[i - 1]))
			return (0);
		return (1);
	}
	return (0);
}

/*
** 	Be carful in case floor part is -0 and fract part is not 0
**	endeed in such case atoi("-0") return 0 and we loose signess (cf line 62)
*/

float		ft_atof(char *s)
{
	char	**tmp;
	float	floor;
	float	ret;

	if (!ft_is_float(s))
		return (0);
	tmp = ft_strsplit(s, '.');
	ret = 0;
	ret = tmp[1] ? (float)ft_atoi(tmp[1]) / ft_power(10, ft_strlen(tmp[1])) : 0;
	floor = (float)ft_atoi(tmp[0]);
	ret = (floor >= 0) ? ret + floor : floor - ret;
	ret *= (!ft_strcmp(tmp[0], "-0")) ? -1 : 1;
	free_split(tmp);
	return (ret);
}
