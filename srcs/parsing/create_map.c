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
 * @brief helper function for ft_map_enlarger, it allocates a new string
 * for new line in map with max length and fills the line with 
 * content of old line of map + spaces
 */
void	ft_realloc_mapline(t_gamedata **p_config, int fd, int index, int len)
{
	char		*new_mapline;
	char		*old_mapline;
	t_gamedata	*config;

	config = *p_config;
	old_mapline = config->map[index];
	new_mapline = (char *)malloc(sizeof(char) * len + 1);
	if (!new_mapline)
	{
		close (fd);
		ft_error_handling(9, NULL, *p_config);
	}
	ft_strcpy(new_mapline, old_mapline);
	ft_memset(&new_mapline[ft_strlen(old_mapline)], 
		' ', (len + 1) - ft_strlen(old_mapline));
	new_mapline[len] = '\0';
	config->map[index] = new_mapline;
	free(old_mapline);
}

/**
 * @brief function to increase the length of each string
 * (line) of the map to the max length of map array
 * 1st it checks for the max length of a line of map
 * 2nd it iterates through map to adapt each line to max length
 * (it length of line is smaller than max length)
 */
void	ft_map_enlarger(t_gamedata **p_config, int fd)
{
	t_gamedata	*config;
	size_t			len;
	int			i;

	config = *p_config;
	i = 0;
	len = 0;
	while (config->map[i])
	{
		if (ft_strlen(config->map[i]) > len)
			len = ft_strlen(config->map[i]);
		i += 1;
	}
	i = 0;
	while (config->map[i])
	{
		if (ft_strlen(config->map[i]) < len)
			ft_realloc_mapline(p_config, fd, i, len);
		i += 1;
	}
	//just for testing reasons
	// i = 0;
	// while (config->map[i])
	// {
	// 	printf("Length line %i: %li\n", i, ft_strlen(config->map[i]));
	// 	i += 1;
	// }
	// printf("Length array total %li\n", ft_arrlen(config->map));
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
	free(map_clean);
	if (!config->map)
	{
		close (fd);
		ft_error_handling(9, NULL, *p_config);
	}
	ft_map_enlarger(p_config, fd);
	map_cpy = ft_arrdup(config->map);
	if (!map_cpy)
	{
		close (fd);
		ft_error_handling(9, NULL, *p_config);
	}
	// index = ft_split(map_clean, '\n');
	// map_cpy = ft_split(map_clean, '\n');
	// ft_zero_index(index);
	// ft_testprint_maparray(config->map);
	if (!ft_wall_check(*p_config, fd, map_cpy)
		|| !ft_player_check(*p_config, fd))
	{
		// ft_free(index);
		ft_free(map_cpy);
		close (fd);
		ft_error_handling(11, NULL, *p_config);
	}
	// ft_free(index);
	ft_free(map_cpy);
	return (1);
}
