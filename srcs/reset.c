/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 10:20:46 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 15:22:20 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	reset(t_meta *data)
{
	initialize_map(&data->map, NULL, 1);
	data->map.ratio = data->map.size.pos[Z] / data->map.size.pos[X];
	if (data->map.ratio > 0.5 && data->map.ratio <= 1.0)
		data->map.resize = data->map.ratio * 15;
	else if (data->map.ratio > 1 && data->map.ratio <= 2.0)
		data->map.resize = data->map.ratio * 30;
	else if (data->map.ratio > 1)
		data->map.resize = data->map.ratio * 45;
	initialize_colors(&data->map);
	draw_map(data, FIT);
}
