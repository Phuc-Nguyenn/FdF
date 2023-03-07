/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:55:29 by phunguye          #+#    #+#             */
/*   Updated: 2023/01/04 15:42:55 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../FdF.h"

void	put_points(t_line *line, int *x_pixel, int *y_pixel, t_img img)
{
	int	e2;

	e2 = line->error;
	if (e2 > -line->dy)
	{
		line->error -= line->dy;
		*x_pixel += line->x_step;
	}
	if (e2 < line->dx)
	{
		line->error += line->dx;
		*y_pixel += line->y_step;
	}
	if (*x_pixel >= 0 && *y_pixel >= 0
		&& *x_pixel < W_WIDTH && *y_pixel < W_HEIGHT)
		my_pixel_put(&img, *x_pixel, *y_pixel, (int)0x00FFFFFF);
}

void	draw_line(t_img img, t_coordinate p1, t_coordinate p2)
{
	t_line	line;
	int		x_pixel;
	int		y_pixel;

	line.dx = abs(p2.display_x - p1.display_x);
	line.dy = abs(p2.display_y - p1.display_y);
	line.error = line.dx - line.dy;
	x_pixel = p1.display_x;
	y_pixel = p1.display_y;
	line.x_step = -1;
	if (p1.display_x < p2.display_x)
		line.x_step = 1;
	line.y_step = -1;
	if (p1.display_y < p2.display_y)
		line.y_step = 1;
	if (x_pixel >= 0 && y_pixel >= 0 && x_pixel < W_WIDTH && y_pixel < W_HEIGHT)
		my_pixel_put(&img, x_pixel, y_pixel, (int)0x00FFFFFF);
	while (x_pixel != p2.display_x || y_pixel != p2.display_y)
		put_points(&line, &x_pixel, &y_pixel, img);
}
