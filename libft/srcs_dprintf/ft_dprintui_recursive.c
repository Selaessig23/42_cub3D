/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:06:22 by mstracke          #+#    #+#             */
/*   Updated: 2024/01/22 16:06:41 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	ft_countui(unsigned int help)
{
	int	i;

	i = 0;
	if (help == 0)
		i++;
	else
	{
		while (help != 0)
		{
			help /= 10;
			i++;
		}
	}
	return (i);
}

static void	ft_writeui(int fd, unsigned int help)
{
	if (help > 9)
	{
		ft_writeui(fd, help / 10);
		ft_putchar_fd(((help % 10) + '0'), fd);
	}
	else
		ft_putchar_fd(((help % 10) + '0'), fd);
}

int	ft_dprintui(int fd, va_list args)
{
	unsigned int	help;

	help = va_arg(args, unsigned int);
	if (help == 0)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	ft_writeui(fd, help);
	return (ft_countui(help));
}
