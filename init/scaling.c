/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:23:08 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/23 20:58:13 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	set_scaling(int button, int x, int y, void *param)
{
	t_fdf	*fdf;

	(void)x;
	(void)y;
	fdf = (t_fdf *)param;
	if (!fdf)
		return (0);
	if (button == 4)
	{
		ft_printf("up\n");
		fdf->scale = fdf->scale + (fdf->scale / 20);
	}
	else if (button == 5)
	{
		ft_printf("down\n");
		fdf->scale = fdf->scale - (fdf->scale / 20);
	}
	put_matrix(&fdf);
	return (0);
}
