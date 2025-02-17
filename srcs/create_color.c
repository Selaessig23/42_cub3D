#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file assigns paths for the textures and checks if
 * the path is correct and file is readable,
 * otherwise it will print an error message
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
 * @brief helper function to free within 25lines limit
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
 */
static int	ft_extract_color(t_gamedata **p_config, t_color *color, 
	char *to_extract, int *startindex, int fd)
{
	char	*temp;
	int		i;
	int		color_value;

	i = *startindex;
	color_value = 0;
	while (ft_isdigit(to_extract[i]))
		i += 1;
	temp = ft_substr(to_extract, *startindex, i);
	if (!temp)
	{
		ft_free_helper_for_extract(color, to_extract, startindex, fd);
		ft_error_handling(9, NULL, *p_config);
	}
	color_value = ft_atoi(temp);
	if (color_value < 0 || color_value > 255)
	{
		ft_free_helper_for_extract(color, to_extract, startindex, fd);
		ft_error_handling(6, NULL, *p_config);
	}
	free(temp);
	*startindex = i;
	return (color_value);
}

/**
* @brief (helper) function that sets the color for floor and ceiling
* if identifiers were found in a line of input file
* 
* @param line the line of content inclusive the color identifier, 
* that has to be cleaned and than assigned to the game config variables
* @param start the index where to start searching for color values
* @param c the color identifier that was found (to be assigned)
*/
// void	ft_set_color(t_gamedata **p_config, char *line, int start, char c)
void	ft_set_color(t_gamedata **p_config, char *line, int fd)
{
	t_gamedata	*config;
	t_color		*color;
	int			start;
	int			*i;

	config = *p_config;
	color = NULL;
	start = 1;
	i = NULL;
	while (!ft_isdigit(line[start]))
		start += 1;
	if (!line[start])
	{
		ft_free_helper_for_extract(NULL, line, i, fd);
		ft_error_handling(5, 
			"no color for ceiling or floor defined", *p_config);
	}
	i = ft_calloc(1, sizeof(int));
	if (!i)
	{
		ft_free_helper_for_extract(NULL, line, i, fd);
		ft_error_handling(9, 
			"no color for ceiling or floor defined", *p_config);
	}
	*i = start;
	// i += 1;
	// while (!ft_isdigit(line[*i]))
	// 	*i += 1;
	// if (!line[*i])
	// {
	// 	ft_free_helper_for_extract(NULL, line, i, fd);
	// 	ft_error_handling(5, 
	// 		"no color for ceiling or floor defined", *p_config);
	// }
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
	free (i);
}
