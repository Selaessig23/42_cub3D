/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:07:46 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/07 15:14:01 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file assigns texture-paths to game-config-struct
 * if the path is correct and file is readable,
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
	if (!ft_strncmp(&line[ft_startjumper(line)], "NO", 2))
		config->t_north = path_texture;
	else if (!ft_strncmp(&line[ft_startjumper(line)], "SO", 2))
		config->t_south = path_texture;
	else if (!ft_strncmp(&line[ft_startjumper(line)], "WE", 2))
		config->t_west = path_texture;
	else if (!ft_strncmp(&line[ft_startjumper(line)], "EA", 2))
		config->t_east = path_texture;
}

/**
 * @brief function that checks extension of texture-
 * path (must be .png). 
 * 
 * @return if png it returns 1, if not png it returns 0
 */
int	ft_check_texture_extension(char *path_texture)
{
	if (!ft_strncmp(&path_texture[ft_strlen(path_texture) - 4], 
			".png", 4))
		return (1);
	else
		return (0);
}

/**
 * @brief function to extract the path of line 
 * with texture-identifier of input file
 * 
 * @param start the index after the texture-identifier
 */
char	*ft_create_texture_path(t_gamedata **p_config, int fd, char *line, 
	int start)
{
	char	*path_texture;
	int		j;

	path_texture = NULL;
	j = start + 1;
	while (line[j] && line[j] != ' ' 
		&& !(line[j] > 9 && line[j] < 12))
		j += 1;
	path_texture = ft_substr(line, start, j - start);
	if (!path_texture)
	{
		ft_freeing_support(fd, line);
		ft_error_handling(9, NULL, *p_config);
	}
	if (line[j - start])
		path_texture[j - start] = '\0';
	return (path_texture);
}

/**
 * @brief function that checks for the path of the texture in
 * input file and sends the path to ft_open_texture(p_config, line, temp)
 * to check accessibility of the file and assign path to the config struct
 * 
 * it will ignore all spaces in between identifier and value 
 * (according startjumper)
 * 
 * consider: in case of extension error of texture (non-png), texture-path
 * will be freed in ft_error_handling
 */

void	ft_set_texture(t_gamedata **p_config, char *line, int fd)
{
	int			i;
	char		*path_texture;

	i = ft_startjumper(line);
	i += 2;
	path_texture = NULL;
	i += ft_startjumper(&line[i]);
	if (!line[i] || line[i] == '\n')
	{
		path_texture = ft_substr(line, 0, 2);
		ft_freeing_support(fd, line);
		ft_error_handling(4, path_texture, *p_config);
	}
	path_texture = ft_create_texture_path(p_config, fd, line, i);
	if (!ft_check_texture_extension(path_texture))
	{
		ft_freeing_support(fd, line);
		ft_error_handling(13, path_texture, *p_config);
	}
	ft_check_and_assign_path_texture(p_config, line, path_texture, fd);
}
