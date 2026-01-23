/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:17:50 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/22 21:27:08 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
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
typedef struct s_fdf
{
	void			*mlx;
	void			*mlx_win;
	t_matrix		*matrix;
	int				win_width;
	int				win_height;
	int				color;
	int				matrix_width;
	int				matrix_height;
	int				scale;
	int				height_scale;
	int				z_min;
	int				z_max;
}					t_fdf;

// parse_c
int					validate_file_type(char *file);
int					validate(int argc, char *file, int *width, int *height);
int					validate_map(char *file, int *width, int *height);

// init_matrix_c
void				init_matrix(t_fdf **fdf, int fd);

// init_pixel_c
t_pixel				*new_pixel(int x, int y, int z);
int					add_to_back(t_pixel **row, int x, int y, char *z);

// free_c
void				free_pixel_row(t_pixel *p);
void				free_matrix(t_matrix *m);
void				free_split(char **arr);

// pixel_gen_c
void				put_matrix(t_fdf **fdf);
// scaling_c
int					set_scaling(t_fdf **fdf, int keycode);

// window_c
void				init_window(t_fdf **fdf);
#endif // !FDF_H
