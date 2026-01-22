/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:05:38 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/22 21:31:33 by zaalrafa         ###   ########.fr       */
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

void	init_matrix(t_fdf **fdf, int fd)
{
	int		coordinates[2];
	char	*str;
	char	**arr;
	char	**save;
	t_pixel	*row;
	int		row_width;
	int		z_val;

	row_width = 0;
	coordinates[1] = 0;
	row = NULL;
	str = get_next_line(fd);
	while (str)
	{
		coordinates[0] = 0;
		arr = ft_split(str, ' ');
		save = arr;
		free(str);
		row_width = 0;
		while (*arr)
		{
			z_val = ft_atoi(*arr);
			if (z_val < (*fdf)->z_min)
				(*fdf)->z_min = z_val;
			if (z_val > (*fdf)->z_max)
				(*fdf)->z_max = z_val;
			if (add_to_back(&row, coordinates[0], coordinates[1], *arr))
			{
				free_split(save);
				free_matrix((*fdf)->matrix);
				return ;
			}
			coordinates[0]++;
			arr++;
			row_width++;
		}
		if (coordinates[1] == 0)
			(*fdf)->matrix_width = row_width;
		add_to_matrix(&(*fdf)->matrix, &row);
		coordinates[1]++;
		free_split(save);
		str = get_next_line(fd);
	}
	(*fdf)->matrix_height = coordinates[1];
	close(fd);
}
