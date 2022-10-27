/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:45:13 by rpohl             #+#    #+#             */
/*   Updated: 2022/05/06 09:47:57 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	checklength(char *start)
{
	int	c;

	if (!start)
		return (0);
	c = 0;
	while (*(start + c) != 0)
		c++;
	return (c);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*cp;
	unsigned int	l1;
	unsigned int	l2;
	unsigned int	c;

	l1 = checklength((char *)s1);
	l2 = checklength((char *)s2);
	cp = malloc(sizeof(char) * (l1 + l2 + 1));
	if (!cp)
		return (NULL);
	c = 0;
	while (c < l1)
	{
		*(cp + c) = *(s1 + c);
		c++;
	}
	c = 0;
	while (c < l2)
	{
		*(cp + c + l1) = *(s2 + c);
		c++;
	}
	*(cp + l1 + l2) = 0;
	return (cp);
}
