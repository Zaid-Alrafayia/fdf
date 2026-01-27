/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:38:26 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/28 00:39:47 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../fdf.h"

static void	rotate_x(double *y, double *z, double alpha_deg)
{
	double	alpha;
	double	tmp_y;
	double	tmp_z;

	alpha = alpha_deg * M_PI / 180.0;
	tmp_y = *y;
	tmp_z = *z;
	*y = tmp_y * cos(alpha) - tmp_z * sin(alpha);
	*z = tmp_y * sin(alpha) + tmp_z * cos(alpha);
}

static void	rotate_y(double *x, double *z, double theta_deg)
{
	double	theta;
	double	tmp_x;
	double	tmp_z;

	theta = theta_deg * M_PI / 180.0;
	tmp_x = *x;
	tmp_z = *z;
	*x = tmp_x * cos(theta) + tmp_z * sin(theta);
	*z = tmp_z * cos(theta) - tmp_x * sin(theta);
}

static void	rotate_z(double *x, double *y, double gamma_deg)
{
	double	gamma;
	double	tmp_x;
	double	tmp_y;

	gamma = gamma_deg * M_PI / 180.0;
	tmp_x = *x;
	tmp_y = *y;
	*x = tmp_x * cos(gamma) - tmp_y * sin(gamma);
	*y = tmp_x * sin(gamma) + tmp_y * cos(gamma);
}

void	project_iso(int gx, int gy, int gz, t_fdf **fdf, int ox, int oy,
		int *sx, int *sy)
{
	double x, y, z;
	int px, py;
	const double ang = M_PI / 6.0; // 30 degrees for classic iso
	x = (double)gx * (*fdf)->scale;
	y = (double)gy * (*fdf)->scale;
	z = (double)gz * (*fdf)->height_scale;
	if ((*fdf)->z_moved)
		rotate_z(&x, &y, (*fdf)->z_ang);
	if ((*fdf)->y_moved)
		rotate_y(&x, &z, (*fdf)->y_ang);
	if ((*fdf)->x_moved)
		rotate_x(&y, &z, (*fdf)->x_ang);
	px = (x - y) * cos(ang);
	py = (x + y) * sin(ang) - z;
	*sx = (int)(px + ox);
	*sy = (int)(py + oy);
}
