/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:13:44 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/02 20:38:35 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	file_is_valid(char **argv)
{
	int	length;

	length = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][length - 4], ".fdf", 5))
		return (0);
	return (1);
}

int	boot_system(t_meta *data)
{
	data->map.ratio = data->map.size.pos[Z] / data->map.size.pos[X];
	if (data->map.ratio > 0.5 && data->map.ratio <= 1.0)
		data->map.resize = data->map.ratio * 15;
	else if (data->map.ratio > 1 && data->map.ratio <= 2.0)
		data->map.resize = data->map.ratio * 30;
	else if (data->map.ratio > 1)
		data->map.resize = data->map.ratio * 45;
	// TODO: Initialize Keys
	data->vars.mlx = mlx_init();
	if (!data->vars.mlx)
		return (-1);
	data->vars.win = mlx_new_window(data->vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF - gda-cruz");
	if (!data->vars.win)
		return (-1);
	data->img.img_ptr = mlx_new_image(data->vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img.img_ptr)
		return (-1);
	data->img.address = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, \
		&data->img.line_length, &data->img.endian);
	return (0);
}

int	main(int argc, char **argv)
{
	t_meta	data;
	if (argc != 2 || !file_is_valid(argv))
		return (0);
	load_map(&data.map, argv[1]);
	if (boot_system(&data) == -1)
		exit(1); // need to free the contents of the map in this case
	// printf("Min: %x\nMax: %x\nFloor: %x\nBackground: %x\n", data.map.colors.min, data.map.colors.max, data.map.colors.floor, data.map.colors.background);
	// printf("%.2f, %.2f\n", data.map.size.pos[X], data.map.size.pos[Y]);
	draw_map(&data, FIT);
	mlx_key_hook(data.vars.win, &handle_key_press, &data);
	mlx_loop_hook(data.vars.mlx, &handle_no_event, &data);
	mlx_loop(data.vars.mlx);
	// printf("\n%s\n", data.map.file_content);
	// printf("%d\n", data.map.num_points);
	// printf("\n\n");
	// printf("[ X = %.2f, Y = %.2f, Z = %.2f ]\n", data.map.size.pos[X], data.map.size.pos[Y], data.map.size.pos[Z]);
	// for (int i = 0; i < data.map.num_points; i++)
	// 	printf("%i = [ X = %.2f, Y = %.2f, Z = %.2f, Col = %d ]\n", i, data.map.points[i].pos[X], data.map.points[i].pos[Y], data.map.points[i].pos[Z], data.map.points[i].color);
	return (0);
}
