#include "cub3d.h"

/**
 * DESCRIPTION:
 * this file creates a (cleaned) map out of the input file,
 * assigns it to the game config struct and checks for
 * errors (validation of map)
 * 
 * CHECK: the algorithm will stop using input from the file
 * until end of file | newline was found | wrong letter was found
 * --> correct / desired behaviour?
 */

/**
 * @brief function that assigns the content of input file,
 * identified as part of map (last part of content in file, 
 * allowed characters: 0, 1, N, S, E, W)
 * 
 * CHECK: DO I need to delete the \n of last char of last line?
 */
int	ft_set_map(t_gamedata **p_config, char *line, int fd)
{
	t_gamedata	*config;
	char		*temp1;
	char		*temp2;
	// char	*temp3;

	config = *p_config;
	temp2 = NULL;
	temp1 = ft_strdup(line);
	//than I do not need to free gnl-line in initiate_data-function
	// temp1 = line;
	if (!temp1)
	{
		free(line);
		ft_error_handling(9, NULL, *p_config);
	}
	// printf("hi\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else if (*line == '\n' || *line == '\0'
			|| !ft_search_map(line))
		{
			printf("test\n");
			free(line);
			break ;
		}
		else
		{
			// maybe use ft_strlcat(temp1, line, (ft_strlen(temp1) + ft_strlen(line) + 1)) instead
			//(difficult without being able to use realloc)
			// ft_strlcat(temp1, line, (ft_strlen(temp1) + ft_strlen(line) + 1));
			temp2 = temp1;
			temp1 = ft_strjoin(temp2, line);
			free(temp2);
			free(line);
			// printf("hello 2\n");
			if (!temp1)
				ft_error_handling(9, NULL, *p_config);
		}
	}
	config->map = temp1;
	// printf("hello 3\n");
	return (1);
}
