/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:36:05 by rpohl             #+#    #+#             */
/*   Updated: 2022/05/06 18:01:28 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*nullpointer(void)
{
	char	*cp;

	cp = malloc(sizeof(char) * 1);
	if (!cp)
		return (NULL);
	*cp = 0;
	return (cp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*cp;
	unsigned int	c;
	int				src_length;

	if (!s)
		return (NULL);
	src_length = ft_strlen(s);
	c = 0;
	if (src_length < (int) start)
		return (nullpointer());
	if (len <= src_length - start)
		cp = malloc(sizeof(char) * (len + 1));
	else
		cp = malloc(sizeof(char) * (src_length - start));
	if (!cp)
		return (NULL);
	while (c < len && c < src_length - start)
	{
		*(cp + c) = *(s + start + c);
		c++;
	}
	*(cp + c) = 0;
	return (cp);
}
