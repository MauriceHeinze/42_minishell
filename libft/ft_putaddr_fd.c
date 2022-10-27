/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:04:51 by rpohl             #+#    #+#             */
/*   Updated: 2022/07/27 11:06:19 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putlhex_fd(unsigned long n, int fd, int *counter, const char *cp)
{
	unsigned char	c;

	if (n >= 16)
	{
		ft_putlhex_fd(n / 16, fd, counter, cp);
		c = n % 16 + '0';
		if (c > '9' && *cp == 'x')
			c += 39;
		else if (c > '9' && *cp == 'X')
			c += 7;
	}
	else
	{
		c = n + 48;
		if (c > '9' && *cp == 'x')
			c += 39;
		else if (c > '9' && *cp == 'X')
			c += 7;
	}
	write(fd, &c, 1);
	*counter += 1;
}

void	ft_putaddr_fd(void *str, int fd, int *counter)
{
	unsigned long	n;

	write(fd, "0x", 2);
	*counter += 2;
	if (!str)
	{
		write(fd, "0", 1);
		*counter += 1;
	}
	else
	{
		n = (unsigned long)str;
		ft_putlhex_fd(n, fd, counter, "x");
	}
}
