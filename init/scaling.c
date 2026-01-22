/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:23:08 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/22 21:26:30 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_scaling(t_fdf **fdf)
{
	int z;

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
