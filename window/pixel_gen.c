/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:22:56 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/23 17:33:50 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

static void	project_iso(int gx, int gy, int gz, t_fdf **fdf, int ox, int oy,
		int *sx, int *sy)
{
	int				px;
	int				py;
	double			xyz[3];
	const double	ang = M_PI / 6.0;

	xyz[0] = (double)gx * (*fdf)->scale;
	xyz[1] = (double)gy * (*fdf)->scale;
	xyz[2] = (double)gz * (*fdf)->height_scale;
	px = (xyz[0] - xyz[1]) * cos(ang);
	py = (xyz[0] + xyz[1]) * sin(ang) - xyz[2];
	*sx = (int)(px + ox);
	*sy = (int)(py + oy);
}

void	drawline(void *mlx, void *mlx_win, int x0, int y0, int x1, int y1,
		int color)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		mlx_pixel_put(mlx, mlx_win, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

static t_pixel	*get_pixel_at(t_matrix *matrix, int y, int x)
{
	int		i;
	t_pixel	*pixel;

	i = 0;
	while (y > 0 && matrix)
	{
		matrix = matrix->next;
		y--;
	}
	if (!matrix)
		return (NULL);
	pixel = matrix->node;
	while (i < x && pixel)
	{
		pixel = pixel->next;
		i++;
	}
	return (pixel);
}

static void	draw_neighbors(t_fdf **fdf, int y, int x)
{
	t_pixel	*curr;
	t_pixel	*right;
	t_pixel	*below;
	int		sxy[4];

	curr = get_pixel_at((*fdf)->matrix, y, x);
	right = get_pixel_at((*fdf)->matrix, y, x + 1);
	below = get_pixel_at((*fdf)->matrix, y + 1, x);
	if (curr && right)
	{
		project_iso(curr->x, curr->y, curr->z, fdf, (*fdf)->win_width / 2
			- (*fdf)->matrix_width / 2, (*fdf)->win_height / 2
			- (*fdf)->matrix_height / 2, &sxy[0], &sxy[1]);
		project_iso(right->x, right->y, right->z, fdf, (*fdf)->win_width / 2
			- (*fdf)->matrix_width / 2, (*fdf)->win_height / 2
			- (*fdf)->matrix_height / 2, &sxy[2], &sxy[3]);
		drawline((*fdf)->mlx, (*fdf)->mlx_win, sxy[0], sxy[1], sxy[2], sxy[3],
			curr->color);
	}
	if (curr && below)
	{
		project_iso(curr->x, curr->y, curr->z, fdf, (*fdf)->win_width / 2
			- (*fdf)->matrix_width / 2, (*fdf)->win_height / 2
			- (*fdf)->matrix_height / 2, &sxy[0], &sxy[1]);
		project_iso(below->x, below->y, below->z, fdf, (*fdf)->win_width / 2
			- (*fdf)->matrix_width / 2, (*fdf)->win_height / 2
			- (*fdf)->matrix_height / 2, &sxy[2], &sxy[3]);
		drawline((*fdf)->mlx, (*fdf)->mlx_win, sxy[0], sxy[1], sxy[2], sxy[3],
			curr->color);
	}
}

void	put_matrix(t_fdf **fdf)
{
	int	y;
	int	x;

	y = 0;
	while (y < (*fdf)->matrix_height)
	{
		x = 0;
		while (x < (*fdf)->matrix_width)
		{
			draw_neighbors(fdf, y, x);
			x++;
		}
		y++;
	}
}
