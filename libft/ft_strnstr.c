/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:40:38 by rpohl             #+#    #+#             */
/*   Updated: 2022/05/06 18:21:47 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	c;
	char	*n;

	i = 0;
	c = 0;
	n = (char *) needle;
	if (*needle == 0)
		return ((char *) haystack);
	while (*(haystack + i) != 0 && i < len)
	{
		if (*(haystack + i) == *needle)
		{
			while (n[c] != 0 && i + c < len && haystack[i + c] == n[c])
			{
				if (*(needle + c + 1) == 0)
					return ((char *)(haystack + i));
				c++;
			}
			c = 0;
		}		
		i++;
	}
	return (0);
}
