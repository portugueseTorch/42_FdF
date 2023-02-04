/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 10:18:37 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 12:29:48 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	shift_right(t_meta *data)
{
	data->map.origin.pos[X] += 50;
	draw_map(data, 0);
}

void	shift_left(t_meta *data)
{
	data->map.origin.pos[X] -= 50;
	draw_map(data, 0);
}

void	shift_up(t_meta *data)
{
	data->map.origin.pos[Y] -= 50;
	draw_map(data, 0);
}

void	shift_down(t_meta *data)
{
	data->map.origin.pos[Y] += 50;
	draw_map(data, 0);
}
