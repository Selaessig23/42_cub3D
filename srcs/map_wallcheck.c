#include "cub3d.h"

/**
 * DESCRIPTION: 
 * file to check if the map is closed/surrounded by walls, 
 * if not the program must returns an errormessage and exits.
 */

int	ft_west_check(t_gamedata *config)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (config->map[i] && config->map[i][j])
	{
		j = 0;
		while (config->map[i][j] && config->map[i][j] == ' ')
			j += 1;
		if (config->map[i][j] != '1')
			return (0);
		if (config->map[i][j] == '1')
			i += 1;
	}
	return (1);
}

int	ft_east_check(t_gamedata *config)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (config->map[i] && config->map[i][j])
	{
		j = ft_strlen(config->map[i]) - 1;
		while (j >= 0 && config->map[i][j] == ' ')
			j -= 1;
		if (config->map[i][j] != '1')
			return (0);
		if (config->map[i][j] == '1')
			i += 1;
		if (config->map[i] && config->map[i + 1])
			j = ft_strlen(config->map[i + 1]) - 1;
	}
	// printf("test1\n");
	return (1);
}

int	ft_north_check(t_gamedata *config)
{
	int		i;
	int		j;
	int		k;

	i = ft_arrlen(config->map) - 1;
	j = 0;
	k = 0;
	while (config->map[i][j])
	{
		k = i;
		while (i >= 0 && config->map[i][j] == ' ')
			i -= 1;
		if (config->map[i][j] != '1')
			return (0);
		if (config->map[i][j] == '1')
			j++;
		i = k;
	}
	return (1);
}

int	ft_south_check(t_gamedata *config)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (config->map[i][j])
	{
		k = i;
		while (config->map[i][j] && config->map[i][j] == ' ')
			i += 1;
		if (config->map[i][j] != '1')
			return (0);
		if (config->map[i][j] == '1')
			j++;
		i = k;
	}
	return (1);
}

int	ft_wall_check(t_gamedata *config, int fd)
{
	int		i;

	i = 0;
	if (!ft_south_check(config))
	{
		close(fd);
		ft_error_handling(10, ft_strdup("SOUTH"), config);
	}
	else if (!ft_north_check(config))
	{
		close(fd);
		ft_error_handling(10, ft_strdup("NORTH"), config);
	}
	else if (!ft_east_check(config))
	{
		close(fd);
		ft_error_handling(10, ft_strdup("EAST"), config);
	}
	else if (!ft_west_check(config))
	{
		close(fd);
		ft_error_handling(10, ft_strdup("WEST"), config);
	}
	return (1);
}
