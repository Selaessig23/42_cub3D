/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_input_check.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:43:02 by mstracke          #+#    #+#             */
/*   Updated: 2025/02/17 14:43:54 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief checks if input file is accessible and readable
 * 
 * @return returns a file descriptor to opened input file 
 * with reading rights
 */
int	ft_access_check(char *inputfile)
{
	int	fd;

	fd = open(inputfile, O_RDONLY);
	if (fd < 0)
		ft_error_handling(2, strdup(inputfile), NULL);
	if (read(fd, NULL, 0) < 0)
		ft_error_handling(3, strdup(inputfile), NULL);
	return (fd);
}

/**
 * @brief checks the extension of input file (must be .cub)
 * 
 * IDEA: maybe directly send to error_handling in case of check fails
 * 
 * @param input second argument of command line input
 */
int	ft_extension_check(char *input)
{
	if (ft_strncmp(&input[ft_strlen(input) - 4], ".cub", ft_strlen(".cub")))
		ft_error_handling(1, NULL, NULL);
	return (0);
}

