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
#include <string.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

static inline void img_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	if (!fdf || !fdf->img_data)
		return;
	if (x < 0 || y < 0 || x >= fdf->win_width || y >= fdf->win_height)
		return;
	int bytes_per_pixel = fdf->bpp / 8;
	if (bytes_per_pixel <= 0)
		return;
	int idx = y * fdf->line_len + x * bytes_per_pixel;
	unsigned int col = (unsigned int)color;
	if (fdf->endian == 0)
	{
		for (int i = 0; i < bytes_per_pixel; ++i)
			fdf->img_data[idx + i] = (col >> (8 * i)) & 0xFF;
	}
	else
	{
		for (int i = 0; i < bytes_per_pixel; ++i)
			fdf->img_data[idx + i] = (col >> (8 * (bytes_per_pixel - 1 - i))) & 0xFF;
	}
}
static void rotate_x(double *y, double *z, double alpha_deg)
{
    double alpha = alpha_deg * M_PI / 180.0;
    double tmp_y = *y;
    double tmp_z = *z;
    *y = tmp_y * cos(alpha) - tmp_z * sin(alpha);
    *z = tmp_y * sin(alpha) + tmp_z * cos(alpha);
}

static void rotate_y(double *x, double *z, double theta_deg)
{
    double theta = theta_deg * M_PI / 180.0;
    double tmp_x = *x;
    double tmp_z = *z;
    *x = tmp_x * cos(theta) + tmp_z * sin(theta);
    *z = tmp_z * cos(theta) - tmp_x * sin(theta);
}

static void rotate_z(double *x, double *y, double gamma_deg)
{
    double gamma = gamma_deg * M_PI / 180.0;
    double tmp_x = *x;
    double tmp_y = *y;
    *x = tmp_x * cos(gamma) - tmp_y * sin(gamma);
    *y = tmp_x * sin(gamma) + tmp_y * cos(gamma);
}

// Modified project_iso to apply rotations
static void	project_iso(int gx, int gy, int gz, t_fdf **fdf, int ox, int oy,
        int *sx, int *sy)
{
    double	x, y, z;
    int		px, py;
    const double	ang = M_PI / 6.0; // 30 degrees for classic iso

    x = (double)gx * (*fdf)->scale;
    y = (double)gy * (*fdf)->scale;
    z = (double)gz * (*fdf)->height_scale;

    // Apply Z, then Y, then X rotation
	// Apply only the active axis rotation (flags are made exclusive in handlers)
	if ((*fdf)->z_moved)
		rotate_z(&x, &y, (*fdf)->z_ang);
	 if ((*fdf)->y_moved)
		rotate_y(&x, &z, (*fdf)->y_ang);
	 if ((*fdf)->x_moved)
		rotate_x(&y, &z, (*fdf)->x_ang);
	
    px = (x - y) * cos(ang);
    py = (x + y) * sin(ang) - z;
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
		img_pixel_put((*fdf), x0, y0,
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
	int y;
	int x;
	t_fdf *f;

	if (!fdf || !*fdf)
		return;
	f = *fdf;
	/* clear image buffer once per frame */
	if (f->img_data)
		memset(f->img_data, 0, (size_t)f->line_len * (size_t)f->win_height);

	compute_center_offsets(fdf);
	y = 0;
	while (y < f->matrix_height)
	{
		x = 0;
		while (x < f->matrix_width)
		{
			draw_neighbors(fdf, y, x);
			x++;
		}
		y++;
	}
	/* blit image buffer to window once per frame */
	if (f->mlx && f->mlx_win && f->img)
		mlx_put_image_to_window(f->mlx, f->mlx_win, f->img, 0, 0);
}