/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:31:08 by rpohl             #+#    #+#             */
/*   Updated: 2022/05/06 09:47:29 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(const char *src)
{
	unsigned int	lsrc;
	unsigned int	i;
	char			*dst;

	i = 0;
	lsrc = ft_strlen((char *)src);
	dst = malloc(sizeof(char) * (lsrc + 1));
	while (i < lsrc)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = 0;
	return (dst);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		end;
	int		start;
	char	*cp;

	start = 0;
	end = 0;
	cp = 0;
	if (*set == 0)
	{
		cp = ft_strcpy(s1);
	}
	else if (s1 && set)
	{
		while (s1[start] && ft_strchr(set, s1[start]))
			start++;
		while (*(s1 + end) != 0)
			end++;
		while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > start)
			end--;
		cp = malloc (sizeof(char) * (end - start + 1));
		if (!cp)
			return (NULL);
		ft_strlcpy(cp, &s1[start], end - start + 1);
	}
	return (cp);
}
