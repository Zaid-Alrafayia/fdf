/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:22:56 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/21 17:30:26 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../fdf.h"

static void	project_iso(int gx, int gy, int gz, int scale, int height, int ox,
		int oy, int *sx, int *sy)
{
	double	dx;
	double	dy;

	const double ang = M_PI / 6.0; /* 30 degrees */
	dx = (double)(gx - gy);
	dy = (double)(gx + gy);
	*sx = (int)(dx * cos(ang) * (double)scale) + ox;
	*sy = (int)(dy * sin(ang) * (double)scale) - (int)(gz * height) + oy;
}

void	put_row(t_pixel **head, void *mlx, void *mlx_win)
{
	t_pixel	*tmp;
	int		sx;
	int		sy;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		sx = 0;
		sy = 0;
		project_iso(tmp->x, tmp->y, tmp->z, 20, 10, 540, 900 / 4, &sx, &sy);
		ft_printf("%d\n%d", sy, sx);
		mlx_pixel_put(mlx, mlx_win, sx, sy, tmp->color);
		tmp = tmp->next;
	}
}

void	put_matrix(t_matrix **matrix, void *mlx, void *mlx_win)
{
	t_pixel		*row;
	t_matrix	*tmp;

	tmp = *matrix;
	while (tmp)
	{
		row = tmp->node;
		put_row(&row, mlx, mlx_win);
		tmp = tmp->next;
	}
}
