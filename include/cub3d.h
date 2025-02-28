/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:19 by pvasilan          #+#    #+#             */
/*   Updated: 2025/02/28 13:26:28 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../libft/include/libft_bonus.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>
//check https://harm-smits.github.io/42docs/libs/minilibx/
//getting_started.html#installation
//for good documentation of the minilibx-library
# include "../MLX42/include/MLX42/MLX42.h"
//to communicate with X server / X Window System (X11)
# include <X11/X.h>
//well documented at https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h
# include <X11/keysym.h>
//to define which set is used in render.c
# include <stdbool.h>
//to provide a standardized way to report and interpret error conditions
# include <errno.h>

typedef struct s_vector2 {
	double	x;
	double	y;
}		t_vector2;

typedef struct s_player {
	t_vector2	pos;
	t_vector2	dir;
	int 	fov;
}		t_player;

typedef union u_color
{
	uint32_t	color;
	struct
	{
		uint8_t	blue;
		uint8_t	green;
		uint8_t	red;
		uint8_t	alpha;
	};
} t_color;

typedef struct s_cub3d
{
	mlx_t			*mlx;
	mlx_texture_t	*current_surface;
}	t_cub3d;

typedef struct s_gamedata {
	int			fd_north;
	int			fd_south;
	int			fd_east;
	int			fd_west;
	t_color		*floor;
	t_color		*ceiling;
	char		**map;
	t_player	player;
	t_cub3d		cub3d_data;
	int			window_width;
	int			window_height;
}		t_gamedata;


//command_line_input_check.c
int			ft_access_check(char *inputfile);
int			ft_extension_check(char *input);
//error_handling.c
void		ft_error_handling(int err, char *addinfo, t_gamedata *config);
//initiate_data.c
t_gamedata	*ft_initiate_data(int fd);
int			ft_search_map(char *line);
//create_texture.c
void		ft_set_texture(t_gamedata **p_config, char *line, int fd_infile);
//create_color.c
void		ft_set_color(t_gamedata **p_config, char *line, int fd);
//create_map.c
int			ft_set_map(t_gamedata **p_config, char *line, int fd);
//map_wallcheck.c
// int			ft_wall_check(t_gamedata *config, int fd);
int			ft_wall_check(t_gamedata *config, int fd, char **index);
//enclosure.c
// int			ft_check_carve(char **map, int startarr, int startstr,
// 				char prev_direction);
int			ft_check_carve(char **map, int startarr, int startstr, 
				char prev_direction);
//map_playercheck.c
int			ft_player_check(t_gamedata *config, int fd, char **map_cpy);
//free.c
void		ft_freeing_support(int fd, char *line);
void		ft_free_config(t_gamedata *config);
//parsing_utils.c
int			ft_startjumper(char *str);
// void		ft_zero_index(char **index);
void		ft_refill_map(char **dest, char **src);
//test.c
void		ft_testprint(t_gamedata *config);
void		ft_testprint_maparray(char **map_arr);

//vector functions
t_vector2	newvector(double x, double y);
t_vector2	addvectors(t_vector2 vector1, t_vector2 vector2);
t_vector2	subtractvectors(t_vector2 vector1, t_vector2 vector2);
t_vector2	multiplyvector(t_vector2 vector, double scalar);
t_vector2	dividevector(t_vector2 vector, double scalar);
t_vector2	normalizevector(t_vector2 vector);
t_vector2	rotatevector(t_vector2 vector, double angle);
double		vectorln(t_vector2 vector);

//drawing functions
mlx_texture_t*	createSurface(t_gamedata *config);
void			putPixel(t_color color, mlx_texture_t *surface, uint32_t x, uint32_t y);
void			drawLine(t_color color, mlx_texture_t *minimap_surface, t_vector2 start, t_vector2 end);
void			fillCeiling(t_gamedata *config);
void 			fillFloor(t_gamedata *config);

#endif
