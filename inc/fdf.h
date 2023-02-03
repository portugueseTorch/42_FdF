/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:13:58 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/03 15:46:05 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/***** LIBRARIES *****/
# include "../lib/libft/inc/libft.h"
# include <mlx.h>
# include <X11/keysym.h>
# include <stdbool.h>
# include <math.h>
# include <X11/keysym.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

/******* MACROS ******/
# define X 0
# define Y 1
# define Z 2
# define WINDOW_WIDTH	1920
# define WINDOW_HEIGHT	1080
# define MENU_WIDTH		0
# define FIT			1
# define MARGIN			50

/*** ERROR MESSAGES **/
# define NUM_ARGS	"fdf requires 2 arguments"
# define FILE_TYPE	"input file must be of type .fdf"
# define FILE_OPEN	"no such file or directory"
# define MEMORY		"unable to allocate memory"
# define MAP_LOAD	"failure loading the map"
# define BOOTING	"failure booting mlx server"

/******* COLORS ******/
# define GREEN_TEXT "\033[0;32m"
# define RED_TEXT 	"\033[0;31m"
# define RESET_TEXT "\033[0;0m"

# define LIGHT_GRAY	0xBBBBBB
# define BLACK		0x151515
# define CLAY		0xCF9241
# define BROWN		0x885306
# define LIGHT_BLUE	0x70BEF5
# define WATER_BLUE	0x3096e0
# define DARK_BLUE	0x0434C3
# define DARK_GRAY	0x303030

# define BACKGROUND	BLACK
# define MENU_COLOR DARK_GRAY
# define DEFAULT	0xEF8633

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
	float		angle[3];		// holds the rotation angles for the projection
	float		ratio;			// stores the ratio between the highest value of z and the x axis
	float		resize;			// scaleback for z if it is too big in proportion to x axis
	float		scale;
}	t_map;

typedef struct s_meta
{
	t_vars	vars;
	t_img	img;
	t_map	map;
}	t_meta;

/**** Map Setup ****/
void	load_map(t_meta *data, char *file);
void	initialize_map(t_map *map, int flag);
void	initialize_colors(t_map *map);

/**** Map Draw *****/
int		draw_map(t_meta *data, int fit);
void	color_bytes(char *img, int endian, int color, int a);
int		my_mlx_pixel_put(t_meta *data, t_point point);
int		in_bounds(t_point point);
void	copy_map(t_point *src, t_point *dest, int length);

/******* Math ******/
void	matrix_bzero(float (*matrix)[3]);
float	deg_to_rad(float angle);
t_point	multiply_matrix(float (*matrix)[3], t_point point);
void	mult_matrix(float (*m1)[3], float (*m2)[3], float (*result)[3]);

/****** Utils ******/
void	free_split(char **arr);
int		get_hex_color(char *point);
int		get_gradient(int start, int end, int length, int relative);

int		handle_key_press(int code, void *param);
int		handle_no_event(void *param);

void	err_handler(char *code, t_meta *data);
void	free_stuff(t_meta *data, int complete);

#endif