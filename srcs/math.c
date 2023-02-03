/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:25:09 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/01 16:14:30 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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

void	mult_matrix(float (*m1)[3], float (*m2)[3], float (*result)[3])
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			k = 0;
			while (k < 3)
			{
				result[i][j] += m1[i][k] * m2[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
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
