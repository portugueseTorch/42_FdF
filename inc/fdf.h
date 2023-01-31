/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:13:58 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/01/31 20:33:42 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define X 0
# define Y 1
# define Z 2
# define WINDOW_WIDTH	1920
# define WINDOW_HEIGHT	1080
# define MENU_WIDTH		300
# define FIT			1

/******* COLORS ******/
# define GREEN_TEXT "\033[0;32m"
# define RESET_TEXT "\033[0;0m"

# define LIGHT_GRAY	0xBBBBBB
# define BLACK		0x151515
# define CLAY		0xCF9241
# define BROWN		0x885306
# define LIGHT_BLUE	0x70BEF5
# define DARK_BLUE	0x0434C3
# define DARK_GRAY	0x303030

# define BACKGROUND	BLACK
# define MENU_COLOR DARK_GRAY
# define DEFAULT	BLACK

/***** LIBRARIES *****/

# include "../lib/libft/inc/libft.h"
# include <mlx.h>
# include <stdbool.h>
# include <math.h>
# include <X11/keysym.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

/***** STRUCTS *****/

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_img
{
	void	*img_ptr;
	char	*address;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_point
{
	int		color;
	int		hex_color;
	float	pos[3];
	float	globe[2];
	int		paint;
}	t_point;

typedef struct s_colors
{
	int	min;
	int	max;
	int	floor;
	int	background;
	int	menu;
}	t_colors;


typedef struct s_map
{
	char		*file_content;	// store the contents of the file instead of keep opening and closing it
	char		**lines;		// file split into lines
	t_point		size;			// store information of the map (ex. number of cols, rows, and highest z)
	t_point		origin;			// information about the coordinates of the origin (moved to the middle).
	t_point		*points;		// stores a t_point[], where each entry is a point, and the coordinates are offset
	t_colors	colors;			// stores the general colors of the map, used to determine the color of the point
	int			num_points;		// number of points in total
	int			min_z;			// smallest value of z
	float		proportion;		// stores the proportion between the highest value of z and the x axis
	float		resize;			// scaleback for z if it is too big in proportion to x axis
}	t_map;

typedef struct s_meta
{
	t_vars	vars;
	t_img	img;
	t_map	map;
}	t_meta;

/**** Map Setup ****/
void	load_map(t_map *map, char *file);

/**** Map Draw *****/
int		draw_map(t_meta *data, int fit);
void	color_bytes(char *img, int endian, int color, int a);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/****** Utils ******/
void	free_split(char **arr);
int		get_hex_color(char *point);
int		get_gradient(int start, int end, int length, int relative);

#endif