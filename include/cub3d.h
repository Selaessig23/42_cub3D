/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:19 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/15 17:41:24 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../libft/include/libft_bonus.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdbool.h>
# include <errno.h>

# define WIDTH 800
# define HEIGHT 600

typedef struct s_vector2 {
	double	x;
	double	y;
}		t_vector2;

typedef struct s_player {
	t_vector2	pos;
	t_vector2	dir;
	int			fov;
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
}	t_color;

typedef struct s_cub3d
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*minimap_surface;
	mlx_image_t		*east;
	mlx_image_t		*west;
	mlx_image_t		*north;
	mlx_image_t		*south;
}	t_cub3d;

typedef struct s_gamedata {
	char		*t_north;
	char		*t_south;
	char		*t_east;
	char		*t_west;
	t_color		*floor;
	t_color		*ceiling;
	char		**map;
	t_player	player;
	t_cub3d		cub3d_data;
	int			window_width;
	int			window_height;
	bool		show_minimap;
}		t_gamedata;

typedef enum e_direction{
	DIR_NORTH = 0,
	DIR_SOUTH = 1,
	DIR_WEST = 2,
	DIR_EAST = 3
}	t_direction;

int			ft_access_check(char *inputfile);
int			ft_extension_check(char *input);
void		ft_error_handling(int err, char *addinfo, t_gamedata *config);
t_gamedata	*ft_initiate_data(int fd);
int			ft_search_map(char *line);
void		ft_set_texture(t_gamedata **p_config, char *line, int fd_infile);
void		ft_set_color(t_gamedata **p_config, char *line, int fd);
int			ft_set_map(t_gamedata **p_config, char *line, int fd);
int			ft_wall_check(t_gamedata *config, int fd, char **index);
int			ft_check_carve(char **map, int startarr, int startstr,
				char prev_direction);
int			ft_player_check(t_gamedata *config, int fd);
void		ft_freeing_support(int fd, char *line);
void		ft_free_config(t_gamedata *config);
int			ft_startjumper(char *str);
void		ft_refill_map(char **dest, char **src);
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
mlx_image_t	*createSurface(t_gamedata *config);
void		putPixel(t_color color, mlx_image_t *img, uint32_t x, uint32_t y);
void		drawLine(t_color color, mlx_image_t *minimap_surface, 
				t_vector2 start, t_vector2 end);
void		fillCeiling(t_gamedata *config);
void		fillFloor(t_gamedata *config);
void		ft_create_minimap(t_gamedata *config);
void		render(void *param);
void		delete_images(t_gamedata *config);
void load_wall_textures(t_gamedata *config);
mlx_image_t	*load_single_wall_texture(t_gamedata *config, char *path);
void		draw_minimap(t_gamedata *config);
void		key_handler(mlx_key_data_t keydata, void *param);
void		cast_ray_and_draw_wall(char **map, t_vector2 player_pos, 
				t_vector2 player_dir, mlx_image_t *img, t_gamedata *config);

#endif
