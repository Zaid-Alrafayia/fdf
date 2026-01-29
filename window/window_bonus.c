/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:04:28 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/28 15:37:10 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../fdf.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

int	close_program(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (!fdf)
		exit(0);
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->mlx_win)
		mlx_destroy_window(fdf->mlx, fdf->mlx_win);
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
	free_fdf(&fdf);
	exit(0);
	return (0);
}

int	orthographic_view(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (!fdf)
		exit(0);
	if (keycode == 105)
		fdf->ang = M_PI / 6;
	else if (keycode == 111)
	{
		fdf->ang = 0;
		fdf->x_ang = 0;
		fdf->y_ang = 0;
		fdf->z_ang = 0;
		fdf->x_moved = true;
		fdf->y_moved = true;
		fdf->z_moved = true;
	}
	if (fdf->mlx && fdf->mlx_win)
		mlx_clear_window(fdf->mlx, fdf->mlx_win);
	put_matrix(&fdf);
	return (0);
}

int	key_handler(int keycode, void *param)
{
	if (keycode == 65307)
		return (close_program(param));
	else if (keycode == 97 || keycode == 100)
		return (move_x_axis(keycode, param));
	else if (keycode == 119 || keycode == 115)
		return (move_y_axis(keycode, param));
	else if (keycode == 113 || keycode == 101)
		return (move_z_axis(keycode, param));
	else if (keycode == 45 || keycode == 61 || keycode == 43)
		return (change_height_scale(keycode, param));
	else if (keycode == 112 || keycode == 105)
		return (orthographic_view(keycode, param));
	else if (keycode == 111)
		return (orthographic_view(keycode, param));
	return (0);
}

void	init_window(t_fdf **fdf)
{
	(*fdf)->mlx = mlx_init();
	if (!(*fdf)->mlx)
	{
		perror("ERROR: can't make window.\n");
		return ;
	}
	(*fdf)->mlx_win = mlx_new_window((*fdf)->mlx, (*fdf)->win_width,
			(*fdf)->win_height, "!!The Great FDF!!");
	(*fdf)->img = mlx_new_image((*fdf)->mlx, (*fdf)->win_width,
			(*fdf)->win_height);
	(*fdf)->img_data = mlx_get_data_addr((*fdf)->img, &(*fdf)->bpp,
			&(*fdf)->line_len, &(*fdf)->endian);
	if (!(*fdf)->mlx_win || !(*fdf)->img || !(*fdf)->img_data)
	{
		close_program(*fdf);
		return ;
	}
	put_matrix(fdf);
	mlx_hook((*fdf)->mlx_win, 4, 1L << 2, zoom_scaling, *fdf);
	mlx_hook((*fdf)->mlx_win, 2, 1L << 0, key_handler, *fdf);
	mlx_hook((*fdf)->mlx_win, 17, 0L, close_program, *fdf);
	mlx_loop((*fdf)->mlx);
}
