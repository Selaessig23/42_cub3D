/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:57:07 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/07 11:09:35 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file creates a (cleaned) map out of the input file,
 * assigns it to the game config struct and checks for
 * errors (validation of map)
 * 
 * CHECK: the algorithm will stop using input from the file
 * until end of file | (empty line = newline) was found 
 * | wrong letter was found at beginning of line
 * everything comes after will be simply ignored
 * CHECK: --> correct / desired behaviour? 
 * (it would also be possible to return an error instead 
 * simply exlcuding it from map creation, except
 * case of eof)
 */

static void	ft_improve_and_check_map(t_gamedata **p_config, int fd)
{
	t_gamedata	*config;
	char		**map_cpy;

	config = *p_config;
	ft_map_enlarger(p_config, fd);
	map_cpy = ft_arrdup(config->map);
	if (!map_cpy)
	{
		close (fd);
		ft_error_handling(9, NULL, *p_config);
	}
	// ft_testprint_maparray(config->map);
	ft_wall_check(*p_config, fd, map_cpy);
	ft_free(map_cpy);
}

/**
 * @brief function to check the line of map for valid characters
 * 
 * CHECK: maybe integrate space_jump here as well
 * 
 * @return returns 1 if map is valid
 * 0 if NOT valid
*/ 
static int	ft_map_valid_check(char *line)
{
	while (*line)
	{
		if (*line == '\n')
			return (1);
		if (*line == ' ')
			line += 1;
		else if (!ft_search_map(line))
			return (0);
		else
			line += 1;
	}
	return (1);
}
/**
 * @brief adds a new line of input (gnl) to existing string
 */
char	*ft_concat(char *str_old, char *str_toadd, t_gamedata **p_config)
{
	char	*temp;
	char	*str_new;

	// maybe use ft_strlcat(temp1, line, (ft_strlen(temp1) + ft_strlen(line) + 1)) instead
	//(difficult without being able to use realloc)
	// ft_strlcat(temp1, line, (ft_strlen(temp1) + ft_strlen(line) + 1));
	temp = str_old;
	str_new = ft_strjoin(str_old, str_toadd);
	free(temp);
	free(str_toadd);
	// printf("hello 2\n");
	if (!str_new)
		ft_error_handling(9, NULL, *p_config);
	return (str_new);
}

/**
 * @brief function to loop through the end of input file,
 * which has to be the map input, and use each line for
 * map char creation until eol or invalid character
 */
static char	*ft_gnl_maploop(char *map, int fd, t_gamedata **p_config)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else if (*line == '\n' || *line == '\0')
		{
			ft_freeing_support(fd, line);
			break ;
		}
		else if (!ft_map_valid_check(line))
		{
			ft_freeing_support(fd, line);
			free(map);
			map = NULL;
			ft_error_handling(7, NULL, *p_config);
		}
		else
			map = ft_concat(map, line, p_config);
	}
	return (map);
}

/**
 * @brief function that assigns the content of input file,
 * identified as part of map (last part of content in file, 
 * allowed characters: 0, 1, N, S, E, W)
 * 
 * CHECK: DO I need to delete the \n of last char of last line?
 * (NO in case of creating an array of chars out of it, then using it
 * as a delimiter for split)
 */
int	ft_set_map(t_gamedata **p_config, char *line, int fd)
{
	t_gamedata	*config;
	char		*map_clean;
	//char		**index;
	// char		**map_cpy;

	config = *p_config;
	// index = NULL;
	// map_cpy = NULL;
	if (!ft_map_valid_check(line))
	{
		ft_freeing_support(fd, line);
		ft_error_handling(7, NULL, *p_config);
	}
	map_clean = ft_gnl_maploop(line, fd, p_config);
	config->map = ft_split(map_clean, '\n');
	free(map_clean);
	if (!config->map)
	{
		close (fd);
		ft_error_handling(9, NULL, *p_config);
	}
	ft_improve_and_check_map(p_config, fd);
	// ft_map_enlarger(p_config, fd);
	// map_cpy = ft_arrdup(config->map);
	// if (!map_cpy)
	// {
	// 	close (fd);
	// 	ft_error_handling(9, NULL, *p_config);
	// }
	// // index = ft_split(map_clean, '\n');
	// // map_cpy = ft_split(map_clean, '\n');
	// // ft_zero_index(index);
	// // ft_testprint_maparray(config->map);
	// ft_wall_check(*p_config, fd, map_cpy);
	// // ft_free(index);
	// // printf("x_config = %f\n", config->player.pos.x);
	// // printf("y_config = %f\n", config->player.pos.y);
	// ft_free(map_cpy);
	return (1);
}
