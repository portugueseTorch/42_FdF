/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:45:22 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 12:55:11 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	get_color(t_meta *data, int color)
{
	if (data->img.bpp != 32)
		color = mlx_get_color_value(data->vars.mlx, color);
	return (color);
}

int	get_hex_color(char *point, t_meta *data)
{
	char	**arr;
	int		color;

	color = 0;
	if (ft_strchr(point, ','))
	{
		arr = ft_split(point, ',');
		color = hextoi(&arr[1][2], data);
		free_split(arr);
		return (color);
	}
	return (0);
}

static int	get_light(int start, int end, float percent)
{
	return ((int)((1 - percent) * start + percent * end));
}

int	get_gradient(int start, int end, int length, int relative)
{
	float	percentage;
	int		colors[3];

	percentage = (float)relative / length;
	colors[0] = get_light((start >> 16) & 0xFF, (end >> 16) & 0xFF, percentage);
	colors[1] = get_light((start >> 8) & 0xFF, (end >> 8) & 0xFF, percentage);
	colors[2] = get_light(start & 0xFF, end & 0xFF, percentage);
	return ((colors[0] << 16) + (colors[1] << 8) + colors[2]);
}
