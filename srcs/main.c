/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:58:33 by mstracke          #+#    #+#             */
/*   Updated: 2025/02/17 14:43:55 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	int				fd;
	t_gamedata		*config;

	fd = 0;
	config = NULL;
	if (ac == 2)
	{
		if (!ft_extension_check(av[1]))
			fd = ft_access_check(av[1]);
		dprintf(1, "correct no of arguments and correct extension "
			"for gaming fun, fd: %i\n", fd);
		config = ft_initiate_data(fd);
		// printf("test x\n");
		close (fd);
		ft_testprint(config);
		ft_free_config(config);
		return (0);
	}
	ft_error_handling(0, NULL, NULL);
}
