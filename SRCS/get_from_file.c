/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 22:08:42 by phunguye          #+#    #+#             */
/*   Updated: 2022/12/10 22:08:42 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../FdF.h"

char	*get_dimensions(int	*x_width, int *y_height, char *file_name)
{
	char	*temporary_line;
	int		temporary_y;
	int		file_descriptor;
	char	*file_contents;

	file_descriptor = open(file_name, O_RDONLY);
	temporary_y = 0;
	temporary_line = "c";
	while (temporary_line != NULL)
	{
		temporary_line = get_next_line(file_descriptor);
		if (temporary_line == NULL)
			break ;
		*x_width = ft_wordcount(temporary_line, ' ');
		if (temporary_y == 0)
			file_contents = strdup(temporary_line);
		else
		{
			file_contents = ft_strjoin(file_contents, " ");
			file_contents = ft_strjoin(file_contents, temporary_line);
		}
		temporary_y++;
	}
	*y_height = temporary_y;
	return (file_contents);
}

t_coordinate	*get_all_xy(t_coordinate **points_array, char *file_contents,
		int x_max, int y_max)
{
	int	array_index;
	int	x_value;
	int	y_value;

	array_index = 0;
	y_value = 0;
	while (y_value < y_max)
	{
		x_value = 0;
		while (x_value < x_max)
		{
			points_array[0][array_index].x = x_value++;
			points_array[0][array_index++].y = y_value;
		}
		y_value++;
	}
	return (*points_array);
}

t_coordinate	*get_all_z(t_coordinate **points_array,
		char *file_contents, int x_max, int y_max)
{
	size_t	word_len;
	int		array_index;

	array_index = 0;
	while (*file_contents)
	{
		while (*file_contents == ' ' && *file_contents)
			file_contents++;
		if (*file_contents)
		{
			if (!ft_strchr(file_contents, ' '))
				word_len = ft_strlen(file_contents);
			else
				word_len = ft_strchr(file_contents, ' ') - file_contents;
			points_array[0][array_index++].z = ft_atoi(
					ft_substr(file_contents, 0, word_len));
			file_contents += word_len;
		}
	}
	return (*points_array);
}

t_coordinate	*get_coordinates(char *file_name, t_data *data)
{
	t_coordinate	*points_array;
	char			*file_contents;
	int				x_width;
	int				y_height;

	file_contents = get_dimensions(&x_width, &y_height, file_name);
	data->number_of_points = x_width * y_height;
	data->x_width = x_width;
	data->y_height = y_height;
	points_array = (t_coordinate *)malloc((x_width * y_height)
			*sizeof(t_coordinate));
	get_all_xy(&points_array, file_contents, x_width, y_height);
	get_all_z(&points_array, file_contents, x_width, y_height);
	return (points_array);
}
