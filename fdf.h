/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:17:50 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/21 14:35:49 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_pixel
{
	int				x;
	int				y;
	int				z;
	int				color;
	struct s_pixel	*next;
}					t_pixel;

typedef struct s_matrix
{
	t_pixel			*node;
	struct s_matrix	*next;
}					t_matrix;
// parse_c
int					validate_file_type(char *file);
int					validate_map(char *file);
int					validate(int argc, char *file);

// init_matrix_c
void				init_matrix(t_matrix **matrix, int fd);

// init_pixel_c
t_pixel				*new_pixel(int x, int y, int z);
int					add_to_back(t_pixel **row, int x, int y, char *z);

// free_c
void				free_pixel_row(t_pixel *p);
void				free_matrix(t_matrix *m);
void				free_split(char **arr);
#endif // !FDF_H
