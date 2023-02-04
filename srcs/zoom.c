/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 10:19:14 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 12:29:53 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	zoom_in(t_meta *data)
{
	data->map.scale += 0.1 * data->map.scale;
	draw_map(data, 0);
}

void	zoom_out(t_meta *data)
{
	data->map.scale -= 0.1 * data->map.scale;
	draw_map(data, 0);
}
