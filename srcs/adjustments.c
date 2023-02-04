/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjustments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:15:28 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 12:28:16 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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
	ortho_projection(&data->map, arr, arr);
	rescale(&data->map, arr);
	center_map(&data->map, arr);
}
