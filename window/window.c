/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:04:28 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/23 19:07:42 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../fdf.h"
#include <stdlib.h>

int	close_program(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (!fdf)
		exit(0);
	if (fdf->mlx && fdf->mlx_win)
		mlx_destroy_window(fdf->mlx, fdf->mlx_win);
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->matrix)
		free_matrix(fdf->matrix);
	free(fdf);
	exit(0);
	return (0);
}
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
int move_y_axis(int keycode, void *param)
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
int move_z_axis(int keycode, void *param)
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
	if (keycode == 45) /* '-' key */
	{
		if (fdf->height_scale > 0)
			fdf->height_scale -= 1;
	}
	else if (keycode == 61 || keycode == 43) /* '=' or '+' */
	{
		fdf->height_scale += 1;
	}
	printf("height_scale = %f\n", fdf->height_scale);
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
		return(move_x_axis(keycode, param));
		else if (keycode == 119 || keycode == 115)
		return(move_y_axis(keycode, param));
	else if (keycode == 113 || keycode == 101)
		return(move_z_axis(keycode, param));
	else if (keycode == 45 || keycode == 61 || keycode == 43)
		return (change_height_scale(keycode, param));
		
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
	    /* create image buffer for faster rendering */
	    (*fdf)->img = mlx_new_image((*fdf)->mlx, (*fdf)->win_width, (*fdf)->win_height);
	    (*fdf)->img_data = mlx_get_data_addr((*fdf)->img, &(*fdf)->bpp,
		&(*fdf)->line_len, &(*fdf)->endian);

	    put_matrix(fdf);
	mlx_hook((*fdf)->mlx_win, 4, 1L << 2, zoom_scaling, *fdf);
	mlx_hook((*fdf)->mlx_win, 2, 1L << 0, key_handler, *fdf);
	mlx_hook((*fdf)->mlx_win, 17, 0L, close_program, *fdf);
	mlx_loop((*fdf)->mlx);
}
