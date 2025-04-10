/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:19 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/10 22:36:24 by pvasilan         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	char			*t_north; //only for parsing
	char			*t_south; //only for parsing
	char			*t_east; //only for parsing
	char			*t_west; //only for parsing
	t_color			*floor; //required
	t_color			*ceiling; //required
	char			**map; //required
	t_player		player; //required
	t_cub3d			cub3d_data; //required
	int				window_width; //not in use
	int				window_height; //not in use
	bool			show_minimap; //required
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
	t_vector2		dir;       // Ray direction
	t_vector2		delta_dist; // Delta distance
	t_vector2		side_dist;  // Side distance
	int				map_x;           // Current map x position
	int				map_y;           // Current map y position
	int				step_x;          // Step direction in x
	int				step_y;          // Step direction in y
	float			wall_x;        // Where exactly the wall was hit
}		t_ray;

typedef struct s_render_line {
	int				height;          // Height of line to draw
	int				draw_start;      // Start y position
	int				draw_end;        // End y position
	int				screen_x;        // X position on screen
}		t_render_line;

typedef struct s_wall_slice {
    int screen_x;
    float wall_x;
} t_wall_slice;

typedef struct s_triangle {
	t_vector2	v1;
	t_vector2	v2;
	t_vector2	v3;
}		t_triangle;

typedef struct s_fov_data {
    t_vector2   player_pos;
    t_vector2   dir_end;
    t_vector2   left_ray;
    t_vector2   right_ray;
    double      dir_angle;
    double      left_angle;
    double      right_angle;
    double      fov_angle;
    int         radius;
    t_color     color_view;
    mlx_image_t *surface;
} t_fov_data;

typedef struct s_rect {
    int x;
    int y;
    int width;
    int height;
} t_rect;



//parsing
//parsing/command_line_input_check.c
int			ft_access_check(char *inputfile);
int			ft_extension_check(char *input);
//parsing/parsing.c
t_gamedata	*ft_initiate_data(int fd);
//identifier_check.c
void		ft_gnl_infileloop(int fd, t_gamedata **p_config);
int			ft_search_map(char *line);
//parsing/create_texture.c
void		ft_set_texture(t_gamedata **p_config, char *line, int fd_infile);
//parsing/create_color.c
void		ft_set_color(t_gamedata **p_config, char *line, int fd);
//parsing/create_map.c
int			ft_set_map(t_gamedata **p_config, char *line, int fd);
//parsing/map_enlarger.c
void		ft_map_enlarger(t_gamedata **p_config, int fd);
//parsing/map_wallcheck.c
int			ft_wall_check(t_gamedata *config, int fd, char **index);
//parsing/map_outer_cave_check.c
int			ft_check_cave(char **map, int startarr, int startstr,
				char prev_direction);
//parsing/create_player.c
int			ft_player_check(t_gamedata *config, int fd);
//parsing/parsing_utils.c
int			ft_startjumper(char *str);
void		ft_refill_map(char **dest, char **src);
int			ft_colorjumper(char *str, t_gamedata *config, char *line, int fd);
int			ft_map_is_last(t_gamedata *config);
void		ft_new_line_looper(char *line, t_gamedata *config, int fd, char *map);
//initiate_mlx.c
void		ft_init_mlx(t_gamedata *config);
void		ft_init_imgs(t_gamedata *config);
//locomotion.c
void		ft_player_rotation(mlx_key_data_t keydata, t_gamedata *config);
void		ft_player_movement(mlx_key_data_t keydata, t_gamedata *config);
//handlers.c
void		key_handler(mlx_key_data_t keydata, void *param);
void		render(void *param);
void		resize(int width, int height, void *param);

//renderer/minimap/minimap.c
void		ft_minimap_switcher(t_gamedata *config);
void		draw_minimap(t_gamedata *config);
//renderer/minimap/mm_draw_grid.c
void		draw_minimap_grid(t_gamedata *config,
				t_minimap_data minimap_data);
void		init_fov_data(t_gamedata *config,
				t_minimap_data minimap_data, t_fov_data *fov_data);
void		draw_fov_outline(t_fov_data *fov_data);
void		draw_fov_arc(t_fov_data *fov_data);
void		draw_player_fov(t_gamedata *config, t_minimap_data minimap_data);
//renderer/minimap/mm_draw_player.c
void		draw_player_position(t_gamedata *config,
				t_minimap_data minimap_data);
void		draw_player_direction(t_gamedata *config,
				t_minimap_data minimap_data);
//renderer/cub3d/renderer.c
void		init_ray(t_ray *ray, t_player player, float camera_x);
void		cast_ray_and_draw_wall(t_gamedata *config);
//renderer/cub3d/background.c
void		fill_lower_half(mlx_image_t *img, t_color color);
void		fill_upper_half(mlx_image_t *img, t_color color);
//renderer/cub3d/dda.c
void		perform_dda(char **map, t_ray *ray, t_hit_info *hit_info);
//renderer/cub3d/texture_cast.c
mlx_image_t	*pick(t_direction side, t_gamedata *config);
//renderer/color_pixel.c
void		putpixel(t_color color, mlx_image_t *img, uint32_t x, uint32_t y);
void		copy_texture_line(mlx_image_t *render_img, mlx_image_t *texture,
				t_render_line line, t_wall_slice wall_slice);
//vector functions
t_vector2	newvector(double x, double y);
t_vector2	addvectors(t_vector2 vector1, t_vector2 vector2);
t_vector2	subtractvectors(t_vector2 vector1, t_vector2 vector2);
t_vector2	multiplyvector(t_vector2 vector, double scalar);
t_vector2	dividevector(t_vector2 vector, double scalar);
t_vector2	normalizevector(t_vector2 vector);
t_vector2	rotatevector(t_vector2 vector, double angle);
double		vectorln(t_vector2 vector);

//error_handling.c
void		ft_error_handling(int err, char *addinfo, t_gamedata *config);
//cleanup.c
void		ft_cleanup(t_gamedata *config, bool error);
//free.c
void		ft_freeing_support(int fd, char *line);
void		ft_free_config(t_gamedata *config);

//just for testing of parsing-part
void		ft_testprint(t_gamedata *config);
void		ft_testprint_maparray(char **map_arr);

//test functions
// mlx_image_t	*createSurface(t_gamedata *config);
// void		drawLine(t_color color, mlx_image_t *minimap_surface,
// 				t_vector2 start, t_vector2 end);
// void		fillCeiling(t_gamedata *config);
// void		fillFloor(t_gamedata *config);
// void		delete_images(t_gamedata *config);
// void		load_wall_textures(t_gamedata *config);
// mlx_image_t	*load_single_wall_texture(t_gamedata *config, char *path);
// void		ft_create_minimap(t_gamedata *config);

//unsorted static functions
// void		pick_and_place(t_direction side, t_gamedata *config, mlx_image_t *img, int x, int draw_start, int draw_end, float wall_x);
// void		clear_minimap_surface(t_gamedata *config, t_minimap_data minimap_data);
#endif
