/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:58:33 by mstracke          #+#    #+#             */
/*   Updated: 2025/02/05 17:39:35 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	(void)av;
	if (ac == 2)
	{
		if (ft_extension_check(av[1]))
			ft_error_handling(1);
		dprintf(1, "correct no of arguments and correct extension for gaming fun\n");
		return (0);
	}
	ft_error_handling(0);

}
