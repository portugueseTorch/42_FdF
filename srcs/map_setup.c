/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:32:12 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/02 20:45:10 by gda_cruz         ###   ########.fr       */
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

static char	*initial_read(int fd)
{
	int		bytes;
	char	*buffer;
	char	*content;
	char	*temp;

	buffer = malloc(sizeof(char) * BUFF + 1);
	if (!buffer)
		exit (EXIT_FAILURE);
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

static void	get_map_size(t_map *map)
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
				exit (EXIT_FAILURE);
			map->size.pos[X] = count;
			count = 0;
		}
	}
	if (map->size.pos[X] && map->size.pos[X] != count)
		exit (EXIT_FAILURE);
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

static int	load_points(t_map *map, char *str, int line)
{
	int			i;
	char		**arr;
	static int	index = 0;

	i = 0;
	arr = ft_split(str, ' ');
	while (arr[i] && arr[i][0] != '\n')
	{
		if (!valid_point(&arr[i][0]))
			exit (EXIT_FAILURE);
		map->points[index].pos[X] = i - (map->size.pos[X] / 2);
		map->points[index].pos[Y] = line - (map->size.pos[Y] / 2);
		map->points[index].pos[Z] = ft_atoi(&arr[i][0]);
		map->points[index].paint = 1;
		map->points[index].color = DEFAULT;
		map->points[index].hex_color = get_hex_color(arr[i]);
		// printf("%i\n", map->points[index].hex_color);
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

static void	get_map_points(t_map *map)
{
	int	i;
	int	points;

	i = 0;
	map->points = ft_calloc(map->num_points, sizeof(t_point));
	while (map->lines[i])
	{
		points += load_points(map, map->lines[i], i);
		i++;
	}
}

static void	get_file_lines(t_map *map, char *file)
{
	int	i;
	int	fd;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit (EXIT_FAILURE);
	map->lines = malloc(sizeof(char *) * (map->size.pos[Y] + 1));
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

void	load_map(t_map *map, char *file)
{
	int	fd;

	initialize_map(map, 0);
	initialize_colors(map);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit (EXIT_FAILURE);
	map->file_content = initial_read(fd);
	close(fd);
	get_map_size(map);
	get_file_lines(map, file);
	get_map_points(map);
	setup_color(map);
	ft_printf("%s[ Setting up GUI ]%s\n", GREEN_TEXT, RESET_TEXT);
}
