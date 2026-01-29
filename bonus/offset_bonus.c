/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:55:36 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/28 12:57:17 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../fdf_bonus.h"

static void	init_minmax(int minxy[2], int maxxy[2])
{
	minxy[0] = INT_MAX;
	minxy[1] = INT_MAX;
	maxxy[0] = INT_MIN;
	maxxy[1] = INT_MIN;
}

static void	scan_matrix_minmax(t_fdf **fdf, int minxy[2], int maxxy[2],
		int xy[2])
{
	int		pxy[2];
	t_pixel	*curr;

	while (xy[1] < (*fdf)->matrix_height)
	{
		xy[0] = 0;
		while (xy[0] < (*fdf)->matrix_width)
		{
			curr = get_pixel_at((*fdf)->matrix, xy[1], xy[0]);
			if (curr)
			{
				project_iso_raw(curr, fdf, &pxy[0], &pxy[1]);
				if (pxy[0] < minxy[0])
					minxy[0] = pxy[0];
				if (pxy[1] < minxy[1])
					minxy[1] = pxy[1];
				if (pxy[0] > maxxy[0])
					maxxy[0] = pxy[0];
				if (pxy[1] > maxxy[1])
					maxxy[1] = pxy[1];
			}
			xy[0]++;
		}
		xy[1]++;
	}
}

static void	apply_center_offsets(t_fdf **fdf, int minxy[2], int maxxy[2])
{
	if (minxy[0] == INT_MAX || minxy[1] == INT_MAX)
	{
		(*fdf)->offset_x = (*fdf)->win_width / 2;
		(*fdf)->offset_y = (*fdf)->win_height / 2;
		return ;
	}
	(*fdf)->offset_x = (*fdf)->win_width / 2 - ((minxy[0] + maxxy[0]) / 2);
	(*fdf)->offset_y = (*fdf)->win_height / 2 - ((minxy[1] + maxxy[1]) / 2);
}

void	compute_center_offsets(t_fdf **fdf)
{
	int	minxy[2];
	int	maxxy[2];
	int	xy[2];

	xy[1] = 0;
	init_minmax(minxy, maxxy);
	scan_matrix_minmax(fdf, minxy, maxxy, xy);
	apply_center_offsets(fdf, minxy, maxxy);
}
