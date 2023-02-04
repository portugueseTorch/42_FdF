/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:12:25 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 13:50:28 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	in_bounds(t_point point)
{
	if (point.pos[X] < 0 || point.pos[X] > WINDOW_WIDTH \
		|| point.pos[Y] < 0 || point.pos[Y] > WINDOW_HEIGHT)
		return (0);
	return (1);
}

int	limits(t_point *points, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (points[i].pos[X] < MARGIN \
			|| points[i].pos[X] > (WINDOW_WIDTH - MARGIN))
			return (1);
		if (points[i].pos[Y] < MARGIN \
			|| points[i].pos[Y] > (WINDOW_HEIGHT - MARGIN))
			return (1);
		i++;
	}
	return (0);
}

void	copy_map(t_point *src, t_point *dest, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		dest[i] = src[i];
		i++;
	}
}

int	valid_point(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (i == 0)
		return (0);
	return (1);
}

void	print_instructions(void)
{
	ft_printf("\n%s----------------\n", CYAN_TEXT);
	ft_printf("| INSTRUCTIONS |\n");
	ft_printf("----------------\n");
	ft_printf("Moving Map: Keyboard Arrows\n");
	ft_printf("Rotating Map:\n");
	ft_printf("  • Clockwise Rotation - End\n");
	ft_printf("  • Counter-clockwise Rotation - Home\n");
	ft_printf("Zoom:\n");
	ft_printf("  • Zoom In - Tab\n");
	ft_printf("  • Zoom Out - Backspace\n");
	ft_printf("Height Manipulation:\n");
	ft_printf("  • Increase Heights - Space\n");
	ft_printf("  • Decrease Heights - Del\n");
	ft_printf("Display Map Info: Enter\n");
	ft_printf("Reset: 0\n");
	ft_printf("Quit: Esc\n\n%s", RESET_TEXT);
}
