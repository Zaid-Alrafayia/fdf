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
	if (fdf->matrix)
		free_matrix(fdf->matrix);
	free(fdf);
	exit(0);
	return (0);
}
int	move_x_axis(int keycode, void *param)
{
	t_fdf			*fdf;
	const double	delta = 1.0;

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
	printf("x_ang = %.2f°\n", fdf->x_ang);
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
		move_x_axis(keycode, param);
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
	put_matrix(fdf);
	mlx_hook((*fdf)->mlx_win, 4, 1L << 2, zoom_scaling, *fdf);
	mlx_hook((*fdf)->mlx_win, 2, 1L << 0, key_handler, *fdf);
	mlx_hook((*fdf)->mlx_win, 17, 0L, close_program, *fdf);
	mlx_loop((*fdf)->mlx);
}
