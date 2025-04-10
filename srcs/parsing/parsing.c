/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:05:19 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/10 10:25:06 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRIPTION:
 * file that organises the parsing-part by reading 
 * from input-file and checking for errors
 * and if all required information for the game 
 * was provided by input file
 */

/**
 * @brief helper function for ft_config_set_complete
 * that prints error and exits programm in case of missing data
 */
static void	print_error_and_exit(t_gamedata *config, int fd, char *errmsg)
{
	ft_freeing_support(fd, NULL);
	ft_error_handling(5, errmsg, config);
}

/**
 * @brief check if all necessary variables
 * for game configuration have been assigned except map,
 * otherwise send error message to ft_error_handling
 * (where everything gets freed and program exits)
 *
 * CHECK: up to now all colors for ceiling and floor have to be
 * assigned, no value is not accepted
 * (could be adapted to no value == 0, if desired)
 */
static int	ft_config_set_complete(t_gamedata *config, int fd)
{
	if (!config->t_north)
		print_error_and_exit(config, fd, ft_strdup("Path north texture"));
	if (!config->t_south)
		print_error_and_exit(config, fd, ft_strdup("Path south texture"));
	if (!config->t_east)
		print_error_and_exit(config, fd, ft_strdup("Path east texture"));
	if (!config->t_west)
		print_error_and_exit(config, fd, ft_strdup("Path west texture"));
	if (!config->floor)
		print_error_and_exit(config, fd, ft_strdup("Floor color"));
	if (!config->ceiling)
		print_error_and_exit(config, fd, ft_strdup("Ceiling color"));
	if (!config->map)
		print_error_and_exit(config, fd, ft_strdup("Map"));
	return (1);
}

/**
 * @brief function that sets the game config by reading from
 * input file (of command line argument 2) and sorts content
 * to required variables summarized in struct t_gamedata
 *
 * allocated memory for t_gamedata *config will be freed in main, if
 * no error is found in input file
 *
 * CHECK how to distinguish between malloc error in gnl and eol of file?
 *
 */
t_gamedata	*ft_initiate_data(int fd)
{
	t_gamedata	*config;

	config = ft_calloc(1, sizeof(t_gamedata));
	config->show_minimap = false;
	if (!config)
		ft_error_handling(9, NULL, NULL);
	ft_gnl_infileloop(fd, &config);
	if (!ft_config_set_complete(config, fd))
		return (NULL);
	else
		return (config);
}
