/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:05:19 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/03 12:05:22 by mstracke         ###   ########.fr       */
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
 * @brief final check if all necessary variables
 * for game configuration have been assigned,
 * otherwise send error message to ft_error_handling
 * (where everything gets freed and program exits)
 *
 * CHECK: up to now all colors for ceiling and floor have to be
 * assigned, no value is not accepted
 * (could be adapted to no value == 0, if desired)
 */
static int	ft_config_set_complete(t_gamedata *config)
{
	if (!config->t_north)
		ft_error_handling(5, ft_strdup("Path north texture"), config);
	if (!config->t_south)
		ft_error_handling(5, ft_strdup("Path south texture"), config);
	if (!config->t_east)
		ft_error_handling(5, ft_strdup("Path east texture"), config);
	if (!config->t_west)
		ft_error_handling(5, ft_strdup("Path west texture"), config);
	if (!config->floor)
		ft_error_handling(5, ft_strdup("Floor color"), config);
	if (!config->ceiling)
		ft_error_handling(5, ft_strdup("Ceiling color"), config);
	if (!config->map)
		ft_error_handling(5, ft_strdup("Map"), config);
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
	if (!ft_config_set_complete(config))
		return (NULL);
	else
		return (config);
}
