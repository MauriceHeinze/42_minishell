/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:04:51 by rpohl             #+#    #+#             */
/*   Updated: 2022/07/27 11:06:19 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex_fd(unsigned int n, int fd, int *counter, const char *cp)
{
	unsigned char	c;

	if (n >= 16)
	{
		ft_puthex_fd(n / 16, fd, counter, cp);
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
