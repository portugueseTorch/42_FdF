/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:10:03 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/13 11:04:14 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	handle_no_event(void *param)
{
	(void) param;
	return (0);
}

static void	handle_key_press_aux(int code, t_meta *data)
{
	if (code == XK_space)
		extremize(data);
	else if (code == XK_Delete)
		amenize(data);
	else if (code == XK_Return)
		display_map_info(data);
	else if (code == XK_0)
		reset(data);
	else if (code == XK_Escape)
		close_window((void *)data);
}

int	handle_key_press(int code, void *param)
{
	t_meta	*data;

	data = param;
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
	else
		handle_key_press_aux(code, data);
	return (0);
}
