/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:58:33 by mstracke          #+#    #+#             */
/*   Updated: 2025/02/05 17:13:29 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	(void)av;
	if (ac == 2)
	{
		if (ft_extension_check(av[1]))
		{
			dprintf(2, "wrong file format, please use extension \".cub\"\n");
			return (1);
		}
		dprintf(1, "correct no of arguments for gaming fun\n");
		return (0);
	}
	dprintf(2, "please enter valid no of arguments for gaming fun (==1) \n");
	return (1);

}
