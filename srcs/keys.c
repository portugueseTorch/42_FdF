/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:10:03 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/03 15:50:33 by gda_cruz         ###   ########.fr       */
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

void	display_map_info(t_meta *data)
{
	printf("Angles: [ %.2f, %.2f, %.2f ]\n", data->map.angle[X], data->map.angle[Y], data->map.angle[Z]);
	printf("Origin: [ %.2f, %.2f, %.2f ]\n", data->map.origin.pos[X], data->map.origin.pos[Y], data->map.origin.pos[Z]);
	printf("Ratio: %.2f\n", data->map.ratio);
	printf("Resize: %.2f\n", data->map.resize);
	printf("Scale: %.2f\n", data->map.scale);
	printf("Size: [ %.2f, %.2f, %.2f ]\n\n", data->map.size.pos[X], data->map.size.pos[Y], data->map.size.pos[Z]);
}

void	reset(t_meta *data)
{
	initialize_map(&data->map, 1);
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

int	handle_no_event(void *param)
{
	(void) param;
	return (0);
}

int	handle_key_press(int code, void *param)
{
	t_meta *data = param;
	if (code == XK_Home)
		rotate_left(data);
	else if (code == XK_End)
		rotate_right(data);
	else if (code == XK_Right)
		shift_right(data);
	else if (code == XK_Left)
		shift_left(data);
	else if (code == XK_Up)
		shift_up(data);
	else if (code == XK_Down)
		shift_down(data);
	else if (code == XK_Tab)
		zoom_in(data);
	else if (code == XK_BackSpace)
		zoom_out(data);
	else if (code == XK_space)
		extremize(data);
	else if (code == XK_Delete)
		amenize(data);
	else if (code == XK_Return)
		display_map_info(data);
	else if (code == XK_0)
		reset(data);
	else if (code == XK_Escape)
		free_stuff(data, 0);
	return (0);
}
