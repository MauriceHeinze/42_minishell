/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:01:51 by rpohl             #+#    #+#             */
/*   Updated: 2022/07/27 18:32:10 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_putstr_fd(char *str, int fd, int *counter)
{
	char	c;

	if (!str)
	{
		write(fd, "(null)", 6);
		*counter += 6;
	}
	else
	{
		while (*str)
		{
			c = *str;
			write(fd, &c, 1);
			str++;
			if (counter != NULL)
				*counter += 1;
		}
	}
}
