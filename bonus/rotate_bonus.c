/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:38:26 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/28 11:46:34 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_bonus.h"

void	rotate_x(double *y, double *z, double alpha_deg)
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

void	rotate_y(double *x, double *z, double theta_deg)
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

void	rotate_z(double *x, double *y, double gamma_deg)
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

void	project_iso_raw(t_pixel *node, t_fdf **fdf, int *px, int *py)
{
	double			xyz[3];
	int				gxyz[3];
	const double	ang = (*fdf)->ang;

	gxyz[0] = node->x;
	gxyz[1] = node->y;
	gxyz[2] = node->z;
	xyz[0] = (double)gxyz[0] * (*fdf)->scale;
	xyz[1] = (double)gxyz[1] * (*fdf)->scale;
	xyz[2] = (double)gxyz[2] * (*fdf)->height_scale;
	if ((*fdf)->z_moved)
		rotate_z(&xyz[0], &xyz[1], (*fdf)->z_ang);
	if ((*fdf)->y_moved)
		rotate_y(&xyz[0], &xyz[2], (*fdf)->y_ang);
	if ((*fdf)->x_moved)
		rotate_x(&xyz[1], &xyz[2], (*fdf)->x_ang);
	*px = (int)((xyz[0] - xyz[1]) * cos(ang));
	*py = (int)((xyz[0] + xyz[1]) * sin(ang) - xyz[2]);
}

void	project_iso(t_pixel *node, t_fdf **fdf, int *sx, int *sy)
{
	int	pxy[2];

	project_iso_raw(node, fdf, &pxy[0], &pxy[1]);
	*sx = pxy[0] + (*fdf)->offset_x;
	*sy = pxy[1] + (*fdf)->offset_y;
}
