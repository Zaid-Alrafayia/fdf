/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 00:38:42 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/23 20:58:04 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	fdf->win_height = 900;
	fdf->win_width = 900;
	fdf->mlx = NULL;
	fdf->mlx_win = NULL;
	fdf->matrix = NULL;
	fdf->matrix_height = 0;
	fdf->matrix_width = 0;
	fdf->color = 0xFFFFFF;
	fdf->scale = 1;
	fdf->height_scale = 5;
	fdf->z_min = INT_MAX;
	fdf->z_max = INT_MIN;
	fdf->x_ang = 6.0;
	return (fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	int		fd;

	fdf = init_fdf();
	validate(argc, argv[1], &fdf->matrix_width, &fdf->matrix_height);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("file not found");
		return (1);
	}
	init_matrix(&fdf, fd);
	set_scaling(&fdf);
	init_window(&fdf);
	free_matrix(fdf->matrix);
	return (0);
}
