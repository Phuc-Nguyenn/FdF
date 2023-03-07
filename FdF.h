/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:16:56 by phunguye          #+#    #+#             */
/*   Updated: 2022/12/07 23:16:56 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include "./minilibx/mlx.h"
# include "./key.h"

# define W_HEIGHT 1440
# define W_WIDTH 2560

# define WHITE 0xFFFFFF
# define BACKGROUND 0x000026

//to delete:
# include <stdio.h>

typedef struct s_coordinate
{
	int		x;
	int		y;
	int		z;
	float	project_x;
	float	project_y;
	int		display_x;
	int		display_y;
	int		colour;
}	t_coordinate;

typedef struct s_view
{
	int		rotate_x;
	int		rotate_y;
	int		rotate_z;
	int		trans_hori;
	int		trans_vert;
	float	v_perspect;
	float	z_dilation;
	int		zoom;
}	t_view;

typedef struct s_data
{
	int		number_of_points;
	int		x_width;
	int		y_height;
	int		z_max;
	t_view	view;
}	t_data;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*wdw_ptr;
	char	*title;
	char	*file_name;
}	t_mlx;

typedef struct s_img
{
	void	*img_ptr;
	char	*string;
	int		bits_per_pixel;
	int		size_string;
	int		endian;
}	t_img;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	error;
	int	x_step;
	int	y_step;
}	t_line;

typedef struct s_fdf
{
	t_coordinate	*points_array;
	t_mlx			mlx;
	t_img			img;
	t_data			data;
}	t_fdf;

//get_from_file.c
char			*get_dimensions(int	*x_width, int	*y_height, char	*file_name);
t_coordinate	*get_all_xy(t_coordinate **points_array,
					char *file_contents, int x_max, int y_max);
t_coordinate	*get_all_z(t_coordinate **points_array,
					char *file_contents, int x_max, int y_max);
t_coordinate	*get_coordinates(char *file_name, t_data *data);

//utils.c
void			change_pixel_colour(char	*pixel_addr, int colour);
void			draw_line(t_img img, t_coordinate p1, t_coordinate p2);
	// --> initialise
void			initialise_img(t_img *img, t_mlx *mlx);
void			initialise_mlx(t_mlx	*mlx);
void			my_pixel_put(t_img *img, int x, int y, int colour);

//fdf.c
void			clear_screen(t_img img);
void			ft_fdf(t_fdf *fdf);
void			if_esc(int keycode, t_fdf *fdf);
int				key_hook(int keycode, t_fdf *fdf);
void			view_set(t_fdf *fdf);
void			project_isometric(t_coordinate	*points_array,
					t_img img, t_data data);
void			calculate_projection_xy(t_coordinate **points_array,
					int x_width, int y_height, t_data data);

#endif