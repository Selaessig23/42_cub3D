/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:08:24 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/08 10:27:17 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file keeps small simple functions that
 * are used by several other functions in different files
 */

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
