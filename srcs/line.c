/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:17:11 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/15 09:22:44 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	draw_line(t_meta *data, t_point start, t_point end)
{
	int		pixels;
	int		len;
	t_point	delta;
	t_point	pixel;

	if (!in_bounds(start) && !in_bounds(end))
		return (0);
	delta.pos[X] = end.pos[X] - start.pos[X];
	delta.pos[Y] = end.pos[Y] - start.pos[Y];
	pixels = sqrt((delta.pos[X] * delta.pos[X]) + \
		(delta.pos[Y] * delta.pos[Y]));
	len = pixels;
	delta.pos[X] /= pixels;
	delta.pos[Y] /= pixels;
	pixel.pos[X] = start.pos[X];
	pixel.pos[Y] = start.pos[Y];
	while (pixels > 0)
	{
		pixel.color = get_gradient(start.color, end.color, len, len - pixels);
		my_mlx_pixel_put(data, pixel);
		pixel.pos[X] += delta.pos[X];
		pixel.pos[Y] += delta.pos[Y];
		pixels--;
	}
	return (1);
}

void	create_wire(t_meta *data, t_point *arr, int density, int line)
{
	int	i;
	int	x_end;
	int	y_end;

	i = 0;
	while (i < (int)data->map.size.pos[X])
	{
		x_end = i + density;
		if (x_end > (int)data->map.size.pos[X])
			x_end = (int)data->map.size.pos[X] - 1;
		y_end = i + (int)data->map.size.pos[X] * density;
		if (arr[i].paint)
		{
			if (x_end != (int)data->map.size.pos[X])
				draw_line(data, arr[i], arr[x_end]);
			if (line + density < (int)data->map.size.pos[Y])
				draw_line(data, arr[i], arr[y_end]);
		}
		i += density;
	}
}

void	connect_points(t_meta *data, t_point *arr)
{
	int	i;
	int	density;

	i = 0;
	density = 8 / data->map.scale;
	if (density == 0)
		density++;
	while (i < data->map.num_points)
	{
		create_wire(data, &arr[i], density, i / data->map.size.pos[X]);
		i += (data->map.size.pos[X] * density);
	}
}
