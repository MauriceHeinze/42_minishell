/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:38:26 by rpohl             #+#    #+#             */
/*   Updated: 2022/07/27 11:06:19 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_check_format(const char *format, va_list args, int *count)
{
	while (*format)
	{
		if (*format != '%')
			ft_putchar_fd(*format, 1, count);
		else
		{
			format++;
			if (*format == '%')
				ft_putchar_fd(37, 1, count);
			if (*format == 'c')
				ft_putchar_fd(va_arg(args, int), 1, count);
			if (*format == 's')
				ft_putstr_fd(va_arg(args, char *), 1, count);
			if (*format == 'p')
				ft_putaddr_fd(va_arg(args, void *), 1, count);
			if (*format == 'd' || *format == 'i')
				ft_putnbr_fd(va_arg(args, int), 1, count);
			if (*format == 'u')
				ft_putunbr_fd(va_arg(args, unsigned long), 1, count);
			if (*format == 'x' || *format == 'X')
				ft_puthex_fd(va_arg(args, unsigned int), 1, count, format);
		}
		format++;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start (args, format);
	count = 0;
	ft_check_format(format, args, &count);
	va_end (args);
	return (count);
}
