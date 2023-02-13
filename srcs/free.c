/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:11:23 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/13 11:29:48 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_stuff(t_meta *data, int complete)
{
	if (data->map.file_content)
		free(data->map.file_content);
	if (data->map.name)
		free(data->map.name);
	if (data->map.lines)
		free_split(data->map.lines);
	if (data->map.points)
		free(data->map.points);
	if (data->img.img_ptr)
		mlx_destroy_image(data->vars.mlx, data->img.img_ptr);
	if (data->vars.win)
		mlx_destroy_window(data->vars.mlx, data->vars.win);
	if (complete)
		return ;
}

void	err_handler(char *code, t_meta *data)
{
	printf("%sError: %s%s\n", RED_TEXT, code, RESET_TEXT);
	if (data)
		free_stuff(data, 1);
	exit (EXIT_FAILURE);
}
