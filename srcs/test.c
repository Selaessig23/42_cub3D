#include "cub3d.h"

void	ft_testprint_maparray(char **map_arr)
{
	int		i;

	i = 0;
	while (map_arr[i])
	{
		printf("line %i of map: %s\n", i, map_arr[i]);
		i += 1;
	}
}

/**
 * @brief test function to print the input of game config struct
 */
void	ft_testprint(t_gamedata *config)
{
	t_color	*floor_print;
	t_color	*ceiling_print;

	floor_print = config->floor;
	ceiling_print = config->ceiling;
	ft_printf("\n---------------------------------"
		"-------------------------------\n");
	ft_printf("TEST: Print input of struct game_config\n");
	ft_printf("fd_north: %s\n", config->t_north);
	ft_printf("fd_south: %s\n", config->t_south);
	ft_printf("fd_east: %s\n", config->t_east);
	ft_printf("fd_west: %s\n", config->t_west);
	ft_printf("ceiling red: %i\n", ceiling_print->red);
	ft_printf("ceiling green: %i\n", ceiling_print->green);
	ft_printf("ceiling blue: %i\n", ceiling_print->blue);
	ft_printf("floor red: %i\n", floor_print->red);
	ft_printf("floor green: %i\n", floor_print->green);
	ft_printf("floor blue: %i\n", floor_print->blue);
	ft_testprint_maparray(config->map);
	ft_printf("------------------------------------"
		"----------------------------\n");
	// ft_printf("map:\n%s\n", config->map);
}


