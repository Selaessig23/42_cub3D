#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file keeps small simple functions that
 * are used by several other functions in different files
 */

/**
 * @brief this functions returns a start index to jump
 * over spaces, newlines and tabs at the beginning of a string
 */
int	ft_startjumper(char *str)
{
	int	i;

	i = 0;
	while (str[i] 
		&& ((str[i] == ' ')
			|| (str[i] >= 9 && str[i] <= 12)))
		i += 1;
	return (i);
}
