/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:34:07 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/22 17:47:27 by zaalrafa         ###   ########.fr       */
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



int	add_to_back(t_pixel **row, int x, int y, char *z)
{
	t_pixel	*tmp;
	t_pixel	*tail;
	int		color = 0xf23f23;

	if (ft_strrchr(z, ','))
	{
		char	*color_str = ft_strrchr(z, ',') + 1;
		color = (int)ft_hexatoi(color_str);
		z[ft_strchr(z, ',') - z] = '\0';
		if (check_overflow(ft_atoi(z)))
			return (1);
		tmp = new_pixel(x, y, ft_atoi(z));
		if (!tmp)
			return (1);
		tmp->color = color;
	}
	if (check_overflow(ft_atoi(z)) || !row)
		return (1);
	tmp = new_pixel(x, y, ft_atoi(z));
	tmp->color = color;
	if (!*row)
	{
		*row = tmp;
		return (0);
	}
	tail = (*row);
	while (tail->next)
		tail = tail->next;
	tail->next = tmp;
	return (0);
}
