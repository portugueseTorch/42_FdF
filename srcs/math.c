/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:25:09 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 12:29:18 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	hextoi(char *str, t_meta *data)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	if (!ft_ishex(str))
		err_handler(MAP_LOAD, data);
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

void	matrix_bzero(float (*matrix)[3])
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
			matrix[i][j++] = 0;
		i++;
	}
}

float	deg_to_rad(float angle)
{
	return (angle * (M_PI / 180.0));
}

t_point	multiply_matrix(float (*matrix)[3], t_point point)
{
	int		i;
	int		j;
	t_point	result;

	i = 0;
	result = point;
	while (i < 3)
	{
		result.pos[i] = 0;
		result.color = point.color;
		j = 0;
		while (j < 3)
		{
			result.pos[i] += (matrix[i][j] * point.pos[j]);
			j++;
		}
		i++;
	}
	return (result);
}
