/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 08:45:35 by phunguye          #+#    #+#             */
/*   Updated: 2022/12/08 08:45:35 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../FdF.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	char	*file_name;
	int		status;

	if (argc != 2)
	{
		ft_putstr_fd("Input error\n./[program] [file_name]\n", 1);
		return (-1);
	}
	view_set(&fdf);
	file_name = ft_strdup(argv[1]);
	fdf.points_array = get_coordinates(file_name, &(fdf.data));
	initialise_mlx(&(fdf.mlx));
	initialise_img(&(fdf.img), &(fdf.mlx));
	ft_fdf(&fdf);
	mlx_key_hook(fdf.mlx.wdw_ptr, key_hook, &fdf);
	mlx_hook(fdf.mlx.wdw_ptr, 17, 0, (void *)exit, 0);
	mlx_loop(fdf.mlx.mlx_ptr);
}
