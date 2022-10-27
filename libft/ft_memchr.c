/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:21:00 by rpohl             #+#    #+#             */
/*   Updated: 2022/05/06 18:27:52 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	chr;

	i = 0;
	chr = c;
	if (n == 0)
		return (0);
	while (*(char *)(s + i) != chr && i < n -1)
		i++;
	if (*(char *)(s + i) == chr)
		return ((void *)(s + i));
	else
		return (0);
}
