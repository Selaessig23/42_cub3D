/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:27:58 by mstracke          #+#    #+#             */
/*   Updated: 2024/01/18 13:28:47 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	ft_counthexa(unsigned int help)
{
	int	i;

	i = 0;
	if (help == 0)
		i++;
	else
	{
		while (help != 0)
		{
			help /= 16;
			i++;
		}
	}
	return (i);
}

static void	ft_writehexa(int fd, unsigned int help, char *hex)
{
	if (help > 15)
	{
		ft_writehexa(fd, (help / 16), hex);
		ft_putchar_fd(hex[help % 16], fd);
	}
	else
		ft_putchar_fd(hex[help], fd);
}

int	ft_dprinthexa(int fd, va_list args, char *hex)
{
	unsigned int	help;

	help = va_arg(args, unsigned int);
	if (help == 0)
		ft_putchar_fd('0', fd);
	else
		ft_writehexa (fd, help, hex);
	return (ft_counthexa(help));
}
