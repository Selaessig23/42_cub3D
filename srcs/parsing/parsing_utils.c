#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file keeps small simple functions that
 * are used by several other functions in different files
 */

/**
 * @brief this functions returns a start index to jump
 * over spaces, 
 * (newlines and tabs) 
 * at the beginning of a string
 */
int	ft_startjumper(char *str)
{
	int	i;

	i = 0;
	while (str[i] 
		&& ((str[i] == ' ')
		//	|| (str[i] >= 9 && str[i] <= 12)
		))
		i += 1;
	return (i);
}


/**
 * function to create an index for the map check
 * 
 * NOT NECESSARY -> a more convenient solution was found to 
 * avoid having more than 5 arguments in enclosure.c for carve-checks
 */
// void	ft_zero_index(char **index)
// {
// 	int		i;

// 	i = 0;
// 	while (index[i])
// 	{
// 		ft_memset(index[i], '-', ft_strlen(index[i]));
// 		i += 1;
// 	}
// }

/**
 * @brief function to re-establish the map for carve-checks
 * after having destroyed it in the previous carve-check
 */
void	ft_refill_map(char **dest, char **src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		ft_strncpy(dest[i], src[i], ft_strlen(src[i]));
		i += 1;
	}
	dest[i] = NULL;
}
