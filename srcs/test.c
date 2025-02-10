#include "cub3d.h"


void		ft_testprint(t_gamedata *config)
{
	t_color	*floor_print;
	t_color	*ceiling_print;

	floor_print = config->floor;
	ceiling_print = config->ceiling;
	ft_printf("Print input of struct game_config\n");
	ft_printf("fd_north: %i\n", config->fd_north);
	ft_printf("fd_south: %i\n", config->fd_south);
	ft_printf("fd_east: %i\n", config->fd_east);
	ft_printf("fd_west: %i\n", config->fd_west);
	ft_printf("ceiling red: %i\n", ceiling_print->red);
	ft_printf("ceiling green: %i\n", ceiling_print->green);
	ft_printf("ceiling blue: %i\n", ceiling_print->blue);
	ft_printf("floor red: %i\n", floor_print->red);
	ft_printf("floor green: %i\n", floor_print->green);
	ft_printf("floor blue: %i\n", floor_print->blue);
	ft_printf("map: %s\n", config->map);
}