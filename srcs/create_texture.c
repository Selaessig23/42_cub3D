#include "cub3d.h"

/**
 * @brief function to get fd of texture and assign it to 
 * the corresponding (direction) texture
 */
static void	ft_open_texture(t_gamedata **p_config, char *line, char *temp)
{
	t_gamedata	*config;
	int			fd;

	config = *p_config;
	// printf("%s\n", temp);
	// printf("%s\n", "/home/mstracke/development/cub3D/test/blue_stone.xpm");
	// fd = open("/home/mstracke/development/cub3D/test/blue_stone.xpm", O_RDONLY);
	fd = open(temp, O_RDONLY);
	// printf("%i\n", fd);
	if (fd < 0)
	{
		free(line);
		ft_error_handling(2, temp, *p_config);
	}
	if (read(fd, NULL, 0) < 0)
	{
			free(line);
			ft_error_handling(3, temp, *p_config);
	}
	if (!ft_strncmp(line, "NO", 2))
		config->fd_north = fd;
	else if (!ft_strncmp(line, "SO", 2))
		config->fd_south = fd;
	else if (!ft_strncmp(line, "WE", 2))
		config->fd_west = fd;
	else if (!ft_strncmp(line, "EA", 2))
		config->fd_east = fd;
	else
		printf("where which\n");
}

/**
 * @brief function that checks for the path of the file of the 
 * texture and sends this to ft_open_texture(p_config, line, temp)
 * to check the file and assign a fd to the config struct
 */

void	ft_create_texture(t_gamedata **p_config, char *line)
{
	// t_gamedata	*config;
	int			i;
	int			j;
	char		*temp;

	// config = *p_config;
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
		free(line);
		ft_error_handling(4, ft_substr(line, 0, 2), *p_config);
	}
	j = i + 1;
	while (line[j] && line[j] != ' ' 
		&& !(line[j] > 9 && line[j] < 12))
		j += 1;
	temp = ft_substr(line, i, j);
	if (!temp)
	{
		free(line);
		ft_error_handling(9, NULL, *p_config);
	}
	// printf("last char of temp: %i\n", temp[j - i]);
	if (line[j - i])
		temp[j - i] = '\0';
	ft_open_texture(p_config, line, temp);
	free(temp);
}
