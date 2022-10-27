/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:24:19 by rpohl             #+#    #+#             */
/*   Updated: 2022/07/28 13:50:15 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**malloc_error(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

static char	*word_dup(char *src, int length)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (length));
	if (!src || !result)
		return (NULL);
	i = 0;
	while (i < length)
	{
		*(result + i) = *(src + i);
		i++;
	}
	*(result + i - 1) = 0;
	return (result);
}

static int	check_str_words(char const *str, char c)
{
	int	w;
	int	i;

	i = 0;
	w = 0;
	while (str[i] != 0)
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == 0))
			w++;
		i++;
	}
	return (w);
}

static int	check_str(const char *str, char c, char type)
{
	int	length;
	int	i;

	if (type == 'u')
	{
		length = 0;
		while (*(str + length) != c && *(str + length) != '\0')
			length++;
		return (length);
	}
	if (type == 'o')
	{
		i = 0;
		while (*(str + i) != 0)
		{
			if (*(str + i) != c)
				return (1);
			i++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**word_array;
	char	*cp;
	int		position;
	int		i;

	if (s == NULL || s[0] == '\0' || check_only(s, c))
		throw_error();
	word_array = malloc(sizeof(char *) * (check_str_words(s, c) + 1));
	if (!word_array)
		return (NULL);
	i = 0;
	position = 0;
	cp = (char *)s;
	while (i < check_str_words(s, c))
	{
		if ((check_str(cp, c, 'u') + 1) > 1 && i < check_str_words(s, c))
		{
			word_array[i++] = word_dup(cp, (check_str(cp, c, 'u') + 1));
			if (word_array [i - 1] == (NULL))
				return (malloc_error(word_array));
		}
		cp = (char *)(s + (position += (check_str(cp, c, 'u') + 1)));
	}
	word_array[i] = NULL;
	return (word_array);
}
