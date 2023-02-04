/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   height.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 10:19:48 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 12:28:09 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	extremize(t_meta *data)
{
	data->map.resize -= 0.1 * data->map.resize;
	draw_map(data, 0);
}

void	amenize(t_meta *data)
{
	data->map.resize += 0.1 * data->map.resize;
	draw_map(data, 0);
}
