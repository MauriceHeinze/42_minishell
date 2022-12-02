/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:04:35 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/02 18:18:36 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	c;

	if (!str)
		return (0);
	c = 0;
	while (str[c] != '\0')
		c++;
	return (c);
}

char	*ft_strjoin_2(char *text_data, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!text_data)
	{
		text_data = (char *)malloc(1 * sizeof(char));
		text_data[0] = '\0';
	}
	if (!text_data || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(text_data) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (text_data)
		while (text_data[++i] != '\0')
			str[i] = text_data[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(text_data) + ft_strlen(buff)] = '\0';
	free(text_data);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != (char)c && s[i] != '\0')
		i++;
	if (s[i] == (char)c)
		return ((char *)s + i + 1);
	return (NULL);
}

char	*ft_get_line(char *text_data)
{
	int		i;
	char	*line;

	i = 0;
	if (!text_data[i])
		return (NULL);
	while (text_data[i] && text_data[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (text_data[i] && text_data[i] != '\n')
	{
		line[i] = text_data[i];
		i++;
	}
	if (text_data[i] == '\n')
	{
		line[i] = text_data[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_new_text(char *text_data)
{
	int		i;
	int		j;
	char	*new_text;

	i = 0;
	while (text_data[i] != '\n' && text_data[i] != '\0')
		i++;
	if (!text_data[i])
	{
		free(text_data);
		return (NULL);
	}
	new_text = malloc(sizeof(char) * (ft_strlen(text_data) - i + 1));
	if (!new_text)
		return (NULL);
	j = 0;
	i++;
	while (text_data[i])
		new_text[j++] = text_data[i++];
	new_text[j] = 0;
	free(text_data);
	return (new_text);
}
