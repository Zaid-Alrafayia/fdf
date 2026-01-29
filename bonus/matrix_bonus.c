/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:13:25 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/28 17:13:36 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../fdf_bonus.h"

void	init_matrix(t_fdf **fdf, int fd)
{
	char	*str;
	t_pixel	*row;
	int		y;
	int		row_width;

	y = 0;
	row_width = 0;
	row = NULL;
	str = get_next_line(fd);
	if (!str)
		handle_error_and_exit(fdf, fd);
	while (str)
	{
		row = process_line(fdf, str, y, &row_width);
		free(str);
		str = NULL;
		if (!row)
			handle_error_and_exit(fdf, fd);
		add_row_to_matrix_and_update(fdf, &row, row_width, y);
		y++;
		str = get_next_line(fd);
	}
	(*fdf)->matrix_height = y;
	close(fd);
}
