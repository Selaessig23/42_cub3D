#include "cub3d.h"


/**
 * DESCRIPTION:
 * this file assigns fd for texture-paths if
 * the path is correct and file is readable,
 * otherwise it will print an error message
 */

/**
 * @brief function to get fd of texture and assign it to 
 * the corresponding (direction) texture
 */
static void	ft_open_texture(t_gamedata **p_config, 
		char *line, char *temp, int fd_infile)
{
	t_gamedata	*config;
	int			fd_texture;

	config = *p_config;
	fd_texture = open(temp, O_RDONLY);
	if (fd_texture < 0)
	{
		ft_freeing_support(fd_infile, line);
		ft_error_handling(2, temp, *p_config);
	}
	if (read(fd_texture, NULL, 0) < 0)
	{
		ft_freeing_support(fd_infile, line);
		ft_error_handling(3, temp, *p_config);
	}
	if (!ft_strncmp(line, "NO", 2))
		config->fd_north = fd_texture;
	else if (!ft_strncmp(line, "SO", 2))
		config->fd_south = fd_texture;
	else if (!ft_strncmp(line, "WE", 2))
		config->fd_west = fd_texture;
	else if (!ft_strncmp(line, "EA", 2))
		config->fd_east = fd_texture;
	else
		printf("error: where which\n");
}

/**
 * @brief function that checks for the path of the texture in
 * input file and sends the path to ft_open_texture(p_config, line, temp)
 * to check accessibility of the file and assign a fd to the config struct
 */

void	ft_set_texture(t_gamedata **p_config, char *line, int fd)
{
	int			i;
	int			j;
	char		*temp;

	i = 2;
	j = 0;
	temp = NULL;
	// if (!line)
	// 	return ;
	//while (line[i] && ft_strncmp(&line[i], "./", 2))
	//what about tabs? line[i] >= 9 && line[i] <= 12
	while (line[i] && line[i] == ' ')
		i += 1;
	// printf("test0 A: %s -> %s\n", line, &line[i]);
	if (!&line[i])
	{
		ft_freeing_support(fd, line);
		ft_error_handling(4, ft_substr(line, 0, 2), *p_config);
	}
	j = i + 1;
	while (line[j] && line[j] != ' ' 
		&& !(line[j] > 9 && line[j] < 12))
		j += 1;
	temp = ft_substr(line, i, j);
	if (!temp)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(9, NULL, *p_config);
	}
	// printf("last char of temp: %i\n", temp[j - i]);
	if (line[j - i])
		temp[j - i] = '\0';
	ft_open_texture(p_config, line, temp, fd);
	free(temp);
}
