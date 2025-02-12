#include "cub3d.h"

/**
 * @brief function to free the game config struct and
 * close all relating file descriptors
 */
void	ft_free_config(t_gamedata *config)
{
	close(config->fd_east);
	close(config->fd_north);
	close(config->fd_south);
	close(config->fd_west);
	free(config->floor);
	free(config->ceiling);
	free(config->map);
	free(config);
}
