/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:17:50 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/28 17:15:56 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

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
	double			ang;
	int				matrix_width;
	int				matrix_height;
	int				scale;
	double			height_scale;
	int				z_min;
	int				z_max;
	double			x_ang;
	double			y_ang;
	double			z_ang;
	bool			x_moved;
	bool			y_moved;
	bool			z_moved;
	int				offset_x;
	int				offset_y;
	double			zoom;
	void			*img;
	char			*img_data;
	int				bpp;
	int				line_len;
	int				endian;
}					t_fdf;

/* parse_c */
int					validate_file_type(char *file);
int					validate(int argc, char *file, int *width, int *height);
int					validate_map(char *file, int *width, int *height);

/* init_matrix_c */
void				init_matrix(t_fdf **fdf, int fd);
void				handle_error_and_exit(t_fdf **fdf, int fd);
void				add_row_to_matrix_and_update(t_fdf **fdf, t_pixel **row,
						int row_width, int y);
t_pixel				*process_line(t_fdf **fdf, char *str, int y,
						int *row_width);
/* init_pixel_c */
t_pixel				*new_pixel(int x, int y, int z);
int					add_to_back(t_pixel **row, int x, int y, char *z);

/* free_c */
void				free_pixel_row(t_pixel *p);
void				free_matrix(t_matrix *m);
void				free_split(char **arr);
void				free_fdf(t_fdf **fdf);
void				clear_gnl(int fd);
/* pixel_gen_c */
void				put_matrix(t_fdf **fdf);
int					gradient_color(int color1, int color2, int step, int total);
void				img_pixel_put(t_fdf *fdf, int x, int y, int color);
void				drawline(t_fdf **fdf, int sxy[4], int color1, int color2);
t_pixel				*get_pixel_at(t_matrix *matrix, int y, int x);

/* scaling_c */
void				set_scaling(t_fdf **fdf);
int					zoom_scaling(int button, int x, int y, void *param);

/* window_c */
void				init_window(t_fdf **fdf);
/*rotate_c*/
void				rotate_x(double *y, double *z, double alpha_deg);
void				rotate_y(double *x, double *z, double theta_deg);
void				rotate_z(double *x, double *y, double gamma_deg);
void				project_iso(t_pixel *node, t_fdf **fdf, int *sx, int *sy);
void				project_iso_raw(t_pixel *node, t_fdf **fdf, int *px,
						int *py);
/*movement_c*/
int					move_x_axis(int keycode, void *param);
int					move_y_axis(int keycode, void *param);
int					move_z_axis(int keycode, void *param);
int					change_height_scale(int keycode, void *param);

/*offset_c*/
void				compute_center_offsets(t_fdf **fdf);
#endif // FDF_H
