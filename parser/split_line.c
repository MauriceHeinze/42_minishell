/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:00:11 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/06 21:02:50 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*setup_split_line(char *str, int *i, int *start, int *no_word)
{
	char	*tmp;

	(*i) = 0;
	(*start) = 0;
	(*no_word) = 0;
	tmp = ft_strtrim(str, " ");
	free(str);
	return (tmp);
}

char	**split_line(char *str)
{
	int		i;
	int		start;
	int		no_word;
	int		total_words;
	char	**words;

	str = setup_split_line(str, &i, &start, &no_word);
	total_words = count_words(str);
	words = malloc(sizeof(char *) * (total_words + 1));
	while (str[i] != '\0')
	{
		start = i;
		while (str[i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '\0')
			i++;
		if (i > start)
		{
			if (ft_strchr(" 	", str[i]))
				i++;
			words[no_word++] = ft_substr(str, start, i - start);
			continue ;
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i + quote_length(str[i], str, i) + 2] == ' ')
			{
				i = i + quote_length(str[i], str, i) + 2;
				words[no_word++] = ft_substr(str, start, i - start + 1);
			}
			else
			{
				i = i + quote_length(str[i], str, i) + 1;
				words[no_word++] = ft_substr(str, start, i - start + 1);
			}
		}
		i++;
	}
	free(str);
	str = NULL;
	words[no_word] = NULL;
	return (words);
}
