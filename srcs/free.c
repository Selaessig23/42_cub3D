/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:31:45 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/09 17:48:54 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (line)
	{
		free(line);
		line = NULL;
	}
}

/**
 * @brief function to free the game config struct and
 * close all relating file descriptors
 */
void	ft_free_config(t_gamedata *config)
{
	if (config->t_east)
		free(config->t_east);
	if (config->t_north)
		free(config->t_north);
	if (config->t_south)
		free(config->t_south);
	if (config->t_west)
		free(config->t_west);
	free(config->floor);
	config->floor = NULL;
	free(config->ceiling);
	config->ceiling = NULL;
	if (config->map)
		ft_free(config->map);
	free(config);
	config = NULL;
}
