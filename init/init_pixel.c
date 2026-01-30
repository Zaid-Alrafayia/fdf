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

#include "../fdf.h"

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
	node->color = 0;
	node->next = NULL;
	return (node);
}

static int	parse_color_and_value(char *z, int *color, int *value)
{
	char	*comma;

	*color = 0xFFFFFF;
	comma = ft_strchr(z, ',');
	if (comma)
	{
		*color = (int)ft_hexatoi(comma + 1);
		*comma = '\0';
	}
	*value = ft_atoi(z);
	return (0);
}

static int	get_color_by_height(t_fdf *fdf, int value)
{
	double	t;
	double	loc;
	int		step;

	if (!fdf || fdf->z_max == fdf->z_min)
		return (0x228B22); /* fallback: forest green */
	t = (double)(value - fdf->z_min) / (double)(fdf->z_max - fdf->z_min);
	if (t < 0.0)
		t = 0.0;
	if (t > 1.0)
		t = 1.0;
	if (t < 0.20)
	{
		/* deep -> shallow water: dark blue to light blue */
		loc = t / 0.20;
		step = (int)(loc * 1000.0);
		return (gradient_color(0x000080, 0x1E90FF, step, 1000));
	}
	if (t < 0.25)
	{
		/* beach/sand */
		loc = (t - 0.20) / 0.05;
		step = (int)(loc * 1000.0);
		return (gradient_color(0x1E90FF, 0xF4A460, step, 1000));
	}
	if (t < 0.50)
	{
		/* lowland -> vegetation green */
		loc = (t - 0.25) / 0.25;
		step = (int)(loc * 1000.0);
		return (gradient_color(0x228B22, 0x006400, step, 1000));
	}
	if (t < 0.70)
	{
		/* hills -> brown */
		loc = (t - 0.50) / 0.20;
		step = (int)(loc * 1000.0);
		return (gradient_color(0x8B7765, 0x8B4513, step, 1000));
	}
	if (t < 0.90)
	{
		/* mountain rock */
		loc = (t - 0.70) / 0.20;
		step = (int)(loc * 1000.0);
		return (gradient_color(0xA9A9A9, 0x808080, step, 1000));
	}
	/* high peaks -> snow */
	loc = (t - 0.90) / 0.10;
	step = (int)(loc * 1000.0);
	return (gradient_color(0xFFFFFF, 0xFFFFFF, step, 1000));
}

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
	if (color == 0xFFFFFF)
		tmp->color = get_color_by_height(fdf, value);
	else
		tmp->color = color;
	return (append_pixel(row, tmp));
}
