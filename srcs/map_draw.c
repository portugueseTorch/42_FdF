/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:18:39 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/03 16:04:25 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	get_color(t_meta *data, int color)
{
	if (data->img.bpp != 32)
		color = mlx_get_color_value(data->vars.mlx, color);
	return (color);
}

void	color_bytes(char *img, int endian, int color, int a)
{
	if (endian == 0)
	{
		img[0] = color & 0xFF;
		img[1] = (color >> 8) & 0xFF;
		img[2] = (color >> 16) & 0xFF;
		img[3] = a;
	}
	else
	{
		img[0] = a;
		img[1] = (color >> 16) & 0xFF;
		img[2] = (color >> 8) & 0xFF;
		img[3] = color & 0xFF;
	}
}

int	my_mlx_pixel_put(t_meta *data, t_point point)
{
	int	index;
	int	a;
	int	color;

	a = 0;
	if (point.pos[X] < MENU_WIDTH)
		a = 1;
	if (!in_bounds(point))
		return (-1);
	index = ((int)point.pos[Y] * WINDOW_WIDTH * 4) + ((int)point.pos[X] * 4);
	color = get_color(data, point.color);
	point.color = color;
	color_bytes(&data->img.address[index], data->img.endian, point.color, a);
	return (0);
}

void	draw_background(t_meta *data)
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
			if (i < MENU_WIDTH)
				color = get_color(data, data->map.colors.menu);
			else
				color = get_color(data, data->map.colors.background);
			index = (j * data->img.line_length) + (i * 4);
			color_bytes(&data->img.address[index], data->img.endian, color, 1);
			i++;
		}
		j++;
	}
}

void	resize_z(t_map *map, t_point *arr)
{
	int	i;

	i = 0;
	while (i < map->num_points)
	{
		arr[i].pos[Z] /= map->resize;
		i++;
	}
}

void	rotate_x(t_point *original, t_point *transformed, float angle, int len)
{
	float	matrix[3][3];
	int		i;

	i = 0;
	matrix_bzero(matrix);
	matrix[0][0] = 1;
	matrix[1][1] = cos(deg_to_rad(angle));
	matrix[2][2] = cos(deg_to_rad(angle));
	matrix[2][1] = sin(deg_to_rad(angle));
	matrix[1][2] = -sin(deg_to_rad(angle));
	while (i < len)
	{
		transformed[i] = multiply_matrix(matrix, original[i]);
		i++;
	}
}

void	rotate_y(t_point *original, t_point *transformed, float angle, int len)
{
	float	matrix[3][3];
	int		i;

	i = 0;
	matrix_bzero(matrix);
	matrix[0][0] = cos(deg_to_rad(angle));
	matrix[1][1] = 1;
	matrix[2][2] = cos(deg_to_rad(angle));
	matrix[2][0] = -sin(deg_to_rad(angle));
	matrix[0][2] = sin(deg_to_rad(angle));
	while (i < len)
	{
		transformed[i] = multiply_matrix(matrix, original[i]);
		i++;
	}
}

void	rotate_z(t_point *original, t_point *transformed, float angle, int len)
{
	float	matrix[3][3];
	int		i;

	i = 0;
	matrix_bzero(matrix);
	matrix[0][0] = cos(deg_to_rad(angle));
	matrix[1][1] = cos(deg_to_rad(angle));
	matrix[2][2] = 1;
	matrix[0][1] = -sin(deg_to_rad(angle));
	matrix[1][0] = sin(deg_to_rad(angle));
	while (i < len)
	{
		transformed[i] = multiply_matrix(matrix, original[i]);
		i++;
	}
}

void	rotate_points(t_map *map, t_point *original, t_point *transformed)
{
	rotate_x(original, transformed, map->angle[X], map->num_points);
	rotate_y(original, transformed, map->angle[Y], map->num_points);
	rotate_z(original, transformed, map->angle[Z], map->num_points);
}

void	orthographic_projection(t_map *map, t_point *original, t_point *transformed)
{
	int		i;
	float	matrix[3][3];

	i = 0;
	matrix_bzero(matrix);
	matrix[0][0] = 1;
	matrix[1][1] = 1;
	while (i < map->num_points)
	{
		transformed[i] = multiply_matrix(matrix, original[i]);
		i++;
	}
}

void	rescale(t_map *map, t_point *arr)
{
	int	i;

	i = 0;
	while (i < map->num_points)
	{
		arr[i].pos[X] *= map->scale;
		arr[i].pos[Y] *= map->scale;
		arr[i].pos[Z] *= map->scale;
		i++;
	}
}

void	center_map(t_map *map, t_point *arr)
{
	int	i;

	i = 0;
	while (i < map->num_points)
	{
		arr[i].pos[X] += map->origin.pos[X];
		arr[i].pos[Y] += map->origin.pos[Y];
		arr[i].pos[Z] += map->origin.pos[Z];
		i++;
	}
}

void	translate_map(t_meta *data, t_point *arr)
{
	resize_z(&data->map, arr);
	rotate_points(&data->map, arr, arr);
	orthographic_projection(&data->map, arr, arr);
	rescale(&data->map, arr);
	center_map(&data->map, arr);
}

int	in_bounds(t_point point)
{
	if (point.pos[X] < 0 || point.pos[X] > WINDOW_WIDTH ||
		point.pos[Y] < 0 || point.pos[Y] > WINDOW_HEIGHT)
		return (0);
	return (1);
}

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
	pixels = sqrt((delta.pos[X] * delta.pos[X]) + (delta.pos[Y] * delta.pos[Y]));
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

static int	limits(t_point *points, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (points[i].pos[X] < MARGIN || points[i].pos[X] > (WINDOW_WIDTH - MARGIN))
			return (1);
		if (points[i].pos[Y] < MARGIN || points[i].pos[Y] > (WINDOW_HEIGHT - MARGIN))
			return (1);
		i++;
	}
	return (0);
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

void	copy_map(t_point *src, t_point *dest, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		dest[i] = src[i];
		i++;
	}
}

int	draw_map(t_meta *data, int fit)
{	
	t_point	*temp;

	temp = malloc(sizeof(t_point) * data->map.num_points);
	if (!temp)
		err_handler(MEMORY, data);
	draw_background(data);
	copy_map(data->map.points, temp, data->map.num_points);
	translate_map(data, temp);
	if (fit)
		fit_screen(data, temp);
	connect_points(data, temp);
	mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->img.img_ptr, 0, 0);
	free(temp);
	return (0);
}
