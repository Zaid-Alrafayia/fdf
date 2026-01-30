/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 00:38:42 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/29 15:09:23 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_fdf	*init_fdf(void)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)calloc(1, sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->win_height = 900;
	fdf->win_width = 1200;
	fdf->mlx = NULL;
	fdf->mlx_win = NULL;
	fdf->matrix = NULL;
	fdf->matrix_height = 0;
	fdf->matrix_width = 0;
	fdf->ang = M_PI / 6;
	fdf->scale = 1;
	fdf->height_scale = 2.0;
	fdf->z_min = INT_MAX;
	fdf->z_max = INT_MIN;
	return (fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	int		fd;

	fdf = init_fdf();
	if (!fdf || argc != 2)
	{
		free(fdf);
		return (1);
	}
	if (!validate(argc, argv[1], &fdf->matrix_width, &fdf->matrix_height))
	{
		free(fdf);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("file not found");
		return (1);
	}
	init_matrix(&fdf, fd);
	set_scaling(&fdf);
	init_window(&fdf);
	free_fdf(&fdf);
	return (0);
}
