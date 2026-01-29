/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:23:08 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/28 17:26:17 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_bonus.h"

void	set_scaling(t_fdf **fdf)
{
	int		z;
	double	h;
	double	max_h;

	z = (*fdf)->z_max - (*fdf)->z_min;
	if (z == 0)
		z = 1;
	(*fdf)->scale = ((*fdf)->win_width / (*fdf)->matrix_width) / 2;
	if ((*fdf)->scale < 1)
		(*fdf)->scale = 1;
	h = ((double)(*fdf)->win_height / (double)z) / 4.0;
	max_h = (double)(*fdf)->scale;
	if (h > max_h)
		h = max_h;
	if (h < 0.1)
		h = 0.1;
	(*fdf)->height_scale = h;
}

void	zoom_condtions(t_fdf **fdf, int ab[2], int button)
{
	if (ab[0] < 1)
		ab[0] = 1;
	if (button == 4)
		(*fdf)->scale += ab[0];
	else if (button == 5)
	{
		(*fdf)->scale -= ab[0];
		if ((*fdf)->scale < 1)
			(*fdf)->scale = 1;
	}
}

int	zoom_scaling(int button, int x, int y, void *param)
{
	t_fdf	*fdf;
	int		ab[2];

	(void)y;
	(void)x;
	fdf = (t_fdf *)param;
	if (!fdf)
		return (0);
	ab[1] = fdf->scale;
	ab[0] = fdf->scale / 20;
	zoom_condtions(&fdf, ab, button);
	if ((button == 4 || button == 5) && ab[1] != fdf->scale)
	{
		mlx_clear_window(fdf->mlx, fdf->mlx_win);
		put_matrix(&fdf);
	}
	return (0);
}
