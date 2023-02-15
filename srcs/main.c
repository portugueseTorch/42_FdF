/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:13:44 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/13 13:47:01 by gda-cruz         ###   ########.fr       */
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

static void	initialize_data(t_meta *data)
{
	data->vars.mlx = NULL;
	data->vars.win = NULL;
	data->img.img_ptr = NULL;
	data->map.lines = NULL;
	data->map.points = NULL;
	data->map.name = NULL;
	data->map.file_content = NULL;
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
	data->vars.mlx = mlx_init();
	if (!data->vars.mlx)
		return (-1);
	data->vars.win = mlx_new_window(data->vars.mlx, WINDOW_WIDTH, \
		WINDOW_HEIGHT, "FdF - gda-cruz");
	if (!data->vars.win)
		return (-1);
	data->img.img_ptr = mlx_new_image(data->vars.mlx, WINDOW_WIDTH, \
		WINDOW_HEIGHT);
	if (!data->img.img_ptr)
		return (-1);
	data->img.address = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, \
		&data->img.line_length, &data->img.endian);
	return (0);
}

int	close_window(void *param)
{
	t_meta	*data;

	data = param;
	free_stuff(data, 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_meta	data;

	if (argc != 2)
		err_handler(NUM_ARGS, NULL);
	if (!file_is_valid(argv))
		err_handler(FILE_TYPE, NULL);
	initialize_data(&data);
	load_map(&data, argv[1]);
	if (boot_system(&data) == -1)
		err_handler(BOOTING, &data);
	draw_map(&data, FIT);
	ft_printf("%s ---------------------\e[m\n", GREEN_TEXT);
	ft_printf("%s\e[1m| >> GUI ready to use |\e[m\n", GREEN_TEXT);
	ft_printf("%s ---------------------\e[m\n", GREEN_TEXT);
	print_instructions();
	mlx_key_hook(data.vars.win, &handle_key_press, &data);
	mlx_loop_hook(data.vars.mlx, &handle_no_event, &data);
	mlx_hook(data.vars.win, 33, 0, &close_window, &data);
	mlx_loop(data.vars.mlx);
	if (data.vars.mlx)
	{
		mlx_destroy_display(data.vars.mlx);
		free(data.vars.mlx);
	}
	return (0);
}
