/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 10:17:51 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 12:29:44 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	rotate_left(t_meta *data)
{
	data->map.angle[Z] -= 15;
	draw_map(data, 0);
}

void	rotate_right(t_meta *data)
{
	data->map.angle[Z] += 15;
	draw_map(data, 0);
}
