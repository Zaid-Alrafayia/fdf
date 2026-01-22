/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:22:56 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/21 17:30:26 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../fdf.h"
#include <math.h>
#include <limits.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static void	project_iso(int gx, int gy, int gz, int scale, int height, int ox,
		int oy, int *sx, int *sy)
{
    double px, py, pz;
    const double ang_x = M_PI / 6.0; // 30 degrees (X axis tilt)
    const double ang_y = M_PI / 3.0; // 30 degrees (Y axis tilt)
	const double ang_z = M_PI / 12.0; // 30 degrees (Z axis tilt)

    // Convert grid coordinates to double
    double x = (double)gx * scale;
    double y = (double)gy * height;
    double z = (double)gz * scale;

    // Rotate around X axis
    double y1 = y * cos(ang_x) - z * sin(ang_x);
    double z1 = y * sin(ang_x) + z * cos(ang_x);

    // Rotate around Y axis
    double x2 = x * cos(ang_y) + z1 * sin(ang_y);
    double z2 = -x * sin(ang_y) + z1 * cos(ang_y);
	// Rotate around Z axis
	double px_temp = x2 * cos(ang_z) - y1 * sin(ang_z);
	double py_temp = x2 * sin(ang_z) + y1 * cos(ang_z);
	
(void)pz;
(void)z2;
    // Project to 2D and apply offsets
    px = x2 + ox + px_temp;
    py = y1 + oy + py_temp;

    *sx = (int)px;
    *sy = (int)py;
}

void	put_row(t_pixel **head, void *mlx, void *mlx_win)
{
	t_pixel	*tmp;
	 int		sx;
	 int		sy;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		 sx = 0;
		 sy = 0;
		project_iso(tmp->x, tmp->y, tmp->z, 5, 5, 200, 300, &sx, &sy);
		ft_printf("sy=%d\nsz=%d", sy, sx);
		mlx_pixel_put(mlx, mlx_win, sx ,sy , tmp->color);
		tmp = tmp->next;
	}
}

void	put_matrix(t_matrix **matrix, void *mlx, void *mlx_win)
{
	t_pixel		*row;
	t_matrix	*tmp;

	tmp = *matrix;
	while (tmp)
	{
		row = tmp->node;
		put_row(&row, mlx, mlx_win);
		tmp = tmp->next;
	}
}
