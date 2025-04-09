/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:08:24 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/09 17:24:12 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file keeps small simple functions that
 * are used by several other functions in different files
 */

/**
 * @brief function to jump over spaces and ignore comma
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
	printf("check comma index 1part: %i, $%s$\n", i, &str[i]);
	i += ft_startjumper(str);
	// while (str[i] && str[i] == ' ')
	// 	i += 1;
	printf("check comma index 2part: %i, $%s$\n", i, &str[i]);
	if (str[i] && str[i] == ',')
		i += 1;
	else
	{
		ft_freeing_support(fd, line);
		ft_error_handling(6, NULL, config);
	}
	// while (str[i] && str[i] == ' ')
	// 	i += 1;
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
