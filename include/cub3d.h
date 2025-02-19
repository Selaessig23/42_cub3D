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

typedef struct s_color {
	int		red;
	int		green;
	int		blue;
}		t_color;

typedef struct s_gamedata {
	int		fd_north;
	int		fd_south;
	int		fd_east;
	int		fd_west;
	t_color	*floor;
	t_color	*ceiling;
	char	*map;
}		t_gamedata;

typedef struct s_cub3d
{
	mlx_t	*mlx;
}	t_cub3d;

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
//creta_map.c
int			ft_set_map(t_gamedata **p_config, char *line, int fd);
//free.c
void		ft_freeing_support(int fd, char *line);
void		ft_free_config(t_gamedata *config);
//utils.c
int			ft_startjumper(char *str);
//test.c
void		ft_testprint(t_gamedata *config);
void		ft_testprint_maparray(char **map_arr);

#endif
