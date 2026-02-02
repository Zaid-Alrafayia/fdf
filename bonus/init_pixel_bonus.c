/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:34:07 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/28 17:18:09 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_bonus.h"

static int	check_overflow(int num)
{
	if (num > INT_MAX || num < INT_MIN)
	{
		return (1);
	}
	return (0);
}

t_pixel	*new_pixel(int x, int y, int z)
{
	t_pixel	*node;

	node = malloc(sizeof(t_pixel));
	if (!node)
		return (NULL);
	node->x = x;
	node->y = y;
	node->z = z;
	node->color = -1;
	node->next = NULL;
	return (node);
}

static int	parse_color_and_value(char *z, int *color, int *value)
{
	char	*comma;

	*color = -1;
	comma = ft_strchr(z, ',');
	if (comma)
	{
		*color = (int)ft_hexatoi(comma + 1);
		*comma = '\0';
	}
	*value = ft_atoi(z);
	return (0);
}

// static int	get_color_from_height(t_fdf *fdf, int value)
// {
// 	int	stops[5];
// 	double	ratio;
// 	int	n;
// 	int	seg;
// 	double	local_ratio;
// 	int	step;
// 	int	total;

// 	stops[0] = 0x0000FF; /* blue */
// 	stops[1] = 0x800080; /* purple */
// 	stops[2] = 0xFFFF00; /* yellow */
// 	stops[3] = 0xFFBA00; /* orange */	
// 	stops[4] = 0xFF0000; /* red */

// 	if (fdf->z_max == fdf->z_min)
// 		return (stops[4]);
// 	ratio = (double)(value - fdf->z_min) / (double)(fdf->z_max - fdf->z_min);
// 	if (ratio < 0.0)
// 		ratio = 0.0;
// 	if (ratio > 1.0)
// 		ratio = 1.0;
// 	n = 5; /* number of stops */
// 	seg = (int)(ratio * (n - 1));
// 	if (seg >= n - 1)
// 		return (stops[n - 1]);
// 	local_ratio = (ratio - ((double)seg / (n - 1))) * (n - 1);
// 	step = (int)(local_ratio * 1000.0);
// 	total = 1000;
// 	return (gradient_color(stops[seg], stops[seg + 1], step, total));
// }



static int	append_pixel(t_pixel **row, t_pixel *tmp)
{
	t_pixel	*tail;

	if (!*row)
	{
		*row = tmp;
		return (0);
	}
	tail = *row;
	while (tail->next)
		tail = tail->next;
	tail->next = tmp;
	return (0);
}

int	add_to_back(t_fdf *fdf, t_pixel **row, int x, int y, char *z)
{
	t_pixel	*tmp;
	int		color;
	int		value;

	if (!fdf || !row || !z)
		return (1);
	parse_color_and_value(z, &color, &value);
	if (check_overflow(value))
		return (1);
	(void)x;
	(void)y;
	tmp = new_pixel(x, y, value);
	if (!tmp)
		return (1);
	tmp->color = color;
	return (append_pixel(row, tmp));
}
