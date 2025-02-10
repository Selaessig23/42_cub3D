/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:58:33 by mstracke          #+#    #+#             */
/*   Updated: 2025/02/10 11:59:53 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	int	fd;

	fd = 0;
	if (ac == 2)
	{
		if (!ft_extension_check(av[1]))
			fd = ft_access_check(av[1]);
		dprintf(1, "correct no of arguments and correct extension "
			"for gaming fun, fd: %i\n", fd);
		// ft_initiate_data(fd);
		close (fd);
		return (0);
	}
	ft_error_handling(0);

}
