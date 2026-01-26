/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:23:08 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/23 20:58:13 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_scaling(t_fdf **fdf)
{
	int	z;

	z = (*fdf)->z_max - (*fdf)->z_min;
	if (z == 0)
		z = 1;
	(*fdf)->scale = ((*fdf)->win_width / (*fdf)->matrix_width) / 2;
	if ((*fdf)->scale < 1)
		(*fdf)->scale = 1;
	(*fdf)->height_scale = ((*fdf)->win_height / z) / 4;
	if ((*fdf)->height_scale < 1)
		(*fdf)->height_scale = 1;
}

int	zoom_scaling(int button, int x, int y, void *param)
{
	t_fdf	*fdf;
	int		step;
	int		previous_scale;

	(void)x;
	(void)y;
	fdf = (t_fdf *)param;
	if (!fdf)
		return (0);
	previous_scale = fdf->scale;
	step = fdf->scale / 20;
	if (step < 1)
		step = 1;
	if (button == 4)
		fdf->scale += step;
	else if (button == 5)
	{
		fdf->scale -= step;
		if (fdf->scale < 1)
			fdf->scale = 1;
	}
	if ((button == 4 || button == 5) && previous_scale != fdf->scale)
	{
		mlx_clear_window(fdf->mlx, fdf->mlx_win);
		put_matrix(&fdf);
	}
	return (0);
}
