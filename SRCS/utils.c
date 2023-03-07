/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:14:19 by phunguye          #+#    #+#             */
/*   Updated: 2022/12/11 15:14:19 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../FdF.h"

void	change_pixel_colour(char	*pixel_addr, int colour)
{
	pixel_addr[0] = (colour);
	pixel_addr[1] = (colour >> 8);
	pixel_addr[2] = (colour >> 16);
	pixel_addr[3] = (colour >> 24);
}

void	initialise_mlx(t_mlx	*mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->wdw_ptr = mlx_new_window(mlx->mlx_ptr, W_WIDTH, W_HEIGHT, "FdF");
}

void	initialise_img(t_img *img, t_mlx *mlx)
{
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, W_WIDTH, W_HEIGHT);
	img->string = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
			&img->size_string, &img->endian);
}

void	my_pixel_put(t_img *img, int x, int y, int colour)
{
	int	pixel;

	pixel = (img->size_string * y) + (x * 4);
	if (pixel >= 0 && pixel <= W_WIDTH * W_HEIGHT * 4)
		change_pixel_colour(&img->string[pixel], colour);
}
