#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file extracts all important information of the infile
 * sent by command line argument 2 to assign all required
 * values for game config struct.
 * if some information were missing in input file and therfor 
 * some of the config variables could not been set up
 * an error will be returned and the program exits.
 * 
 * 
 * PROBLEM to solve: how to close the infile fd 
 * in case of an error in one of the subfunctions 
 * (by adding it to the frame config struct?)
 * 
 */

/**
 * @brief final check if all necessary variables
 * for game configuration have been assigned,
 * otherwise send error message to ft_error_handling
 * (where everything gets freed and program exits)
 * 
 * CHECK: up to now all colors for ceiling and floor have to be
 * assigned, no value is not accepted 
 * (could be adapted to no value == 0, if desired)
 */
int	ft_config_set_complete(t_gamedata *config)
{
	// ft_testprint(config);
	if (!config->fd_north)
		ft_error_handling(5, ft_strdup("Path north texture"), config);
	if (!config->fd_south)
		ft_error_handling(5, ft_strdup("Path south texture"), config);
	if (!config->fd_east)
		ft_error_handling(5, ft_strdup("Path east texture"), config);
	if (!config->fd_west)
		ft_error_handling(5, ft_strdup("Path west texture"), config);
	if (!config->floor)
		ft_error_handling(5, ft_strdup("Floor color"), config); 
	if (!config->ceiling)
		ft_error_handling(5, ft_strdup("Ceiling color"), config); 
	if (!config->map)
		ft_error_handling(5, ft_strdup("Map"), config);
	//ft_dprintf(1, "%i\n", config->fd_east);
	return (1);
}

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
 * identifier ("F" / "C")
 * 
 * @param line the line of the input file to check for color identifiers
 */
static int	ft_search_colors(t_gamedata *config, char *line, int fd)
{
	int		i;

	i = ft_startjumper(line);
	if (!ft_strncmp(&line[i], "F", 1) && config->floor)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(8, ft_strdup("floor color"), config);
	}
	else if (!ft_strncmp(&line[i], "C", 1) && config->ceiling)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(8, ft_strdup("ceiling color"), config);
	}
	else if (!ft_strncmp(&line[i], "F", 1)
		|| !ft_strncmp(&line[i], "C", 1))
		return (1);
	return (0);
}


/**
 * @brief function that searches in input file for textures
 * identifiers and checks if this identifier has already been 
 * defined (==nor clear definition of corresponding texture
 * identifier -> error message and exit)
 */
static int	ft_search_textures(t_gamedata *config, char *line, int fd)
{
	int	i;

	i = ft_startjumper(line);
	if (!ft_strncmp(&line[i], "NO", 2) && config->fd_north)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(8, ft_strdup("NORTH texture"), config);
	}
	else if (!ft_strncmp(&line[i], "SO", 2) && config->fd_south)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(8, ft_strdup("SOUTH texture"), config);
	}
	else if (!ft_strncmp(&line[i], "WE", 2) && config->fd_west)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(8, ft_strdup("WEST texture"), config);
	}
	else if (!ft_strncmp(&line[i], "EA", 2) && config->fd_east)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(8, ft_strdup("EAST texture"), config);
	}
	else if (!ft_strncmp(&line[i], "NO", 2)
		|| (!ft_strncmp(&line[i], "SO", 2))
		|| (!ft_strncmp(&line[i], "WE", 2))
		|| (!ft_strncmp(&line[i], "EA", 2)))
		return (1);
	return (0);
}

void	ft_gnl_infileloop(int fd, t_gamedata **p_config)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		// if (*line)
		// {
		if (ft_search_textures(*p_config, line, fd))
			ft_set_texture(p_config, line, fd);
		else if (ft_search_map(line))
		{
			ft_set_map(p_config, line, fd);
			// free(line);
			break ;
		}
		else if (ft_search_colors(*p_config, line, fd))
			ft_set_color(p_config, line, fd);
		// printf("test2\n");
		// }
		free(line);
	}
}

/**
 * @brief function that sets the game config by reading from
 * input file (of command line argument) and sorting content 
 * to required variables summarized in struct t_gamedata
 * 
 * allocated memory for t_gamedata *config will be freed in main
 * 
 * CHECK how to distinguish between malloc error in gnl and eol of file?
 * 
 */
t_gamedata	*ft_initiate_data(int fd)
{
	t_gamedata	*config;

	config = ft_calloc(1, sizeof(t_gamedata));
	if (!config)
		ft_error_handling(9, NULL, NULL);
	ft_gnl_infileloop(fd, &config);
	if (!ft_config_set_complete(config))
		return (NULL);
	else
		return (config);
}
