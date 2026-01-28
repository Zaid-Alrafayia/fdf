/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:25:39 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/28 11:28:20 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	calc_abs_diff(int xy[4], int abs[2])
{
	abs[0] = xy[2] - xy[0];
	abs[1] = xy[3] - xy[1];
	if (abs[0] < 0)
		abs[0] = -abs[0];
	if (abs[1] < 0)
		abs[1] = -abs[1];
}

void	calc_step_direction(int xy[4], int s[2])
{
	if (xy[0] < xy[2])
		s[0] = 1;
	else
		s[0] = -1;
	if (xy[1] < xy[3])
		s[1] = 1;
	else
		s[1] = -1;
}

void	calc_total_steps(int abs[2], int *total_steps)
{
	if (abs[0] > abs[1])
		*total_steps = abs[0];
	else
		*total_steps = abs[1];
	if (*total_steps == 0)
		*total_steps = 1;
}

void	update_error_and_coords(int abs[2], int s[2], int xy[4], int *err)
{
	int	e2;

	e2 = *err * 2;
	if (e2 > -abs[1])
	{
		*err -= abs[1];
		xy[0] += s[0];
	}
	if (e2 < abs[0])
	{
		*err += abs[0];
		xy[1] += s[1];
	}
}

void	drawline(t_fdf **fdf, int xy[4], int color1, int color2)
{
	int	abs[2];
	int	s[2];
	int	err;
	int	i;
	int	total_steps;

	
	calc_abs_diff(xy, abs);
	calc_step_direction(xy, s);
	calc_total_steps(abs, &total_steps);
	err = abs[0] - abs[1];
	i = 0;
	while (1)
	{
		img_pixel_put((*fdf), xy[0], xy[1], gradient_color(color1, color2, i,
				total_steps));
		if (xy[0] == xy[2] && xy[1] == xy[3])
			break ;
		update_error_and_coords(abs, s, xy, &err);
		if (i < total_steps)
			i++;
	}
}
