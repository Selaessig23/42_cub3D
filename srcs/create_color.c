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
static void	ft_free_helper_for_extract(t_color *color, char *str,
	int *i)
{
	free(color);
	free(str);
	free(i);
}

/**
 * @brief function to extract the color value from to_extract
 * and transform it to an int. includes check if color-value
 * is correct (>0 && < 256)
 */
static int	ft_extract_color(t_gamedata **p_config, t_color *color, 
	char *to_extract, int *startindex)
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
		ft_free_helper_for_extract(color, to_extract, startindex);
		ft_error_handling(9, NULL, *p_config);
	}
	color_value = ft_atoi(temp);
	if (color_value < 0 || color_value > 255)
	{
		ft_free_helper_for_extract(color, to_extract, startindex);
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
* @param content the line of content inclusive the color identifier, 
* that has to be cleaned and than assigned to the game config variables
* @param start the index where to start searching for color values
* @param c the color identifier that was found (to be assigned)
*/
void	ft_set_color(t_gamedata **p_config, char *content, int start, char c)
{
	t_gamedata	*config;
	t_color		*color;
	int			*i;

	i = ft_calloc(1, sizeof(int));
	*i = start;
	config = *p_config;
	color = ft_calloc(1, sizeof(t_color));
	if (!color)
	{
		ft_free_helper_for_extract(NULL, content, i);
		ft_error_handling(9, NULL, *p_config);
	}
	color->red = ft_extract_color(p_config, color, 
			content, i);
	while (!ft_isdigit(content[*i]))
		*i += 1;
	color->green = ft_extract_color(p_config, color, 
			content, i);
	while (!ft_isdigit(content[*i]))
		*i += 1;
	color->blue = ft_extract_color(p_config, color, 
			content, i);
	if (c == 'C')
		config->ceiling = color;
	else
		config->floor = color;
	free (i);
}
