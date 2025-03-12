#include "cub3d.h"

/**
 * DESCRIPTION:
 * in this file the map is checked for valid player information
 * and if valid, the player's position is set if
 */

/**
 * @brief function to set players direction
 * (helper function for ft_set_player)
 */
static void	ft_set_players_dir(t_gamedata **p_config, char dir)
{
	t_gamedata	*config;
	t_player	p;
	t_vector2	player_dir;

	config = *p_config;
	p = config->player;
	player_dir = p.dir;
	if (dir == 'N')
	{
		player_dir.x = 0;
		player_dir.y = 1;
	}
	else if (dir == 'E')
	{
		player_dir.x = -1;
		player_dir.y = 0;
	}
	else if (dir == 'S')
	{
		player_dir.x = 0;
		player_dir.y = -1;
	}
	else if (dir == 'W')
	{
		player_dir.x = 1;
		player_dir.y = 0;
	}
}

/**
 * @brief function to set the players position and direction
 * 
 */
static void	ft_set_player(t_gamedata **p_config, int x, int y, char dir)
{
	t_gamedata	*config;
	t_player	p;
	t_vector2	player_pos;
	// t_vector2	player_dir;


	config = *p_config;
	p = config->player;
	player_pos = p.pos;
	// player_dir = p.dir;
	player_pos.x = x;
	player_pos.y = y;
	ft_set_players_dir(p_config, dir);
}

/**
 * @brief function that checks if a player already exists,
 * if yes it exists the programm and returns error message
 * otherwiese it returns 1
 */
static int	ft_check_for_player_duplicates(t_gamedata *config, int fd)
{
	t_player	p;
	t_vector2	player_pos;


	p = config->player;
	player_pos = p.pos;
	if (player_pos.x && player_pos.y)
	{
		//ft_free(map_cpy);
		close (fd);
		ft_error_handling(12, NULL, config);
	}
	return (1);
}

/**
 * @brief function that checks if there is a 
 * player AND if there is only one player
 * 
 * integrated a ternary (conditional) operator
 * to save space for return value
 * (conditions automatically return 1 for true and 0 for false)
 */
int	ft_player_check(t_gamedata *config, int fd)
{
	int		p;
	int		i;
	int		j;

	p = 0;
	i = 0;
	j = 0;
	while (config->map[i])
	{
		j = 0;
		while (config->map[i][j])
		{
			if (config->map[i][j] == 'N' || config->map[i][j] == 'S'
				|| config->map[i][j] == 'W' || config->map[i][j] == 'E')
			{
				p = ft_check_for_player_duplicates(config, fd);
				ft_set_player(&config, j, i, config->map[i][j]);
			}
			j += 1;
		}
		i += 1;
	}
	return (p == 1);
}
