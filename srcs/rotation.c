/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 10:17:51 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/15 09:16:39 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	rotate_left(t_meta *data)
{
	data->map.angle[Y] -= 15;
	draw_map(data, 0);
}

void	rotate_right(t_meta *data)
{
	data->map.angle[Y] += 15;
	draw_map(data, 0);
}
