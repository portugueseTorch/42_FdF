/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:35:09 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/13 09:56:58 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	load_aux(t_map *map, int index, int i, int line)
{
	map->points[index].pos[X] = i - (map->size.pos[X] / 2);
	map->points[index].pos[Y] = line - (map->size.pos[Y] / 2);
	map->points[index].paint = 1;
	map->points[index].color = DEFAULT;
}

static void	check_z(t_map *map, int index)
{
	if (map->points[index].pos[Z] > map->size.pos[Z])
		map->size.pos[Z] = map->points[index].pos[Z];
	if (map->points[index].pos[Z] < map->min_z)
		map->min_z = map->points[index].pos[Z];
}

int	load_points(t_map *map, char *str, int line, t_meta *data)
{
	int			i;
	char		**arr;
	static int	index = 0;

	i = 0;
	arr = ft_split(str, ' ');
	if (!arr)
		err_handler(MAP_LOAD, data);
	while (arr[i] && arr[i][0] != '\n')
	{
		if (!valid_point(&arr[i][0]))
		{
			free_split(arr);
			err_handler(MAP_LOAD, data);
		}
		load_aux(map, index, i, line);
		map->points[index].pos[Z] = ft_atoi(&arr[i][0]);
		map->points[index].hex_color = get_hex_color(arr[i], data);
		check_z(map, index);
		index++;
		i++;
	}
	free_split(arr);
	return (i);
}

void	get_map_points(t_map *map, t_meta *data)
{
	int	i;
	int	points;

	i = 0;
	points = 0;
	map->points = ft_calloc(map->num_points, sizeof(t_point));
	if (!map->points)
		err_handler(MEMORY, data);
	while (map->lines[i])
	{
		points += load_points(map, map->lines[i], i, data);
		i++;
		ft_printf("%s\r  > Loading Points: %d points read", GREEN_TEXT, points);
	}
	ft_printf("%s\n  \e[1mPoints successfully loaded\e[m\n", GREEN_TEXT);
}
