/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:08:24 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/10 14:13:27 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file keeps small simple functions that
 * are used by several other functions in different files
 */

/**
 * @brief this function handles new lines in map part of file
 * (== last part of file)
 * it will loop through the file until end of file (return)
 * or another char than '\n' was found (== error and exit)
 */
void	ft_new_line_looper(char *line, t_gamedata *config, int fd, char *map)
{
	free(line);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else if (*line != '\n')
		{
			ft_freeing_support(fd, line);
			free(map);
			map = NULL;
			ft_error_handling(14, NULL, config);
		}
		free (line);
	}
}

/**
 * @brief function that checks if all required as already been
 * filled as map has to be last content in file
 */
int	ft_map_is_last(t_gamedata *config)
{
	if (!config->t_north || !config->t_south 
		|| !config->t_east || !config->t_west
		|| !config->floor || !config->ceiling)
		return (0);
	else
		return (1);
}

/**
 * @brief function to jump over spaces (according to ft_startjumper) 
 * and ignore comma
 * this functions serves for extracting colors from identifier ceiling
 * and floor
 * 
 * it iterates through the string searching for the next comma while
 * ignoring spaces before and after. if there is no comma,
 * ir returns an error, frees all allocated data and exits program
 * 
 */
int	ft_colorjumper(char *str, t_gamedata *config, char *line, int fd)
{
	int	i;

	i = 0;
	i += ft_startjumper(str);
	if (str[i] && str[i] == ',')
		i += 1;
	else
	{
		ft_freeing_support(fd, line);
		ft_error_handling(6, NULL, config);
	}
	i += ft_startjumper(&str[i]);
	return (i);
}

/**
 * @brief this functions returns a start index to jump
 * over spaces, 
 * (newlines and tabs: //	|| (str[i] >= 9 && str[i] <= 12))
 * at the beginning of a string
 */
int	ft_startjumper(char *str)
{
	int	i;

	i = 0;
	while (str[i] 
		&& ((str[i] == ' ')))
		i += 1;
	return (i);
}

/**
 * @brief function to re-establish the map for carve-checks
 * after having destroyed it in the previous carve-check
 */
void	ft_refill_map(char **dest, char **src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		ft_strncpy(dest[i], src[i], ft_strlen(src[i]));
		i += 1;
	}
	dest[i] = NULL;
}
