/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:30:43 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 13:44:48 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

char	*initial_read(int fd, t_meta *data)
{
	int		bytes;
	int		total;
	char	*buffer;
	char	*content;
	char	*temp;

	buffer = malloc(sizeof(char) * BUFF + 1);
	if (!buffer)
		err_handler(MEMORY, data);
	content = ft_strdup("");
	bytes = BUFF;
	total = 0;
	while (bytes == BUFF)
	{
		bytes = read(fd, buffer, BUFF);
		total += bytes;
		buffer[bytes] = '\0';
		temp = content;
		content = ft_strjoin(temp, buffer);
		ft_printf("%s\r  > Reading File: %d KB read", GREEN_TEXT, total / 1024);
		free(temp);
	}
	free(buffer);
	return (content);
}

void	get_file_lines(t_map *map, char *file, t_meta *data)
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
	ft_printf("\n");
	while (i < map->size.pos[Y])
	{
		ft_printf("%s\r  > Parsing Lines: %d lines read", GREEN_TEXT, i);
		map->lines[i++] = get_next_line(fd);
	}
	ft_printf("%s\n  \e[1mFile successfully read\e[m\n", GREEN_TEXT);
	map->lines[i] = NULL;
	close(fd);
}
