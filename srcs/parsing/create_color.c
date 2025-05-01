/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:21:13 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/30 16:47:42 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file assigns RGB colors to floor and ceiling struct of game-config,
 * if input of input-file is valid
 *
 * CHECK: the algorithm will
 * not ignore wrong letters in between the RGB-color-information
 * like C 225t,  30!,  0
 * it will return an error for cases like this,
 * it only ignores chars defined in startjump-function (spaces),
 * color values have to be seperated by comma,
 * like C 225,30 ,     0
 *
 */

/**
 * @brief function to create an allocated color_struct for t_gamedata config
 * and connect the extracted color values to it
 * alpha value is defined here
 */
t_color	*ft_connect_color_values(int color_red, int color_green, int color_blue)
{
	t_color		*color;

	color = ft_calloc(1, sizeof(t_color));
	if (!color)
		return (NULL);
	color->red = color_red;
	color->green = color_green;
	color->blue = color_blue;
	color->alpha = 255;
	return (color);
}

/**
 * @brief function to extract the color value from to_extract
 * and transform it from char to an int.
 * function als checks if color-value
 * is correct (>0 && < 256)
 *
 * TODO: find a solution for fd-gnl-handling in case of error
 * by respecting the max amount of parameters
 * @return in case there is an malloc issue, function returns -1,
 * otherwise it returns the extracted color value
 */
static int	extr_color(char *to_extract, int *startindex, bool blue)
{
	char		*temp;
	int			endindex;
	long long	color_value;

	if (!to_extract[*startindex] || to_extract[*startindex] == '\n')
		return (-3);
	endindex = *startindex;
	color_value = 0;
	temp = NULL;
	while (to_extract[endindex] && to_extract[endindex] != '\n'
		&& ft_isdigit(to_extract[endindex]))
		endindex += 1;
	if (ft_last_color_check(blue, to_extract, *startindex, endindex))
		return (-4);
	temp = ft_substr(to_extract, *startindex, endindex);
	if (!temp)
		return (-1);
	color_value = (long long) ft_atoi(temp);
	free(temp);
	if (color_value > 255
		|| color_value > 255
		|| color_value > 255)
		return (-2);
	*startindex = endindex;
	return (color_value);
}

/**
 * @brief function that assigns the extracted color value
 * to the game config according to indentifier
 * of corresponding line in input file (ceiling / floor color)
 *
 * // while (line[*start] && line[*start] != '\n'
 * 		&& !ft_isdigit(line[*start]))/
 * // 	*start += 1;
 *
 * it ignores all chars that are not digit between the color-
 * definitions (not only comma)
 */
t_color	*ft_assign_color(t_gamedata **p_config,
			char *line, int *start, int fd)
{
	t_color		*color;
	long long	color_red;
	long long	color_green;
	long long	color_blue;

	color_red = check_color(*p_config, extr_color(line, start, false),
			line, fd);
	*start += ft_colorjumper(&line[*start], *p_config, line, fd);
	color_green = check_color(*p_config, extr_color(line, start, false),
			line, fd);
	*start += ft_colorjumper(&line[*start], *p_config, line, fd);
	color_blue = check_color(*p_config, extr_color(line, start, true),
			line, fd);
	color = ft_connect_color_values(color_red, color_green, color_blue);
	if (!color)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(9, NULL, *p_config);
	}
	return (color);
}

/**
 * @brief function that sets the color for floor and ceiling
 * as identifiers were found in line of input file
 *
 * if all chars that are not digit should be ignored
 * at the front of line (instead of only ignoring chars from
 * startjumper [apparantly spaces]):
 * // while (line[start] && line[start] != '\n'
 * // 	&& !ft_isdigit(line[start]))
 * // 	start += 1;
 *
 * @param line the line of content inclusive the color identifier,
 * that has to be cleaned and than assigned to the game config variables
 * @param start the index where to start searching for color values
 * @param c the color identifier that was found (to be assigned)
 */
void	ft_set_color(t_gamedata **p_config, char *line, int fd)
{
	t_gamedata	*config;
	t_color		*color;
	int			start;
	int			i;

	color = NULL;
	config = *p_config;
	start = 0;
	i = 0;
	start += ft_startjumper(&line[start]) + 1;
	start += ft_startjumper(&line[start]);
	if (!line[start] || line[start] == '\n')
	{
		ft_freeing_support(fd, line);
		ft_error_handling(4,
			ft_strdup("ceiling(\"C\") or floor(\"F\")"), *p_config);
	}
	color = ft_assign_color(p_config, line, &start, fd);
	i = ft_startjumper(line);
	if (!ft_strncmp(&line[i], "C", 1))
		config->ceiling = color;
	else
		config->floor = color;
}
