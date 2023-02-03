/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:11:23 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/03 15:49:40 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	free_stuff(t_meta *data, int complete)
{
	if (data->map.file_content)
		free(data->map.file_content);
	if (data->map.lines)
		free_split(data->map.lines);
	if (data->map.points)
		free(data->map.points);
	if (data->img.img_ptr)
		mlx_destroy_image(data->vars.mlx, data->img.img_ptr);
	if (data->vars.win)
		mlx_destroy_window(data->vars.mlx, data->vars.win);
	if (complete)
		mlx_destroy_display(data->vars.mlx);
}

void	err_handler(char *code, t_meta *data)
{
	printf("%sError: %s%s\n", RED_TEXT, code, RESET_TEXT);
	if (data)
		free_stuff(data, 1);
	exit (EXIT_FAILURE);
}
