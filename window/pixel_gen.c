/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:22:56 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/28 10:22:55 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../fdf.h"

int	get_pixel_index(t_fdf *fdf, int x, int y)
{
	if (!fdf || !fdf->img_data)
		return (-1);
	if (x < 0 || y < 0 || x >= fdf->win_width || y >= fdf->win_height)
		return (-1);
	if (fdf->bpp <= 0)
		return (-1);
	return (y * fdf->line_len + x * (fdf->bpp / 8));
}

void	img_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	int				idx;
	int				bpp;
	int				i;
	unsigned int	col;

	idx = get_pixel_index(fdf, x, y);
	if (idx < 0)
		return ;
	bpp = fdf->bpp / 8;
	col = (unsigned int)color;
	i = -1;
	if (fdf->endian == 0)
	{
		while (i++ < bpp)
		{
			fdf->img_data[idx + i] = (col >> (8 * i)) & 0xFF;
		}
	}
	else
	{
		while (i++ < bpp)
		{
			fdf->img_data[idx + i] = (col >> (8 * (bpp - 1 - i))) & 0xFF;
		}
	}
}

int	gradient_color(int color1, int color2, int step, int total)
{
	int		argb1[4];
	int		argb2[4];
	int		argb[4];
	double	t;
	int		x;

	if (total <= 0)
		return (color2);
	t = (double)step / (double)total;
	argb1[0] = (color1 >> 24) & 0xFF;
	argb1[1] = (color1 >> 16) & 0xFF;
	argb1[2] = (color1 >> 8) & 0xFF;
	argb1[3] = (color1 >> 0) & 0xFF;
	argb2[0] = (color2 >> 24) & 0xFF;
	argb2[1] = (color2 >> 16) & 0xFF;
	argb2[2] = (color2 >> 8) & 0xFF;
	argb2[3] = (color2 >> 0) & 0xFF;
	argb[0] = (int)((1.0 - t) * argb1[0] + t * argb2[0]);
	argb[1] = (int)((1.0 - t) * argb1[1] + t * argb2[1]);
	argb[2] = (int)((1.0 - t) * argb1[2] + t * argb2[2]);
	argb[3] = (int)((1.0 - t) * argb1[3] + t * argb2[3]);
	x = ((argb[0] & 0xFF) << 24) | ((argb[1] & 0xFF) << 16);
	return (x | ((argb[2] & 0xFF) << 8) | (argb[3] & 0xFF));
}

t_pixel	*get_pixel_at(t_matrix *matrix, int y, int x)
{
	t_pixel	*pixel;
	int		i;

	i = 0;
	while (y > 0 && matrix)
	{
		matrix = matrix->next;
		y--;
	}
	if (!matrix)
		return (NULL);
	pixel = matrix->node;
	while (i < x && pixel)
	{
		pixel = pixel->next;
		i++;
	}
	return (pixel);
}
