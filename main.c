/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 00:38:42 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/21 14:51:40 by zaalrafa         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_matrix	*matrix;
	int			fd;

	validate(argc, argv[1]);
	matrix = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("file not found");
		return (1);
	}
	init_matrix(&matrix, fd);
	close(fd);
	free_matrix(matrix);
	return (0);
}
