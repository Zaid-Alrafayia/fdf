/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:22:56 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/22 18:05:01 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

static void project_iso(int gx, int gy, int gz, int scale, int height, int ox, int oy, int *sx, int *sy)
{
	
	int px;
	int py;
double x = (double)gx * scale;
double y = (double)gy * scale;
double z = (double)gz * height;
const double ang = M_PI / 6.0;
	px = (x - y) * cos(ang);
	py = (x + y) * sin(ang) - z;
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
void	put_row(t_pixel **head, void *mlx, void *mlx_win)
{
	t_pixel	*tmp;
	int		sx;
	int		sy;
	int		prev_set;
	int		px;
	int		py;

	prev_set = 0;
	px = 0;
	py = 0;
	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		project_iso(tmp->x, tmp->y, tmp->z, 5, 5, 200, 300, &sx, &sy);
		if (prev_set)
			drawline(mlx, mlx_win, px, py, sx, sy, tmp->color);
		mlx_pixel_put(mlx, mlx_win, sx, sy, tmp->color);
		px = sx;
		py = sy;
		prev_set = 1;
		tmp = tmp->next;
	}
}

void	put_matrix(t_matrix **matrix, void *mlx, void *mlx_win)
{
	t_pixel		*row;
	t_matrix	*tmp;
	t_pixel		*nrow;
	t_pixel		*r;

	tmp = *matrix;
	while (tmp)
	{
		row = tmp->node;
		put_row(&row, mlx, mlx_win);
		if (tmp->next)
		{
			nrow = tmp->next->node;
			r = tmp->node;
			while (r && nrow)
			{
				int sx, sy, sx2, sy2;
				project_iso(r->x, r->y, r->z, 5, 5, 200, 300, &sx, &sy);
				project_iso(nrow->x, nrow->y, nrow->z, 5, 5, 200, 300, &sx2,
					&sy2);
				drawline(mlx, mlx_win, sx, sy, sx2, sy2, r->color);
				r = r->next;
				nrow = nrow->next;
			}
		}
		tmp = tmp->next;
	}
}
