/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_enlarger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:37:01 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/10 15:29:39 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file enlarges the extracted map with spaces so that all lines (y)
 * have the same length (x). this is useful for the wall check.
 */

/**
 * @brief helper function for ft_map_enlarger, it allocates a new string
 * for new line in map with max length and fills the line with 
 * content of old line of map + spaces
 */
static void	ft_realloc_mapline(t_gamedata **p_config, 
	int fd, int index, int len)
{
	char		*new_mapline;
	char		*old_mapline;
	t_gamedata	*config;

	config = *p_config;
	old_mapline = config->map[index];
	new_mapline = (char *)malloc(sizeof(char) * len + 1);
	if (!new_mapline)
	{
		close (fd);
		ft_error_handling(9, NULL, *p_config);
	}
	ft_strcpy(new_mapline, old_mapline);
	ft_memset(&new_mapline[ft_strlen(old_mapline)], 
		' ', (len + 1) - ft_strlen(old_mapline));
	new_mapline[len] = '\0';
	config->map[index] = new_mapline;
	free(old_mapline);
}

/**
 * @brief function to increase the length of each string
 * (line) of the map to the max length of map array
 * 1st it checks for the max length of a line of map
 * 2nd it iterates through map to adapt each line to max length
 * (it length of line is smaller than max length)
 * 
 * if x or y of grid is bigger than 500 there will be a warning
 * in terminal
 */
void	ft_map_enlarger(t_gamedata **p_config, int fd)
{
	t_gamedata	*config;
	size_t		len;
	int			i;

	config = *p_config;
	i = 0;
	len = 0;
	while (config->map[i])
	{
		if (ft_strlen(config->map[i]) > len)
			len = ft_strlen(config->map[i]);
		i += 1;
	}
	if (len > 500 || i > 500)
		ft_dprintf(1, "Wow, this maps seems to be huge. This could cause "\
			"performance problems.\n Are you sure you use the required hardware "\
			"to not experience performance problems?\n");
	i = 0;
	while (config->map[i])
	{
		if (ft_strlen(config->map[i]) < len)
			ft_realloc_mapline(p_config, fd, i, len);
		i += 1;
	}
}
