/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:19 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/27 11:06:34 by mstracke         ###   ########.fr       */
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
	char			*t_north;
	char			*t_south;
	char			*t_east;
	char			*t_west;
	t_color			*floor;
	t_color			*ceiling;
	char			**map;
	t_player		player;
	t_cub3d			cub3d_data;
	int				window_width;
	int				window_height;
	bool			show_minimap;
}		t_gamedata;

typedef enum e_direction{
	DIR_NORTH = 0,
	DIR_SOUTH = 1,
	DIR_WEST = 2,
	DIR_EAST = 3
}	t_direction;

typedef struct s_minimap_data
{
	int				minimap_size;
	int				cell_size;
	int				map_x_len;
	int				map_y_len;
	t_color			wall_color;
	t_color			floor_color;
	t_color			player_color;
	t_color			bg_color;
}		t_minimap_data;

typedef struct s_hit_info
{
	t_vector2		pos;
	t_direction		side;
	int				hit;
	float			perp_wall_dist;
}		t_hit_info;

typedef struct s_ray {
    t_vector2 dir;       // Ray direction
    t_vector2 delta_dist; // Delta distance
    t_vector2 side_dist;  // Side distance
    int map_x;           // Current map x position
    int map_y;           // Current map y position
    int step_x;          // Step direction in x
    int step_y;          // Step direction in y
    float wall_x;        // Where exactly the wall was hit
} t_ray;

typedef struct s_render_line {
    int height;          // Height of line to draw
    int draw_start;      // Start y position
    int draw_end;        // End y position
    int screen_x;        // X position on screen
} t_render_line;


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

//initiate_mlx.c
void	    ft_init_mlx(t_gamedata *config);
//cleanup.c
void		ft_cleanup(t_gamedata *config, bool error);
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
// void		delete_images(t_gamedata *config);
// void		load_wall_textures(t_gamedata *config);
// mlx_image_t	*load_single_wall_texture(t_gamedata *config, char *path);
void		draw_minimap(t_gamedata *config);
void		key_handler(mlx_key_data_t keydata, void *param);
void		cast_ray_and_draw_wall(char **map, mlx_image_t *img, t_gamedata *config);
void		pick_and_place(t_direction side, t_gamedata *config, mlx_image_t *img, int x, int draw_start, int draw_end, float wall_x);
void		resize(int width, int height, void *param);
void		key_handler(mlx_key_data_t keydata, void *param);
void fill_upper_half(mlx_image_t *img, t_color color);
void fill_lower_half(mlx_image_t *img, t_color color);

void draw_player_position(t_gamedata *config, t_minimap_data minimap_data);
void draw_player_direction(t_gamedata *config, t_minimap_data minimap_data);
void clear_minimap_surface(t_gamedata *config, t_minimap_data minimap_data);
#endif
