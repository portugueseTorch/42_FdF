/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:13:58 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 15:22:34 by gda_cruz         ###   ########.fr       */
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
# define X 				0
# define Y 				1
# define Z 				2
# define WINDOW_WIDTH	1920
# define WINDOW_HEIGHT	1080
# define MENU_WIDTH		0
# define FIT			1
# define MARGIN			50
# define BUFF 			5000

/*** ERROR MESSAGES **/
# define NUM_ARGS	"fdf requires 2 arguments"
# define FILE_TYPE	"input file must be of type .fdf"
# define FILE_OPEN	"no such file or directory"
# define MEMORY		"unable to allocate memory"
# define MAP_LOAD	"failure loading the map"
# define BOOTING	"failure booting mlx server"

/******* COLORS ******/
# define RED_TEXT 		"\033[0;31m"
# define GREEN_TEXT 	"\033[0;32m"
# define YELLOW_TEXT 	"\033[0;33m"
# define BLUE_TEXT 		"\033[0;34m"
# define PURPLE_TEXT	"\033[0;35m"
# define CYAN_TEXT 		"\033[0;36m"
# define RESET_TEXT 	"\033[0;0m"

# define LIGHT_GRAY	0xBBBBBB
# define BLACK		0x151515
# define CLAY		0xCF9241
# define BROWN		0x885306
# define LIGHT_BLUE	0x70BEF5
# define WATER_BLUE	0x3096e0
# define DARK_BLUE	0x0434C3
# define DARK_GRAY	0x303030
# define EARTH		0x3E571A

# define BACKGROUND	BLACK
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
}	t_colors;

typedef struct s_map
{
	char		*file_content;
	char		*name;
	char		**lines;
	t_point		size;
	t_point		origin;
	t_point		*points;
	t_colors	colors;
	int			num_points;
	int			min_z;
	float		angle[3];
	float		ratio;
	float		resize;
	float		scale;
}	t_map;

typedef struct s_meta
{
	t_vars	vars;
	t_img	img;
	t_map	map;
}	t_meta;

/**** Map Setup ****/
char	*initial_read(int fd, t_meta *data);
void	load_map(t_meta *data, char *file);
void	initialize_map(t_map *map, char *file, int flag);
void	initialize_colors(t_map *map);
void	get_file_lines(t_map *map, char *file, t_meta *data);
void	get_map_points(t_map *map, t_meta *data);

/**** Map Draw *****/
int		draw_map(t_meta *data, int fit);
int		my_mlx_pixel_put(t_meta *data, t_point point);
int		in_bounds(t_point point);
void	color_bytes(char *img, int endian, int color, int a);
void	copy_map(t_point *src, t_point *dest, int length);
void	connect_points(t_meta *data, t_point *arr);

/****** Colors ******/
int		get_color(t_meta *data, int color);
void	setup_color(t_map *map);

/**** Projection ***/
void	rotate_points(t_map *map, t_point *original, t_point *transformed);
void	ortho_projection(t_map *map, t_point *original, t_point *transformed);
void	translate_map(t_meta *data, t_point *arr);

/******* Math ******/
float	deg_to_rad(float angle);
int		hextoi(char *str, t_meta *data);
t_point	multiply_matrix(float (*matrix)[3], t_point point);
void	matrix_bzero(float (*matrix)[3]);

/****** Utils ******/
int		valid_point(char *str);
int		get_hex_color(char *point, t_meta *data);
int		get_gradient(int start, int end, int length, int relative);
int		limits(t_point *points, int len);
void	print_instructions(void);

/******* Free ******/
void	free_split(char **arr);
void	free_stuff(t_meta *data, int complete);
void	err_handler(char *code, t_meta *data);

/******* Hooks *******/
int		handle_key_press(int code, void *param);
int		handle_no_event(void *param);
void	rotate_left(t_meta *data);
void	rotate_right(t_meta *data);
void	shift_right(t_meta *data);
void	shift_left(t_meta *data);
void	shift_up(t_meta *data);
void	shift_down(t_meta *data);
void	zoom_in(t_meta *data);
void	zoom_out(t_meta *data);
void	extremize(t_meta *data);
void	amenize(t_meta *data);
void	display_map_info(t_meta *data);
void	reset(t_meta *data);

#endif