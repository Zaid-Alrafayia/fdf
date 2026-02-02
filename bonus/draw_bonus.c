/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:04:11 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/28 12:58:13 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_bonus.h"

static int	resolve_pixel_color(t_fdf *fdf, t_pixel *p)
{
	double	t;
	double	loc;
	int		step;

	if (!p)
		return (0x000000);
	if (p->color != -1)
		return (p->color);
	if (!fdf || fdf->z_max == fdf->z_min)
		return (0x228B22);
	t = (double)(p->z - fdf->z_min) / (double)(fdf->z_max - fdf->z_min);
	if (t < 0.0)
		t = 0.0;
	if (t > 1.0)
		t = 1.0;
	if (t < 0.20)
	{
		loc = t / 0.20;
		step = (int)(loc * 1000.0);
		return (gradient_color(0x000080, 0x1E90FF, step, 1000));
	}
	if (t < 0.25)
	{
		loc = (t - 0.20) / 0.05;
		step = (int)(loc * 1000.0);
		return (gradient_color(0x1E90FF, 0xF4A460, step, 1000));
	}
	if (t < 0.50)
	{
		loc = (t - 0.25) / 0.25;
		step = (int)(loc * 1000.0);
		return (gradient_color(0x228B22, 0x006400, step, 1000));
	}
	if (t < 0.70)
	{
		loc = (t - 0.50) / 0.20;
		step = (int)(loc * 1000.0);
		return (gradient_color(0x8B7765, 0x8B4513, step, 1000));
	}
	if (t < 0.90)
	{
		loc = (t - 0.70) / 0.20;
		step = (int)(loc * 1000.0);
		return (gradient_color(0xA9A9A9, 0x808080, step, 1000));
	}
	loc = (t - 0.90) / 0.10;
	step = (int)(loc * 1000.0);
	return (gradient_color(0xFFFFFF, 0xFFFFFF, step, 1000));
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
		project_iso(curr, fdf, &sxy[0], &sxy[1]);
		project_iso(right, fdf, &sxy[2], &sxy[3]);
		drawline(fdf, sxy, resolve_pixel_color(*fdf, curr),
				resolve_pixel_color(*fdf, right));
	}
	if (curr && below)
	{
		project_iso(curr, fdf, &sxy[0], &sxy[1]);
		project_iso(below, fdf, &sxy[2], &sxy[3]);
		drawline(fdf, sxy, resolve_pixel_color(*fdf, curr),
				resolve_pixel_color(*fdf, below));
	}
}

void	put_matrix(t_fdf **fdf)
{
	int		y;
	int		x;
	t_fdf	*f;

	if (!fdf || !*fdf)
		return ;
	f = *fdf;
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
	if (f->mlx && f->mlx_win && f->img)
		mlx_put_image_to_window(f->mlx, f->mlx_win, f->img, 0, 0);
}
