/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:05:38 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/28 17:16:00 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_bonus.h"

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

t_pixel	*process_line(t_fdf **fdf, char *str, int y, int *row_width)
{
	char	**arr;
	int		xz[2];
	t_pixel	*row;

	arr = ft_split(str, ' ');
	if (!arr)
		return (NULL);
	row = NULL;
	xz[0] = 0;
	while (arr[xz[0]] && ++(*row_width))
	{
		xz[1] = ft_atoi(arr[xz[0]]);
		if (xz[1] < (*fdf)->z_min)
			(*fdf)->z_min = xz[1];
		if (xz[1] > (*fdf)->z_max)
			(*fdf)->z_max = xz[1];
		if (add_to_back(&row, xz[0], y, arr[xz[0]]))
		{
			free_split(arr);
			return (NULL);
		}
		xz[0]++;
	}
	free_split(arr);
	return (row);
}

void	handle_error_and_exit(t_fdf **fdf, int fd)
{
	if (fdf)
		free_fdf(fdf);
	clear_gnl(fd);
	close(fd);
	exit(1);
}

void	add_row_to_matrix_and_update(t_fdf **fdf, t_pixel **row, int row_width,
		int y)
{
	if (y == 0)
		(*fdf)->matrix_width = row_width;
	add_to_matrix(&(*fdf)->matrix, row);
}
