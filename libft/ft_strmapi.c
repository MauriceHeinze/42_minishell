/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:39:08 by rpohl             #+#    #+#             */
/*   Updated: 2022/05/06 09:47:23 by rpohl            ###   ########.fr       */
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

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*cp;

	if (!s || !f)
		return (NULL);
	if (*s == 0)
	{
		cp = malloc(sizeof(char) * 1);
		if (!cp)
			return (NULL);
		*cp = 0;
		return (cp);
	}
	i = check_str_length(s);
	cp = malloc((sizeof(char) * (i + 1)));
	if (cp == NULL)
		return (NULL);
	*(cp + (i--)) = 0;
	while (i > 0)
	{
		*(cp + i) = f(i, *(s + i));
		i--;
	}
	*(cp) = f(0, *(s));
	return (cp);
}
