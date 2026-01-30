/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:04:28 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/29 15:10:10 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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

int	key_handler(int keycode, void *param)
{
	if (keycode == 65307)
		return (close_program(param));
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
	mlx_hook((*fdf)->mlx_win, 17, 0L, close_program, *fdf);
	mlx_hook((*fdf)->mlx_win, 2, 1L << 0, key_handler, *fdf);
	mlx_loop((*fdf)->mlx);
}
