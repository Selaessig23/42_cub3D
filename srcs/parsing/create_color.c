/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:21:13 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/03 16:15:48 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file assigns RGB colors to floor and ceiling struct of game-config,
 * if input of input-file is valid
 *
 * CHECK: the algorithm will
 * ignore wrong letters in between the RGB-color-information
 * like
 * C 225t,  30!,  0
 * it will not return an error for cases like this, it just 
 * reads the digits, therefore also in case of negative values
 * (it will just ignore the dash)
 * --> correct / desired behaviour?
 *
 */

/**
 * @brief helper function to free within 25 lines limit
 */
static void	ft_free_helper_for_extract(t_color *color, char *line,
	int fd)
{
	if (color)
		free(color);
	ft_freeing_support(fd, line);
}

/**
 * @brief it validates the color values
 * as there can't be any negative-value (as 
 * only digits are accepted to be valid), the
 * negative value
 * -1 was used in ft_extract_color
 * to describe a malloc issue;
 * -2 was used in ft_extract_color 
 * to describe values that are bigger than 255;
 * in these case program frees correctly, 
 * returns an error and exits in this case
 * 
 */
static int	check_color(t_gamedata *config, int color,
	char *line, int fd)
{
	if (color == -1 
		|| color == -1
		|| color == -1)
	{
		ft_free_helper_for_extract(NULL, line, fd);
		ft_error_handling(9, NULL, config);
	}
	else if (color == -2
		|| color == -2
		|| color == -2)
	{
		ft_free_helper_for_extract(NULL, line, fd);
		ft_error_handling(6, NULL, config);
	}
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
static int	extr_color(t_color *color, char *to_extract, 
				int *startindex)
{
	char		*temp;
	int			endindex;
	long long	color_value;

	endindex = *startindex;
	color_value = 0;
	temp = NULL;
	while (ft_isdigit(to_extract[endindex]))
		endindex += 1;
	temp = ft_substr(to_extract, *startindex, endindex);
	if (!temp)
		return (-1);
	color_value = (long long) ft_atoi(temp);
	if (color_value > 255
		|| color_value > 255
		|| color_value > 255)
		return (-2);
	// printf("color value: %i\n", color_value);
	free(temp);
	*startindex = endindex;
	return (color_value);
}

/**
 * @brief function that assigns the extracted color value
 * to the game config according to indentifier
 * of corresponding line in input file (ceiling / floor color)
 * 
 * it ignores all chars that are not digit between the color-
 * definitions (not only comma)
 */
t_color	*ft_assign_color(t_gamedata **p_config, 
			char *line, int *start, int fd)
{
	t_gamedata	*config;
	t_color		*color;
	long long	color_value;

	config = *p_config;
	color = ft_calloc(1, sizeof(t_color));
	if (!color)
	{
		ft_free_helper_for_extract(NULL, line, fd);
		ft_error_handling(9, NULL, *p_config);
	}
	color_value = check_color(config, extr_color(color, line, start), line, fd);
	color->red = color_value;
	// printf("color value: %i\n", color->red);
	while (!ft_isdigit(line[*start]))
		*start += 1;
	color_value = check_color(config, extr_color(color, line, start), line, fd);
	color->green = color_value;
	while (!ft_isdigit(line[*start]))
		*start += 1;
	color_value = check_color(config, extr_color(color, line, start), line, fd);
	color->blue = color_value;
	color->alpha = 255;
	return (color);
}

/**
 * @brief function that sets the color for floor and ceiling
 * as identifiers were found in line of input file
 * 
 * it ignores all chars that are not digit at the front of line
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
	start = 1;
	i = 0;
	while (line[start] && !ft_isdigit(line[start]))
		start += 1;
	if (!line[start] || line[start] == '\n')
	{
		ft_free_helper_for_extract(NULL, line, fd);
		ft_error_handling(4,
			ft_strdup("ceiling color (\"C\") or floor color (\"F\")"), *p_config);
	}
	color = ft_assign_color(p_config, line, &start, fd);
	i = ft_startjumper(line);
	if (!ft_strncmp(&line[i], "C", 1))
		config->ceiling = color;
	else
		config->floor = color;
}
