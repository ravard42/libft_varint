/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 12:31:25 by ravard            #+#    #+#             */
/*   Updated: 2019/06/28 12:43:20 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		init_read_struct(t_read *p)
{
	p->msg = NULL;
	p->len = 0;
	p->prev = NULL;
	p->next = NULL;
}

static t_read	*new_link(t_read *current)
{
	if (!(current->next = (t_read *)ft_memalloc(sizeof(t_read))))
		return (NULL);
	init_read_struct(current->next);
	current->next->prev = current;
	return (current->next);
}

static int		fill_linked_list(int fd, t_read *origin)
{
	t_read	*current;
	int		r;
	int		n;
	char	buff[READ_BUFF_SIZE];

	n = 0;
	current = origin;
	while ((r = read(fd, buff, READ_BUFF_SIZE)) > 0)
	{
		if (!(current->msg = (char *)ft_memalloc(sizeof(char) * r)))
			return (-2);
		ft_memcpy(current->msg, buff, r);
		current->len = r;
		if (!(current = new_link(current)))
			return (-2);
		n += r;
	}
	if (fd)
		close(fd);
	if (r == -1 && ft_dprintf(2, "%sread error in ft_read [...]%s\n", KRED, KNRM))
		return (-1);
	return (n);
}

static void		merge_list(t_read *origin, t_read *r)
{
	t_read	*current;
	int		i;

	current = origin;
	i = 0;
	while (current->next)
	{
		ft_memcpy(r->msg + i * READ_BUFF_SIZE, current->msg, current->len);
		current = current->next;
		free(current->prev->msg);
		if (i != 0)
			free(current->prev);
		i++;
	}
	free(current);
}

/*
** RETURN VALUE		SIGNIFICATION
**	 -2				malloc error
**	 -1				open/read error
**	  0				rien a lire
**	 >0				nombre de caractères lus
*/

int				ft_read(char *file, t_read *r)
{
	int		fd;
	t_read	origin;

	if (file == NULL)
		fd = 0;
	else
	{
		if ((fd = open(file, O_RDONLY)) == -1
			&& ft_dprintf(2, "%s\"%s\" is not a valid file for reading%s\n",
			KRED, file, KNRM))
			return (-1);
	}
	init_read_struct(r);
	init_read_struct(&origin);
	if ((r->len = fill_linked_list(fd, &origin)) <= 0)
		return (r->len);
	if (!(r->msg = (char *)ft_memalloc(sizeof(char) * (r->len + 1))))
		return (-2);
	merge_list(&origin, r);
	return (r->len);
}