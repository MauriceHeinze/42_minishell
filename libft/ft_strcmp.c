/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:12:41 by rpohl             #+#    #+#             */
/*   Updated: 2022/10/13 15:14:21 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	l;

	l = 0;
	while (*(s1 + l) != 0 && *(s2 + l) != 0)
	{
		if (*(s1 + l) != *(s2 + l))
		{
			if ((unsigned char)*(s1 + l) > (unsigned char)*(s2 + l))
				return ((unsigned char)*(s1 + l) - (unsigned char)*(s2 + l));
			if ((unsigned char)*(s1 + l) < (unsigned char)*(s2 + l))
				return ((unsigned char)*(s1 + l) - (unsigned char)*(s2 + l));
		}
		l++;
	}
	if (*(s1 + l) != *(s2 + l))
	{
		if ((unsigned char)*(s1 + l) > (unsigned char)*(s2 + l))
			return ((unsigned char)*(s1 + l) - (unsigned char)*(s2 + l));
		if ((unsigned char)*(s1 + l) < (unsigned char)*(s2 + l))
			return ((unsigned char)*(s1 + l) - (unsigned char)*(s2 + l));
	}
	return (0);
}
