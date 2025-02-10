#include "cub3d.h"

void	ft_free_config(t_gamedata *config)
{
	free(config->floor);
	free(config->ceiling);
	free(config->map);
}
