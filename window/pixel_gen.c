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
	const double	ang = M_PI / (*fdf)->x_ang;

	xyz[0] = (double)gx * (*fdf)->scale;
	xyz[1] = (double)gy * (*fdf)->scale;
	xyz[2] = (double)gz * (*fdf)->height_scale;
	px = (xyz[0] - xyz[1]) * cos(ang);
	py = (xyz[0] + xyz[1]) * sin(ang) - xyz[2];
	*sx = (int)(px + ox);
	*sy = (int)(py + oy);
}

static int	gradient_color(int color1, int color2, int step, int total)
{
	int		a1;
	int		r1;
	int		g1;
	int		b1;
	int		a2;
	int		r2;
	int		g2;
	int		b2;
	int		a;
	int		r;
	int		g;
	int		b;
	double	t;

	if (total <= 0)
		return (color2);
	t = (double)step / (double)total;
	a1 = (color1 >> 24) & 0xFF;
	r1 = (color1 >> 16) & 0xFF;
	g1 = (color1 >> 8) & 0xFF;
	b1 = (color1 >> 0) & 0xFF;
	a2 = (color2 >> 24) & 0xFF;
	r2 = (color2 >> 16) & 0xFF;
	g2 = (color2 >> 8) & 0xFF;
	b2 = (color2 >> 0) & 0xFF;
	a = (int)((1.0 - t) * a1 + t * a2);
	r = (int)((1.0 - t) * r1 + t * r2);
	g = (int)((1.0 - t) * g1 + t * g2);
	b = (int)((1.0 - t) * b1 + t * b2);
	return ((a & 0xFF) << 24) | ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}
void	drawline(t_fdf **fdf, int x0, int y0, int x1, int y1, int color1,
		int color2)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	i;
	int	total_steps;
	int	abs_dx;
	int	abs_dy;

	abs_dx = x1 - x0;
	if (abs_dx < 0)
		abs_dx = -abs_dx;
	abs_dy = y1 - y0;
	if (abs_dy < 0)
		abs_dy = -abs_dy;
	dx = abs_dx;
	dy = abs_dy;
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	if (dx > dy)
		total_steps = dx;
	else
		total_steps = dy;
	if (total_steps == 0)
		total_steps = 1;
	err = dx - dy;
	i = 0;
	while (1)
	{
		mlx_pixel_put((*fdf)->mlx, (*fdf)->mlx_win, x0, y0,
			gradient_color(color1, color2, i, total_steps));
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = err * 2;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
		if (i < total_steps)
			i++;
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
		project_iso(curr->x, curr->y, curr->z, fdf, (*fdf)->offset_x,
			(*fdf)->offset_y, &sxy[0], &sxy[1]);
		project_iso(right->x, right->y, right->z, fdf, (*fdf)->offset_x,
			(*fdf)->offset_y, &sxy[2], &sxy[3]);
		drawline(fdf, sxy[0], sxy[1], sxy[2], sxy[3], curr->color,
			right->color);
	}
	if (curr && below)
	{
		project_iso(curr->x, curr->y, curr->z, fdf, (*fdf)->offset_x,
			(*fdf)->offset_y, &sxy[0], &sxy[1]);
		project_iso(below->x, below->y, below->z, fdf, (*fdf)->offset_x,
			(*fdf)->offset_y, &sxy[2], &sxy[3]);
		drawline(fdf, sxy[0], sxy[1], sxy[2], sxy[3], curr->color,
			below->color);
	}
}

static void	compute_center_offsets(t_fdf **fdf)
{
	int		y;
	int		x;
	int		px;
	int		py;
	int		minx;
	int		maxx;
	int		miny;
	int		maxy;
	t_pixel	*curr;

	minx = INT_MAX;
	miny = INT_MAX;
	maxx = INT_MIN;
	maxy = INT_MIN;
	y = 0;
	while (y < (*fdf)->matrix_height)
	{
		x = 0;
		while (x < (*fdf)->matrix_width)
		{
			curr = get_pixel_at((*fdf)->matrix, y, x);
			if (curr)
			{
				project_iso(curr->x, curr->y, curr->z, fdf, 0, 0, &px, &py);
				if (px < minx)
					minx = px;
				if (py < miny)
					miny = py;
				if (px > maxx)
					maxx = px;
				if (py > maxy)
					maxy = py;
			}
			x++;
		}
		y++;
	}
	if (minx == INT_MAX || miny == INT_MAX)
	{
		(*fdf)->offset_x = (*fdf)->win_width / 2;
		(*fdf)->offset_y = (*fdf)->win_height / 2;
		return ;
	}
	(*fdf)->offset_x = (*fdf)->win_width / 2 - ((minx + maxx) / 2);
	(*fdf)->offset_y = (*fdf)->win_height / 2 - ((miny + maxy) / 2);
}

void	put_matrix(t_fdf **fdf)
{
	int	y;
	int	x;

	y = 0;
	compute_center_offsets(fdf);
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
