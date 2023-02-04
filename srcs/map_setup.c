/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:32:12 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 15:23:59 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	initialize_map(t_map *map, char *file, int flag)
{
	if (flag == 0)
	{
		map->size.pos[X] = 0;
		map->size.pos[Y] = 0;
		map->size.pos[Z] = 0;
		map->num_points = 0;
		map->min_z = 0;
		map->name = ft_strdup(&file[5]);
	}
	map->origin.pos[X] = WINDOW_WIDTH / 2;
	map->origin.pos[Y] = WINDOW_HEIGHT / 2;
	map->origin.pos[Z] = 0;
	map->angle[X] = 30;
	map->angle[Y] = -30;
	map->angle[Z] = 15;
	map->resize = 1;
	map->scale = 1;
}

void	initialize_colors(t_map *map)
{
	map->colors.background = BACKGROUND;
	map->colors.min = WATER_BLUE;
	map->colors.max = CLAY;
	map->colors.floor = EARTH;
}

static void	get_map_size(t_map *map, t_meta *data)
{
	int		count;
	int		i;

	count = 0;
	i = -1;
	while (map->file_content[++i])
	{
		if (map->file_content[i] == '\n' && !map->file_content[i + 1])
			break ;
		if (ft_isalnum(map->file_content[i]) && \
			ft_isterm(map->file_content[i + 1]))
			count++;
		if (map->file_content[i] == '\n')
		{
			map->size.pos[Y]++;
			if (map->size.pos[X] && map->size.pos[X] != count)
				err_handler(MAP_LOAD, data);
			map->size.pos[X] = count;
			count = 0;
		}
	}
	if (map->size.pos[X] && map->size.pos[X] != count)
		err_handler(MAP_LOAD, data);
	map->size.pos[Y]++;
	map->num_points = map->size.pos[Y] * map->size.pos[X];
}

void	load_map(t_meta *data, char *file)
{
	int	fd;

	ft_printf("%s\n\e[1m[ Loading Map... ]\e[m\n", GREEN_TEXT);
	initialize_map(&data->map, file, 0);
	initialize_colors(&data->map);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		err_handler(FILE_OPEN, data);
	data->map.file_content = initial_read(fd, data);
	close(fd);
	get_map_size(&data->map, data);
	get_file_lines(&data->map, file, data);
	get_map_points(&data->map, data);
	setup_color(&data->map);
	ft_printf("%s\e[1m[ Map Successfully Loaded ]\e[m\n\n", GREEN_TEXT);
}
