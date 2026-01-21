/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:05:38 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/21 14:36:24 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../fdf.h"
#include <stdlib.h>

static t_matrix	*new_row(t_pixel **row)
{
	t_matrix	*matrix;

	matrix = malloc(sizeof(t_matrix));
	if (!matrix)
		return (NULL);
	matrix->node = *row;
	matrix->next = NULL;
	*row = NULL;
	return (matrix);
}

static void	add_to_matrix(t_matrix **matrix, t_pixel **row)
{
	t_matrix	*tail;

	if (!*matrix)
	{
		*matrix = new_row(row);
		return ;
	}
	tail = *matrix;
	while (tail->next)
		tail = tail->next;
	tail->next = new_row(row);
}

void	init_matrix(t_matrix **matrix, int fd)
{
	int		x;
	int		y;
	char	*str;
	char	**arr;
	char	**save;
	t_pixel	*row;

	y = 0;
	row = NULL;
	str = get_next_line(fd);
	while (str)
	{
		x = 0;
		arr = ft_split(str, ' ');
		save = arr;
		free(str);
		while (*arr)
		{
			if (add_to_back(&row, x, y, *arr))
			{
				free_split(save);
				free_matrix(*matrix);
				return ;
			}
			x++;
			arr++;
		}
		add_to_matrix(matrix, &row);
		y++;
		free_split(save);
		str = get_next_line(fd);
	}
}
