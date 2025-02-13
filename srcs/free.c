#include "cub3d.h"

/**
 * @brief function to free the game config struct and
 * close all relating file descriptors
 */
void	ft_free_config(t_gamedata *config)
{
	if (config->fd_east > 2)
		close(config->fd_east);
	if (config->fd_north > 2)
		close(config->fd_north);
	if (config->fd_south > 2)
		close(config->fd_south);
	if (config->fd_west > 2)
		close(config->fd_west);
	free(config->floor);
	free(config->ceiling);
	free(config->map);
	free(config);
}
