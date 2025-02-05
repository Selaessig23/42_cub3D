/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_input_check.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:43:02 by mstracke          #+#    #+#             */
/*   Updated: 2025/02/05 17:36:47 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_extension_check(char *input)
{
	if (ft_strncmp(&input[ft_strlen(input) - 4], ".cub", ft_strlen(".cub")))
		return (1);
	return (0);
}

