/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:18:39 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/01/31 20:33:09 by gda_cruz         ###   ########.fr       */
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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		i;

	dst = img->address + (y * img->line_length + x * (img->bpp / 8));
	i = img->bpp - 8;
	while (i >= 0)
	{
		// little endian
		if (img->endian == 0)
			*dst++ = ((color >> (img->bpp - 8 - i)) & 0xFF);
		// big endian
		else
			*dst++ = ((color >> i) & 0xFF);
		i -= 8;
	}
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
	printf("%x\n", data->map.colors.background);
	mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->img.img_ptr, 0, 0);
}

int	draw_map(t_meta *data, int fit)
{
	t_point	*temp;
	
	temp = malloc(sizeof(t_point) * data->map.num_points);
	if (!temp)
		exit (EXIT_FAILURE); // TODO: adjust exit function to clear leaks
	draw_background(data);
	(void) fit;
	return (0);
}
