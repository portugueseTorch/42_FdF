/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 10:33:21 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 15:22:15 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	display_map_info(t_meta *data)
{
	ft_printf("%s -----------------\e[m\n", YELLOW_TEXT);
	ft_printf("%s| MAP INFORMATION |\n", YELLOW_TEXT);
	ft_printf("%s -----------------\e[m\n", YELLOW_TEXT);
	ft_printf("%sMap Name: %s\n", YELLOW_TEXT, data->map.name);
	ft_printf("%sNumber of Points: %d\n", YELLOW_TEXT, data->map.num_points);
	ft_printf("Angles: [ %d, %d, %d ]\n", (int)data->map.angle[X], \
		(int)data->map.angle[Y], (int)data->map.angle[Z]);
	ft_printf("Origin: [ %d, %d, %d ]\n", (int)data->map.origin.pos[X], \
		(int)data->map.origin.pos[Y], (int)data->map.origin.pos[Z]);
	ft_printf("Ratio: %d\n", (int)data->map.ratio);
	ft_printf("Resize: %d\n", (int)data->map.resize);
	ft_printf("Scale: %d\n", (int)data->map.scale);
	ft_printf("Size: [ %d, %d, %d ]%s\n\n", (int)data->map.size.pos[X], \
		(int)data->map.size.pos[Y], (int)data->map.size.pos[Z], RESET_TEXT);
}
