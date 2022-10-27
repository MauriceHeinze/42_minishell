/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:02:58 by rpohl             #+#    #+#             */
/*   Updated: 2022/07/27 11:06:19 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_putnbr_fd(int n, int fd, int *counter)
{
	char	c;

	if (n == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		*counter += 11;
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
		*counter += 1;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd, counter);
		c = n % 10 + 48;
	}
	else
		c = n + 48;
	write(fd, &c, 1);
	*counter += 1;
}
