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
	mlx_hook((*fdf)->mlx_win, 4, 1 << 2, set_scaling, &fdf);
	mlx_loop((*fdf)->mlx);
}

void	destroy_window(t_fdf **fdf)
{
	mlx_destroy_window((*fdf)->mlx, (*fdf)->mlx_win);
}
