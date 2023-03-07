/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:18:56 by phunguye          #+#    #+#             */
/*   Updated: 2023/01/04 15:30:44 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../FdF.h"

void	clear_screen(t_img img)
{
	int	x;
	int	y;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
			my_pixel_put(&img, x++, y, BACKGROUND);
		y++;
	}
}

void	ft_fdf(t_fdf *fdf)
{	
	clear_screen(fdf->img);
	calculate_projection_xy(&(fdf->points_array), fdf->data.x_width,
		fdf->data.y_height, fdf->data);
	project_isometric(fdf->points_array, fdf->img, fdf->data);
	mlx_put_image_to_window(fdf->mlx.mlx_ptr,
		fdf->mlx.wdw_ptr, fdf->img.img_ptr, 0, 0);
}

void	if_esc(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESCAPE)
	{
		mlx_destroy_window(fdf->mlx.mlx_ptr, fdf->mlx.wdw_ptr);
		free(fdf->mlx.mlx_ptr);
		free(fdf->img.img_ptr);
		exit(0);
	}
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ANSI_A)
		fdf->data.view.trans_hori += 100;
	if (keycode == KEY_ANSI_D)
		fdf->data.view.trans_hori -= 100;
	if (keycode == KEY_ANSI_W)
		fdf->data.view.trans_vert += 100;
	if (keycode == KEY_ANSI_S)
		fdf->data.view.trans_vert -= 100;
	if (keycode == KEY_ANSI_Z)
		fdf->data.view.zoom += 2;
	if (keycode == KEY_ANSI_X)
		fdf->data.view.zoom -= 2;
	if (keycode == KEY_ANSI_V)
		fdf->data.view.v_perspect += 0.1;
	if (keycode == KEY_ANSI_B && fdf->data.view.v_perspect >= 0.2)
		fdf->data.view.v_perspect -= 0.1;
	if (keycode == KEY_ANSI_E && fdf->data.view.z_dilation >= 0.3)
		fdf->data.view.z_dilation -= 0.2;
	if (keycode == KEY_ANSI_Q)
		fdf->data.view.z_dilation += 0.2;
	if_esc(keycode, fdf);
	ft_fdf(fdf);
	return (0);
}

void	view_set(t_fdf *fdf)
{
	fdf->data.view.v_perspect = 1;
	fdf->data.view.z_dilation = 1;
}
