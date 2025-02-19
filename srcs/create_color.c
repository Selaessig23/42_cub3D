#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file assigns RGB colors to floor and ceiling struct of game-config,
 * if input of input-file is valid
 * 
 * CHECK: the algorithm will
 * handle wrong letters in between the RGB-color-information
 * like 
 * C 225t,  30!,  0
 * it will not return an error for cases like this. 
 * --> correct / desired behaviour?
 * 
 */



// int	ft_check_color_value(t_color *color)
// {
// 	if (color->red < 0 || color->red > 255
// 		|| color->blue < 0 || color->blue > 255
// 		|| color->red < 0 || color->red > 255)
// 		return (1);
// 	else
// 		return (0);
// }

/**
 * @brief helper function to free within 25 lines limit
 */
static void	ft_free_helper_for_extract(t_color *color, char *line,
	int *i, int fd)
{
	if (color)
		free(color);
	ft_freeing_support(fd, line);
	if (i)
		free(i);
}

/**
 * @brief function to extract the color value from to_extract
 * and transform it to an int. includes check if color-value
 * is correct (>0 && < 256)
 * 
 * TO-DO: find a solution for fd-gnl-handling in case of error
 * by respecting the max amount of parameters
 */
static int	ft_extract_color(t_gamedata **p_config, t_color *color, 
	char *to_extract, int *startindex, int fd)
{
	char	*temp;
	int		i;
	int		color_value;

	i = *startindex;
	color_value = 0;
	temp = NULL;
	while (ft_isdigit(to_extract[i]))
		i += 1;
	// if (!to_extract[i] || to_extract[i] == '\n')
	// {
	// 	temp = ft_substr(to_extract, 0, 1);
	// 	ft_free_helper_for_extract(color, to_extract, startindex, fd);
	// 	ft_error_handling(4, temp, *p_config);
	// }
	temp = ft_substr(to_extract, *startindex, i);
	if (!temp)
	{
		ft_free_helper_for_extract(color, to_extract, startindex, fd);
		ft_error_handling(9, NULL, *p_config);
	}
	color_value = ft_atoi(temp);
	free(temp);
	if (color_value < 0 || color_value > 255)
	{
		ft_free_helper_for_extract(color, to_extract, startindex, fd);
		ft_error_handling(6, NULL, *p_config);
	}
	*startindex = i;
	return (color_value);
}

/**
 * @brief function that assigns the extracted color value
 * to the game config according to indentifier 
 * of corresponding line in input file (ceiling / floor color)
 */
void	ft_assign_color(t_gamedata **p_config, char *line, int *i, int fd)
{
	t_gamedata	*config;
	t_color		*color;

	config = *p_config;
	color = ft_calloc(1, sizeof(t_color));
	if (!color)
	{
		ft_free_helper_for_extract(NULL, line, i, fd);
		ft_error_handling(9, NULL, *p_config);
	}
	color->red = ft_extract_color(p_config, color, 
			line, i, fd);
	while (!ft_isdigit(line[*i]))
		*i += 1;
	color->green = ft_extract_color(p_config, color, 
			line, i, fd);
	while (!ft_isdigit(line[*i]))
		*i += 1;
	color->blue = ft_extract_color(p_config, color, 
			line, i, fd);
	if (!ft_strncmp(line, "C", 1))
		config->ceiling = color;
	else
		config->floor = color;

}

/**
* @brief function that sets the color for floor and ceiling
* if identifiers were found in a line of input file 
* 
* @param line the line of content inclusive the color identifier, 
* that has to be cleaned and than assigned to the game config variables
* @param start the index where to start searching for color values
* @param c the color identifier that was found (to be assigned)
*/
void	ft_set_color(t_gamedata **p_config, char *line, int fd)
{
	int			start;
	int			*i;

	start = 1;
	i = NULL;
	while (line[start] && !ft_isdigit(line[start]))
		start += 1;
	if (!line[start] || line[start] == '\n')
	{
		ft_free_helper_for_extract(NULL, line, i, fd);
		ft_error_handling(4, 
			ft_strdup("ceiling color (\"C\") or floor color (\"F\")"), *p_config);
	}
	i = ft_calloc(1, sizeof(int));
	if (!i)
	{
		ft_free_helper_for_extract(NULL, line, i, fd);
		ft_error_handling(9, NULL, *p_config);
	}
	*i = start;
	ft_assign_color(p_config, line, i, fd);
	free (i);
}

// if (!to_extract[i] || to_extract[i] == '\n')
// {
// 	temp = ft_substr(to_extract, 0, 1);
// 	ft_free_helper_for_extract(color, to_extract, startindex, fd);
// 	ft_error_handling(4, temp, *p_config);
// }