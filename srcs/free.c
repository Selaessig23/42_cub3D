#include "cub3d.h"

/**
 * DESCRIPTION:
 * file to organise the freeing processes of allocated memory
 * in case of error or exit
 */

/**
 * @brief function that supports freeing of 
 * get_next_line function in case of an error
 * or invalid content of input-file
 * 
 * to free static variable in get_next_line, the function
 * has to be called with closed (invalid) fd
 * 
 * @param fd fd of input file to read from with gnl-function
 * @param line return value of gnl-function to free
 */
void	ft_freeing_support(int fd, char *line)
{
	close(fd);
	get_next_line(fd);
	free(line);
	line = NULL;
}

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
	config->floor = NULL;
	free(config->ceiling);
	config->ceiling = NULL;
	free(config->map);
	config->map = NULL;
	free(config);
	config = NULL;
}
