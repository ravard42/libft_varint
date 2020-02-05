/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnaumenk <nnaumenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 22:12:53 by nnaumenk          #+#    #+#             */
/*   Updated: 2019/02/20 20:28:35 by nnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BIGINT_STRUCT_H
# define FT_BIGINT_STRUCT_H

typedef struct		s_bigint
{
	unsigned char	*value;
	size_t			size;
}					t_bigint;

#endif
