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
static void	ft_check_and_assign_path_texture(t_gamedata **p_config, 
	char *line, char *path_texture, int fd_infile)
{
	t_gamedata	*config;
	int			fd_texture;

	config = *p_config;
	fd_texture = open(path_texture, O_RDONLY);
	if (fd_texture < 0)
	{
		ft_freeing_support(fd_infile, line);
		ft_error_handling(2, path_texture, *p_config);
	}
	if (read(fd_texture, NULL, 0) < 0)
	{
		ft_freeing_support(fd_infile, line);
		ft_error_handling(3, path_texture, *p_config);
	}
	close (fd_texture);
	if (!ft_strncmp(line, "NO", 2))
		config->t_north = path_texture;
	else if (!ft_strncmp(line, "SO", 2))
		config->t_south = path_texture;
	else if (!ft_strncmp(line, "WE", 2))
		config->t_west = path_texture;
	else if (!ft_strncmp(line, "EA", 2))
		config->t_east = path_texture;
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
	char		*path_texture;

	i = 2;
	j = 0;
	path_texture = NULL;
	// if (!line)
	// 	return ;
	//while (line[i] && ft_strncmp(&line[i], "./", 2))
	//what about tabs? line[i] >= 9 && line[i] <= 12
	while (line[i] && line[i] == ' ')
		i += 1;
	// printf("test0 A: %s -> %s\n", line, &line[i]);
	if (!line[i] || line[i] == '\n')
	{
		path_texture = ft_substr(line, 0, 2);
		ft_freeing_support(fd, line);
		ft_error_handling(4, path_texture, *p_config);
	}
	j = i + 1;
	while (line[j] && line[j] != ' ' 
		&& !(line[j] > 9 && line[j] < 12))
		j += 1;
	path_texture = ft_substr(line, i, j);
	if (!path_texture)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(9, NULL, *p_config);
	}
	// printf("last char of temp: %i\n", temp[j - i]);
	if (line[j - i])
		path_texture[j - i] = '\0';
	ft_check_and_assign_path_texture(p_config, line, path_texture, fd);
	// free(temp);
}
