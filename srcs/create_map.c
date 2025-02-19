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

static int	ft_wall_check(t_gamedata *config)
{
	if (config)
		return (1);
	else
		return (0);
}

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
		if (!ft_search_map(line))
			return (0);
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
	// pr!ntf("hello 2\n");
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
 */
int	ft_set_map(t_gamedata **p_config, char *line, int fd)
{
	t_gamedata	*config;
	char		**map_arr;

	config = *p_config;
	map_arr = NULL;
	config->map = ft_gnl_maploop(line, fd, p_config);
	// map_arr = ft_split(config->map, '\n');
	// ft_testprint_maparray(map_arr);
	// ft_free(map_arr);
	if (!ft_wall_check(*p_config))
		ft_error_handling(8, NULL, *p_config);
	// printf("hello 3\n");
	return (1);
}
