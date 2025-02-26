#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file creates a (cleaned) map out of the input file,
 * assigns it to the game config struct and checks for
 * errors (validation of map)
 * 
 * CHECK: the algorithm will stop using input from the file
 * until end of file | newline was found | wrong letter was found
 * --> correct / desired behaviour?
 */

/**
 * @brief function to check the line of map for valid characters
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
 * @brief function that checks if there is a 
 * player AND if there is only one player
 * 
 * integrated a ternary (conditional) operator
 * to save space for return value
 * (conditions automatically return 1 for true and 0 for false)
 */
int	ft_player_check(t_gamedata *config, int fd, char **map_cpy)
{
	int	p;

	p = 0;
	while (*map_cpy)
	{
		while (**map_cpy)
		{
			if (**map_cpy == 'N' || **map_cpy == 'S'
				|| **map_cpy == 'W' || **map_cpy == 'E')
			{
				if (p == 0)
					p = 1;
				else
				{
					ft_free(map_cpy);
					close (fd);
					ft_error_handling(11, NULL, config);
				}
			}
			*map_cpy += 1;
		}
		map_cpy += 1;
	}
	return (p == 1);
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
	char		**map_cpy;

	config = *p_config;
	// index = NULL;
	map_cpy = NULL;
	if (!ft_map_valid_check(line))
	{
		ft_freeing_support(fd, line);
		ft_error_handling(7, NULL, *p_config);
	}
	map_clean = ft_gnl_maploop(line, fd, p_config);
	config->map = ft_split(map_clean, '\n');
	// index = ft_split(map_clean, '\n');
	map_cpy = ft_split(map_clean, '\n');
	free(map_clean);
	// ft_zero_index(index);
	// ft_testprint_maparray(config->map);
	if (!ft_wall_check(*p_config, fd, map_cpy)
		&& !ft_player_check(*p_config, fd, map_cpy))
	{
		// ft_free(index);
		ft_free(map_cpy);
		close (fd);
		ft_error_handling(11, NULL, *p_config);
	}
	// printf("hello 3\n");
	// ft_free(index);
	ft_free(map_cpy);
	return (1);
}
