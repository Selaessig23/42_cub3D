/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:29:58 by mstracke          #+#    #+#             */
/*   Updated: 2025/02/05 16:30:01 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** DESCRIPTION:
 * Prints ARGUMENT(s) according to FORMAT to file descriptor
 * Valid formats: 
 * %c Prints a single character 
 * %s Prints a string (as defined by the common C convention) 
 * %p The void * pointer argument has to be printed in hexadecimal format 
 * %d Prints a decimal (base 10) number 
 * %i Prints an integer in base 10 
 * %u Prints an unsigned decimal (base 10) number 
 * %x Prints a number in hexadecimal (base 16) lowercase format 
 * %X Prints a number in hexadecimal (base 16) uppercase format 
 * %% Prints a percent sign.
 */

#include "ft_dprintf.h"

static int	ft_switch(int fd, char c, va_list args)
{
	if (c == 'c')
		return (ft_dprintchar(fd, args));
	else if (c == 's')
		return (ft_dprintstring(fd, args));
	else if (c == 'p')
		return (ft_dprintpointer(fd, args, "0123456789abcdef"));
	else if (c == 'd' || c == 'i')
		return (ft_dprintint(fd, args));
	else if (c == 'u')
		return (ft_dprintui(fd, args));
	else if (c == 'x')
		return (ft_dprinthexa(fd, args, "0123456789abcdef"));
	else if (c == 'X')
		return (ft_dprinthexa(fd, args, "0123456789ABCDEF"));
	else if (c == '%')
	{
		ft_putchar_fd('%', fd);
		return (1);
	}
	else
		return (0);
}

/**
 * @brief Prints ARGUMENT(s) according to FORMAT to STANDART ERROR
 */
int	ft_dprintf(int fd, const char *format, ...)
{
	size_t	i;
	int		num_char;
	va_list	args;

	if (!format)
		return (-1);
	va_start (args, format);
	i = 0;
	num_char = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			i++;
			num_char = (num_char + ft_switch(fd, format[i], args));
		}
		else
		{
			ft_putchar_fd(format[i], fd);
			num_char++;
		}
		i++;
	}
	va_end (args);
	return (num_char);
}
/*
int	main(void)
{
	char	*arg1 = "\"we are lost\"";
//	char	*arg2 = "\"space\"";
	char	arg0 = 'h';
//	char	*arg1 = "this";
	char	*arg2 = NULL;
	char	*pointer;
	int	i;
	int	fd;
	unsigned int	ui;
	int	result;
	unsigned int	hex;

	fd = 2;
	pointer = 0;
	ui = +17;
	i = -2147483648;
	hex = 11011011;
	result = ft_dprintf(fd, "Me: he asked me if %s in %s\n%c "
	"pointer: %p\nint = %d\nunsigned int:%u\n%x\n%X\n",
	   	arg1, arg2, arg0, pointer, i, ui, hex, hex);
	printf("Result me: %d\n\n", result);
	result = printf("Ex: he asked me if %s in %s\n%c "
	"pointer: %p\nint = %d\nunsigned int:%u\n%x\n%X\n",
	   	arg1, arg2, arg0, pointer, i, ui, hex, hex);
	printf("Result ex: %d\n", result);
	return (0);
}
*/
