/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:32:00 by phunguye          #+#    #+#             */
/*   Updated: 2023/01/04 15:32:13 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../FdF.h"

void	calculate_projection_xy(t_coordinate **points_array, int x_width,
													int y_height, t_data data)
{
	int				array_index;
	int				number_of_points;
	t_coordinate	pt;

	number_of_points = x_width * y_height;
	array_index = 0;
	while (array_index < number_of_points)
	{
		pt = points_array[0][array_index];
		pt.project_x = (pt.x - pt.y) / sqrt (2);
		pt.project_y = (pt.x + (2 * pt.y) - pt.z / data.view.z_dilation)
			/ sqrt (6);
		points_array[0][array_index++] = pt;
	}
}

void	project_isometric(t_coordinate	*points_array, t_img img, t_data data)
{
	int	index;
	int	zoom;
	int	x;
	int	y;

	index = 0;
	zoom = 1600 / sqrt(data.number_of_points);
	zoom += data.view.zoom;
	while (index < data.number_of_points)
	{
		x = points_array[index].project_x * zoom;
		y = points_array[index].project_y / data.view.v_perspect * zoom;
		x += data.view.trans_hori;
		y += data.view.trans_vert;
		points_array[index].display_x = x;
		points_array[index].display_y = y;
		if (index >= 1 && index % data.x_width)
			draw_line(img, points_array[index], points_array[index - 1]);
		if (index >= data.x_width)
			draw_line(img, points_array[index],
				points_array[index - data.x_width]);
		index++;
	}
}
