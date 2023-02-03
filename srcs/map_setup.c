/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:32:12 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/03 13:48:00 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

#define BUFF 5000

void	initialize_map(t_map *map, int flag)
{
	if (flag == 0)
	{
		map->size.pos[X] = 0;
		map->size.pos[Y] = 0;
		map->size.pos[Z] = 0;
		map->num_points = 0;
		map->min_z = 0;
	}
	// initialize all the rest
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
	map->colors.floor = 0x3e571a;
	map->colors.menu = MENU_COLOR;
}

static char	*initial_read(int fd, t_meta *data)
{
	int		bytes;
	char	*buffer;
	char	*content;
	char	*temp;

	buffer = malloc(sizeof(char) * BUFF + 1);
	if (!buffer)
		err_handler(MEMORY, data);
	content = ft_strdup("");
	bytes = BUFF;
	while (bytes == BUFF)
	{
		bytes = read(fd, buffer, BUFF);
		buffer[bytes] = '\0';
		temp = content;
		content = ft_strjoin(temp, buffer);
		free(temp);
	}
	free(buffer);
	ft_printf("%s[ File successfully read ]%s\n", GREEN_TEXT, RESET_TEXT);
	return (content);
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
		if (ft_isalnum(map->file_content[i]) && ft_isterm(map->file_content[i + 1]))
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

static int	valid_point(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (i == 0)
		return (0);
	return (1);
}

static int	load_points(t_map *map, char *str, int line, t_meta *data)
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
		map->points[index].pos[X] = i - (map->size.pos[X] / 2);
		map->points[index].pos[Y] = line - (map->size.pos[Y] / 2);
		map->points[index].pos[Z] = ft_atoi(&arr[i][0]);
		map->points[index].paint = 1;
		map->points[index].color = DEFAULT;
		map->points[index].hex_color = get_hex_color(arr[i]);
		if (map->points[index].pos[Z] > map->size.pos[Z])
			map->size.pos[Z] = map->points[index].pos[Z];
		if (map->points[index].pos[Z] < map->min_z)
			map->min_z = map->points[index].pos[Z];
		index++;
		i++;
	}
	free_split(arr);
	return (i);
}

static void	get_map_points(t_map *map, t_meta *data)
{
	int	i;
	int	points;

	i = 0;
	map->points = ft_calloc(map->num_points, sizeof(t_point));
	if (!map->points)
		err_handler(MEMORY, data);
	while (map->lines[i])
	{
		points += load_points(map, map->lines[i], i, data);
		i++;
	}
}

static void	get_file_lines(t_map *map, char *file, t_meta *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		err_handler(MAP_LOAD, data);
	map->lines = malloc(sizeof(char *) * (map->size.pos[Y] + 1));
	if (!map->lines)
		err_handler(MEMORY, data);
	while (i < map->size.pos[Y])
		map->lines[i++] = get_next_line(fd);
	map->lines[i] = NULL;
	close(fd);
}

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

void	load_map(t_meta *data, char *file)
{
	int	fd;

	ft_printf("%s[ Loading Map... ]%s\n", GREEN_TEXT, RESET_TEXT);
	initialize_map(&data->map, 0);
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
	ft_printf("%s[ Setting up GUI... ]%s\n", GREEN_TEXT, RESET_TEXT);
}
