#include "cub3d.h"

/**
 * @brief function that checks if there is a 
 * player AND if there is only one player
 * 
 * integrated a ternary (conditional) operator
 * to save space for return value
 * (conditions automatically return 1 for true and 0 for false)
 */
int	ft_player_check(t_gamedata *config, int fd, char **map_cpy)
{
	int		p;
	int		i;
	int		j;

	p = 0;
	i = 0;
	j = 0;
	while (map_cpy[i])
	{
		j = 0;
		while (map_cpy[i][j])
		{
			if (map_cpy[i][j] == 'N' || map_cpy[i][j] == 'S'
				|| map_cpy[i][j] == 'W' || map_cpy[i][j] == 'E')
			{
				if (p == 0)
					p = 1;
				else
				{
					ft_free(map_cpy);
					close (fd);
					ft_error_handling(12, NULL, config);
				}
			}
			j += 1;
		}
		i += 1;
	}
	return (p == 1);
}