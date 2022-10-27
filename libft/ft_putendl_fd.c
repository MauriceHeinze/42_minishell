/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:58:07 by rpohl             #+#    #+#             */
/*   Updated: 2022/05/06 09:52:25 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_str_length(const char *str)
{
	int	length;

	length = 0;
	while (*(str + length) != '\0')
	{
		length++;
	}
	return (length);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, check_str_length(s));
	write(fd, "\n", 1);
}
