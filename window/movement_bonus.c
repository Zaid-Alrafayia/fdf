/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:36:50 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/28 00:37:30 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../fdf.h"

int	move_x_axis(int keycode, void *param)
{
	t_fdf			*fdf;
	const double	delta = 2.0;

	fdf = (t_fdf *)param;
	if (!fdf)
		return (0);
	if (keycode == 100)
		fdf->x_ang += delta;
	else if (keycode == 97)
		fdf->x_ang -= delta;
	fdf->x_ang = fmod(fdf->x_ang, 360.0);
	if (fdf->x_ang < 0.0)
		fdf->x_ang += 360.0;
	if (fdf->mlx && fdf->mlx_win)
		mlx_clear_window(fdf->mlx, fdf->mlx_win);
	fdf->x_moved = true;
	put_matrix(&fdf);
	return (0);
}

int	move_y_axis(int keycode, void *param)
{
	t_fdf			*fdf;
	const double	delta = 2.0;

	fdf = (t_fdf *)param;
	if (!fdf)
		return (0);
	if (keycode == 119)
		fdf->y_ang += delta;
	else if (keycode == 115)
		fdf->y_ang -= delta;
	fdf->y_ang = fmod(fdf->y_ang, 360.0);
	if (fdf->y_ang < 0.0)
		fdf->y_ang += 360.0;
	if (fdf->mlx && fdf->mlx_win)
		mlx_clear_window(fdf->mlx, fdf->mlx_win);
	fdf->y_moved = true;
	put_matrix(&fdf);
	return (0);
}

int	move_z_axis(int keycode, void *param)
{
	t_fdf			*fdf;
	const double	delta = 2.0;

	fdf = (t_fdf *)param;
	if (!fdf)
		return (0);
	if (keycode == 101)
		fdf->z_ang += delta;
	else if (keycode == 113)
		fdf->z_ang -= delta;
	fdf->z_ang = fmod(fdf->z_ang, 360.0);
	if (fdf->z_ang < 0.0)
		fdf->z_ang += 360.0;
	if (fdf->mlx && fdf->mlx_win)
		mlx_clear_window(fdf->mlx, fdf->mlx_win);
	fdf->z_moved = true;
	put_matrix(&fdf);
	return (0);
}

int	change_height_scale(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (!fdf)
		return (0);
	if (keycode == 45)
	{
		if (fdf->height_scale > 0)
			fdf->height_scale -= 1;
	}
	else if (keycode == 61 || keycode == 43)
	{
		fdf->height_scale += 1;
	}
	if (fdf->mlx && fdf->mlx_win)
		mlx_clear_window(fdf->mlx, fdf->mlx_win);
	put_matrix(&fdf);
	return (0);
}
