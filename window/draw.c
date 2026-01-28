/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:04:11 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/28 11:45:01 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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
		drawline(fdf, sxy, curr->color, right->color);
	}
	if (curr && below)
	{
		project_iso(curr, fdf, &sxy[0], &sxy[1]);
		project_iso(below, fdf, &sxy[2], &sxy[3]);
		drawline(fdf, sxy, curr->color, below->color);
	}
}

static void	compute_center_offsets(t_fdf **fdf)
{
	int		xy[2];
	int		pxy[2];
	int		minxy[2];
	int		maxxy[2];
	t_pixel	*curr;

	minxy[0] = INT_MAX;
	minxy[1] = INT_MAX;
	maxxy[0] = INT_MIN;
	maxxy[1] = INT_MIN;
	xy[1] = 0;
	while (xy[1] < (*fdf)->matrix_height)
	{
		xy[0] = 0;
		while (xy[0] < (*fdf)->matrix_width)
		{
			curr = get_pixel_at((*fdf)->matrix, xy[1], xy[0]);
			if (curr)
			{
				project_iso(curr, fdf, &pxy[0], &pxy[1]);
				if (pxy[0] < minxy[0])
					minxy[0] = pxy[0];
				if (pxy[1] < minxy[1])
					minxy[1] = pxy[1];
				if (pxy[0] > maxxy[0])
					maxxy[0] = pxy[0];
				if (pxy[1] > maxxy[1])
					maxxy[1] = pxy[1];
			}
			xy[0]++;
		}
		xy[1]++;
	}
	if (minxy[0] == INT_MAX || minxy[0] == INT_MAX)
	{
		(*fdf)->offset_x = (*fdf)->win_width / 2;
		(*fdf)->offset_y = (*fdf)->win_height / 2;
		return ;
	}
	(*fdf)->offset_x = (*fdf)->win_width / 2 - ((minxy[0] + maxxy[0]) / 2);
	(*fdf)->offset_y = (*fdf)->win_height / 2 - ((minxy[1] + maxxy[1]) / 2);
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
