/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:05:43 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/10 10:26:22 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file organises the check for indentifiers in input
 * file by reading line per line with function gnl
 * if identifier is found, all important information 
 * will be extracted by functions of further parsing-files
 * (organised in this file)
 * if identifiers occur twice an error in input-file 
 * is found and therefore some of the config variables 
 * could not be set up an error will be returned 
 * and the program exits.
 *
 *
 * PROBLEM to solve: how to close the infile fd
 * in case of an error in one of the subfunctions
 * (by adding it to the frame config struct?)
 *
 */

/**
 * @brief function that searches for map
 * identifiers, ignoring spaces
 * (| tabs | \n )
 * at the beginning of the line
 *
 * @return 0 in case NO identifier was found,
 * 	1 if identifier was found
 *
 */
int	ft_search_map(char *line)
{
	int			i;

	i = ft_startjumper(line);
	if (line[i] != '0'
		&& line[i] != '1'
		&& line[i] != 'S'
		&& line[i] != 'N'
		&& line[i] != 'E'
		&& line[i] != 'W')
		return (0);
	return (1);
}

/**
 * @brief function that searches in input file for floor and ceiling
 * identifier ("F" / "C"), it ignores spaces
 * (| tabs | \n ) at the beginning of the line, 
 * if it founds identifier although it was already defined it returns an error
 *
 * @param p_config pointer to the config-struct that keeps all 
 * information of input file that is required for the game
 * @param line the line of the input file that has to be checked
 * @param fd file descriptor of input file (to close in case of error)
 * for color identifiers
 * 
 * @return 0 in case NO identifier was found,
 * 	1 if identifier was found
 */
static int	ft_search_colors(t_gamedata *config, char *line, int fd)
{
	int		i;

	i = ft_startjumper(line);
	if (!ft_strncmp(&line[i], "F ", 2) && config->floor)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(8, ft_strdup("floor color"), config);
	}
	else if (!ft_strncmp(&line[i], "C ", 2) && config->ceiling)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(8, ft_strdup("ceiling color"), config);
	}
	else if (!ft_strncmp(&line[i], "F ", 2)
		|| !ft_strncmp(&line[i], "C ", 2))
		return (1);
	return (0);
}

/**
 * @brief checks if there are several identifiers for same
 * type of texture
 * (helper function for ft_search_textures)
 */
static void	ft_texture_duplicate_check(t_gamedata *config, 
			char *line, int fd, int i)
{
	if (!ft_strncmp(&line[i], "NO ", 3) && config->t_north)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(8, ft_strdup("NORTH texture"), config);
	}
	else if (!ft_strncmp(&line[i], "SO ", 3) && config->t_south)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(8, ft_strdup("SOUTH texture"), config);
	}
	else if (!ft_strncmp(&line[i], "WE ", 3) && config->t_west)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(8, ft_strdup("WEST texture"), config);
	}
	else if (!ft_strncmp(&line[i], "EA ", 3) && config->t_east)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(8, ft_strdup("EAST texture"), config);
	}
}

/**
 * @brief function that searches in input file for texture
 * identifiers and checks if this identifier has already been
 * defined (== not clear definition of corresponding texture
 * identifier -> error message and exit)
 * 
 * @param fd file descriptor of input file (to close in case of error)
 * @param line line from input file that was read by gnl-function
 * @param p_config pointer to the config-struct that keeps all 
 * information of input file that is required for the game
 * 
 * @return 0 in case NO identifier was found,
 * 	1 if identifier was found
 */
static int	ft_search_textures(t_gamedata *config, char *line, int fd)
{
	int	i;

	i = ft_startjumper(line);
	ft_texture_duplicate_check(config, line, fd, i);
	if (!ft_strncmp(&line[i], "NO ", 3)
		|| (!ft_strncmp(&line[i], "SO ", 3))
		|| (!ft_strncmp(&line[i], "WE ", 3))
		|| (!ft_strncmp(&line[i], "EA ", 3)))
		return (1);
	return (0);
}

/**
 * @brief loop to read content of input file (line per line).
 * it checks for identifiers to fill struct for game config
 * if it finds map content, the loop will end, as the map
 * has to be the last part in input file as per requirements
 * (therefore following content (lines) will be read in ft_set_map
 * and content of char *line of this function will be used for map
 * creation or freed in ft_set_map if an error occurs)
 *
 * @param fd file descriptor of input file (for gnl-function)
 * @param p_config pointer to the config-struct that keeps all 
 * information of input file that is required for the game
 */
void	ft_gnl_infileloop(int fd, t_gamedata **p_config)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_search_textures(*p_config, line, fd))
			ft_set_texture(p_config, line, fd);
		else if (ft_search_map(line) && ft_map_is_last(*p_config))
		{
			ft_set_map(p_config, line, fd);
			if (!ft_player_check(*p_config, fd))
			{
				close (fd);
				ft_error_handling(11, NULL, *p_config);
			}
			break ;
		}
		else if (ft_search_colors(*p_config, line, fd))
			ft_set_color(p_config, line, fd);
		free(line);
	}
}
