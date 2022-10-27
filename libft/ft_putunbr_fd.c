/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:02:58 by rpohl             #+#    #+#             */
/*   Updated: 2022/07/27 11:06:19 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunbr_fd(unsigned int n, int fd, int *counter)
{
	char	c;

	if (n >= 10)
	{
		ft_putunbr_fd(n / 10, fd, counter);
		c = n % 10 + 48;
	}
	else
		c = n + 48;
	write(fd, &c, 1);
	*counter += 1;
}
