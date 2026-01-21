/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:34:44 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/21 14:35:58 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../fdf.h"

void	free_pixel_row(t_pixel *p)
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
		free_pixel_row(m->node);
		free(m);
		m = tmp;
	}
}

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
