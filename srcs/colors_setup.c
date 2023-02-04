/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:29:49 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 12:28:26 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	load_color(t_map *map, int i)
{
	map->points[i].paint = 1;
	map->points[i].color = DEFAULT;
	if (map->points[i].hex_color > 0)
	{
		map->points[i].color = map->points[i].hex_color;
		return ;
	}
	if (map->points[i].pos[Z] == map->size.pos[Z])
		map->points[i].color = map->colors.max;
	else if (map->points[i].pos[Z] == 0)
		map->points[i].color = map->colors.floor;
	else if (map->points[i].pos[Z] == map->min_z && map->min_z != 0)
		map->points[i].color = map->colors.min;
	else if (map->points[i].pos[Z] > 0)
		map->points[i].color = get_gradient(map->colors.floor, \
		map->colors.max, map->size.pos[Z], map->points[i].pos[Z]);
	else
		map->points[i].color = get_gradient(map->colors.min, \
		map->colors.floor, -map->min_z, \
		-(map->min_z - map->points[i].pos[Z]));
}

void	setup_color(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->num_points)
	{
		load_color(map, i);
		i++;
	}
}
