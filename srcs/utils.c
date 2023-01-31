/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:45:22 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/01/31 18:03:53 by gda_cruz         ###   ########.fr       */
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

static int	hextoi(char *str)
{
	int	result;
	int	i;
	
	i = 0;
	result = 0;
	if (!ft_ishex(str))
		exit (EXIT_FAILURE);
	while (str[i])
	{
		result *= 16;
		if (ft_isdigit(str[i]))
			result += (str[i] - 48);
		else if (str[i] >= 'A' && str[i] <= 'F')
			result += (str[i] - 55);
		else if (str[i] >= 'a' && str[i] <= 'f')
			result += (str[i] - 87);
		i++;
	}
	return (result);
}

int	get_hex_color(char *point)
{
	char	**arr;
	int		color;

	color = 0;
	if (ft_strchr(point, ','))
	{
		arr = ft_split(point, ',');
		color = hextoi(arr[1]);
		free_split(arr);
	}
	return (color);
}

static int	get_color(int start, int end, float percent)
{
	return ((int)((1 - percent) * start + percent * end));
}

int	get_gradient(int start, int end, int length, int relative)
{
	float	percentage;
	int		colors[3];

	percentage = (float)relative/length;
	colors[0] = get_color((start >> 16) & 0xFF, (end >> 16) & 0xFF, percentage);
	colors[1] = get_color((start >> 8) & 0xFF, (end >> 8) & 0xFF, percentage);
	colors[2] = get_color(start & 0xFF, end & 0xFF, percentage);
	return ((colors[0] << 16) + (colors[1] << 8) + colors[2]);
}
