/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 00:38:42 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/22 21:30:53 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	print_pixel_row(t_pixel *p)
{
	if (!p)
	{
		printf("(empty row)\n");
		return ;
	}
	while (p)
	{
		printf(" %d ", p->z);
		p = p->next;
	}
	printf("\n");
}

void	print_matrix(t_matrix *m)
{
	size_t	row;

	row = 0;
	if (!m)
	{
		printf("matrix: (empty)\n");
		return ;
	}
	while (m)
	{
		printf("row %zu: ", row++);
		print_pixel_row(m->node);
		m = m->next;
	}
}

t_fdf	*init_fdf(void)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->win_height = 1080;
	fdf->win_width = 900;
	fdf->mlx = NULL;
	fdf->mlx_win = NULL;
	fdf->matrix = NULL;
	fdf->matrix_height = 0;
	fdf->matrix_width = 0;
	fdf->color = 0xFFFFFF;
	fdf->scale = 5;
	fdf->height_scale = 5;
	fdf->z_min = INT_MAX;
	fdf->z_max = INT_MIN;
	return (fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	int		fd;

	fdf = init_fdf();
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
	{
		perror("ERROR: can't make window.\n");
		return (0);
	}
	validate(argc, argv[1], &fdf->matrix_width, &fdf->matrix_height);
	ft_printf("width= %d\nheight= %d", fdf->matrix_width, fdf->matrix_height);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("file not found");
		return (1);
	}
	init_matrix(&fdf, fd);
	set_scaling(&fdf);
	fdf->mlx_win = mlx_new_window(fdf->mlx, fdf->win_width, fdf->win_height,
			argv[1]);
	put_matrix(&fdf);
	free_matrix(fdf->matrix);
	mlx_loop(fdf->mlx);
	return (0);
}
