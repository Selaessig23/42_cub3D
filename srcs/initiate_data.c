#include "cub3d.h"

int	ft_config_set_complete(t_gamedata *config)
{
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
 * @brief
 */
static int	ft_search_map(t_gamedata **p_config, char *line, int fd)
{
	t_gamedata	*config;
	char		*temp1;
	char		*temp2;
	// char	*temp3;

	temp1 = NULL;
	temp2 = NULL;
	config = *p_config;
	// if (!line)
	// 	return (0);
	// if (ft_strncmp(line, "O", 1)
	// 	&& ft_strncmp(line, "1", 1)
	// 	&& ft_strncmp(line, "S", 1)
	// 	&& ft_strncmp(line, "N", 1)
	// 	&& ft_strncmp(line, "E", 1)
	// 	&& ft_strncmp(line, "W", 1))
	// 	return (0);
	if (*line != 'O'
		&& *line != '1'
		&& *line != 'S'
		&& *line != 'N'
		&& *line != 'E'
		&& *line != 'W')
		return (0);
	temp1 = ft_strdup(line);
	if (!temp1)
		ft_error_handling(9, NULL, *p_config);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp2 = temp1;
		temp1 = ft_strjoin(temp2, line);
		free(temp2);
		free(line);
		// printf("hello 2\n");
		if (!temp1)
			ft_error_handling(9, NULL, *p_config);
	}
	config->map = temp1;
	// printf("hello 3\n");
	return (1);
}

/**
 * @brief (helper) function that sets the color for floor and ceiling
 */
static void	ft_set_color(t_gamedata **p_config, char *content, char c)
{
	t_gamedata	*config;
	t_color		*color;
	char 		*temp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	temp = NULL;
	config = *p_config;
	color = ft_calloc(1, sizeof(t_color));
	if (!color)
		ft_error_handling(9, NULL, *p_config);
	while (ft_isdigit(content[j]))
		j += 1;
	temp = ft_substr(content, 0, j);
	if (!temp)
	{
		free(color);
		free(content);
		//free(line);
		ft_error_handling(9, NULL, *p_config);
	}
	color->red = ft_atoi(temp);
	free(temp);
	j += 1;
	i = j;
	while (ft_isdigit(content[j]))
		j += 1;
	temp = ft_substr(content, i, j);
	if (!temp)
	{
		free(color);
		free(content);
		//free(line);
		ft_error_handling(9, NULL, *p_config);
	}
	color->green = ft_atoi(temp);
	free(temp);
	j += 1;
	i = j;
	while (ft_isdigit(content[j]))
		j += 1;
	temp = ft_substr(content, i, j);
	if (!temp)
	{
		free(color);
		free(content);
		//free(line);
		ft_error_handling(9, NULL, *p_config);
	}
	color->blue = ft_atoi(temp);
	free(temp);
	if (c == 'C')
		config->ceiling = color;
	else
		config->floor = color;
}

/**
 * @brief function that searches in input file for floor and ceiling 
 * identifier
 */
static void	ft_search_colors(t_gamedata **p_config, char *line)
{
	// t_gamedata	*config;
	int			i;
	char		*temp;

	temp = NULL;
	// config = *p_config;
	i = 1;
	// if (!line)
	// 	return ;
	if (!ft_strncmp(line, "F", 1)
		|| !ft_strncmp(line, "C", 1))
		while (ft_isdigit(line[i]))
			i += 1;
	else
		return ;
	if (!line[i])
		return ;
	temp = ft_strdup(&line[i]);
	if (!temp)
		ft_error_handling(9, NULL, *p_config);
	if (!ft_strncmp(line, "F", 1))
		ft_set_color(p_config, temp, 'F');
	else if (!ft_strncmp(line, "C", 1))
		ft_set_color(p_config, temp, 'C');
}


/**
 * @brief function that searches in input file for textures
 * identifiers
 */
static int	ft_search_textures(char *line)
{
	if (!ft_strncmp(line, "NO", 2)
		|| (!ft_strncmp(line, "SO", 2))
		|| (!ft_strncmp(line, "WE", 2))
		|| (!ft_strncmp(line, "EA", 2)))
		return (1);
	else
		return (0);
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
 * CHECK where to free the gnl-return and where to check for valid input
 */
t_gamedata	*ft_initiate_data(int fd)
{
	t_gamedata	*config;
	char		*line;
	char		*line_cpy;
	// int			gnl;

	line = NULL;
	// gnl = 0;
	line_cpy = NULL;
	config = ft_calloc(1, sizeof(t_gamedata));
	if (!config)
		ft_error_handling(9, NULL, NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line_cpy = line;
		while (*line 
			&& ((*line == ' ')
				|| (*line >= 9 && *line <= 12)))
			line += 1;
		if (line)
		{
			if (ft_search_textures(line))
				ft_create_texture(&config, line);
			else if (ft_search_map(&config, line, fd))
				break ;
			else
				ft_search_colors(&config, line);
			// printf("test2\n");
		}
		free(line_cpy);
	}
	// printf("test3\n");
	if (!ft_config_set_complete(config))
		return (NULL);
	else
		return (config);
}
