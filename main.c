/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 00:38:42 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/22 16:39:04 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <stdio.h>

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

int	main(int argc, char **argv)
{
	t_matrix	*matrix;
	int			fd;
	void		*mlx;
	void		*mlx_win;
	int			xy[2];
	xy[0] = 1080;
	xy[1] = 900;
	mlx = mlx_init();
	if (!mlx)
	{
		perror("ERROR: can't make window.\n");
		return (0);
	}
	validate(argc, argv[1]);
	matrix = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("file not found");
		return (1);
	}
	init_matrix(&matrix, fd);
	mlx_win = mlx_new_window(mlx, xy[0], xy[1], argv[1]);
	print_matrix(matrix);
	put_matrix(&matrix, mlx, mlx_win);
	free_matrix(matrix);
	mlx_loop(mlx);
	return (0);
}
