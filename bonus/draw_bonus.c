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
