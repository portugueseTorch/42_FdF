/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:11:40 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 12:29:28 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	rotate_x(t_point *original, t_point *transformed, float angle, int len)
{
	float	matrix[3][3];
	int		i;

	i = 0;
	matrix_bzero(matrix);
	matrix[0][0] = 1;
	matrix[1][1] = cos(deg_to_rad(angle));
	matrix[2][2] = cos(deg_to_rad(angle));
	matrix[2][1] = sin(deg_to_rad(angle));
	matrix[1][2] = -sin(deg_to_rad(angle));
	while (i < len)
	{
		transformed[i] = multiply_matrix(matrix, original[i]);
		i++;
	}
}

void	rotate_y(t_point *original, t_point *transformed, float angle, int len)
{
	float	matrix[3][3];
	int		i;

	i = 0;
	matrix_bzero(matrix);
	matrix[0][0] = cos(deg_to_rad(angle));
	matrix[1][1] = 1;
	matrix[2][2] = cos(deg_to_rad(angle));
	matrix[2][0] = -sin(deg_to_rad(angle));
	matrix[0][2] = sin(deg_to_rad(angle));
	while (i < len)
	{
		transformed[i] = multiply_matrix(matrix, original[i]);
		i++;
	}
}

void	rotate_z(t_point *original, t_point *transformed, float angle, int len)
{
	float	matrix[3][3];
	int		i;

	i = 0;
	matrix_bzero(matrix);
	matrix[0][0] = cos(deg_to_rad(angle));
	matrix[1][1] = cos(deg_to_rad(angle));
	matrix[2][2] = 1;
	matrix[0][1] = -sin(deg_to_rad(angle));
	matrix[1][0] = sin(deg_to_rad(angle));
	while (i < len)
	{
		transformed[i] = multiply_matrix(matrix, original[i]);
		i++;
	}
}

void	rotate_points(t_map *map, t_point *original, t_point *transformed)
{
	rotate_x(original, transformed, map->angle[X], map->num_points);
	rotate_y(original, transformed, map->angle[Y], map->num_points);
	rotate_z(original, transformed, map->angle[Z], map->num_points);
}

void	ortho_projection(t_map *map, t_point *original, t_point *transformed)
{
	int		i;
	float	matrix[3][3];

	i = 0;
	matrix_bzero(matrix);
	matrix[0][0] = 1;
	matrix[1][1] = 1;
	while (i < map->num_points)
	{
		transformed[i] = multiply_matrix(matrix, original[i]);
		i++;
	}
}
