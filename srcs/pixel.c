/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:10:18 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 12:29:23 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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
