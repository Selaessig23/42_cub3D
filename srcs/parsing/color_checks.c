/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:48:23 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/30 16:48:41 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRIPTION:
 * in this file some simple checks of color value are summarized
 * 
 */

/**
 * @brief it validates the color values
 * as there can't be any negative-value (as
 * only digits are accepted to be valid), the
 * negative value
 * -1 was used in ft_extract_color
 * to describe a malloc issue;
 * -2 was used in ft_extract_color
 * to describe values that are bigger than 255;
 * -3 was used in ft_extract_color to
 * describe a missing value
 * -4 was used in ft_extract_color to
 * describe a wrong value in the last color value (blue)
 * in these cases program frees correctly,
 * returns an error and exits in this case
 *
 */
int	check_color(t_gamedata *config, int color, char *line, int fd)
{
	if (color == -1)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(9, NULL, config);
	}
	else if (color == -2)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(6, NULL, config);
	}
	else if (color == -3)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(6, NULL, config);
	}
	else if (color == -4)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(16, NULL, config);
	}
	return (color);
}

/**
 * @brief this function checks if it is the last color (blue) and if 
 * yes if there is something else coming after the color value
 * except spaces (startjumper) and newline(eol) (==wrong)
 * 
 * // printf("last char: $%c$\n", to_check[end]);
 * 
 * @return if wrong, it returns 1, otherwise 0
 */
int	ft_last_color_check(bool blue, char *to_check, int start, int end)
{
	(void)start;
	if (blue == true 
		&& (to_check[end + ft_startjumper(&to_check[end])] 
			&& to_check[end + ft_startjumper(&to_check[end])] != '\n'))
		return (1);
	else
		return (0);
}
