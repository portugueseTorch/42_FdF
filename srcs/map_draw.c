/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:18:39 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/13 11:28:54 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	draw_background(t_meta *data)
{
	int		color;
	int		i;
	int		j;
	int		index;

	j = 0;
	while (j < WINDOW_HEIGHT)
	{
		i = 0;
		while (i < WINDOW_WIDTH)
		{
			color = get_color(data, data->map.colors.background);
			index = (j * data->img.line_length) + (i * 4);
			color_bytes(&data->img.address[index], data->img.endian, color, 1);
			i++;
		}
		j++;
	}
}

static void	fit_screen(t_meta *data, t_point *arr)
{
	data->map.origin.pos[X] = WINDOW_WIDTH / 2;
	data->map.origin.pos[Y] = WINDOW_HEIGHT / 2;
	data->map.origin.pos[Z] = 0;
	data->map.scale = 1;
	copy_map(data->map.points, arr, data->map.num_points);
	translate_map(data, arr);
	while (!(limits(arr, data->map.num_points)))
	{
		copy_map(data->map.points, arr, data->map.num_points);
		translate_map(data, arr);
		data->map.scale += 0.2;
	}
}

int	draw_map(t_meta *data, int fit)
{	
	t_point	*temp;

	temp = malloc(sizeof(t_point) * data->map.num_points);
	if (!temp)
		err_handler(MEMORY, data);
	if (data->img.img_ptr)
	{
		mlx_destroy_image(data->vars.mlx, data->img.img_ptr);
		data->img.img_ptr = mlx_new_image(data->vars.mlx, WINDOW_WIDTH, \
		WINDOW_HEIGHT);
		if (!data->img.img_ptr)
			err_handler(BOOTING, data);
	}
	draw_background(data);
	copy_map(data->map.points, temp, data->map.num_points);
	translate_map(data, temp);
	if (fit)
		fit_screen(data, temp);
	connect_points(data, temp);
	mlx_put_image_to_window(data->vars.mlx, data->vars.win, \
		data->img.img_ptr, 0, 0);
	free(temp);
	return (0);
}
