/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:34:44 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/28 15:38:03 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../fdf.h"

void	free_split(char **arr)
{
	char	**save;

	if (!arr)
		return ;
	save = arr;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(save);
}

static void	free_pixels(t_pixel *p)
{
	t_pixel	*tmp;

	while (p)
	{
		tmp = p->next;
		free(p);
		p = tmp;
	}
}

void	free_matrix(t_matrix *m)
{
	t_matrix	*tmp;

	while (m)
	{
		tmp = m->next;
		if (m->node)
			free_pixels(m->node);
		free(m);
		m = tmp;
	}
}

void	free_fdf(t_fdf **fdf)
{
	if (!fdf || !*fdf)
		return ;
	if ((*fdf)->matrix)
		free_matrix((*fdf)->matrix);
	free(*fdf);
	*fdf = NULL;
}

void	clear_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}
