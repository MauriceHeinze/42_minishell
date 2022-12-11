/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:00:11 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/11 13:06:34 by mheinze          ###   ########.fr       */
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

static char	*handle_quote(char *str, int *i, int *start, int *no_word)
{
	if (str[(*i) + quote_length(str[(*i)], str, (*i)) + 2] == ' '
		|| str[(*i) + quote_length(str[(*i)], str, (*i)) + 2] == '	')
	{
		(*i) = (*i) + quote_length(str[(*i)], str, (*i)) + 2;
		return (ft_substr(str, (*start), (*i) - (*start) + 1));
	}
	else
	{
		(*i) = (*i) + quote_length(str[(*i)], str, (*i)) + 1;
		return (ft_substr(str, (*start), (*i) - (*start) + 1));
	}
}

static char	*add_word(char *str, int *i, int *start)
{
	if (str[(*i)] == ' ' || str[(*i)] == '	')
		(*i)++;
	return (ft_substr(str, (*start), (*i) - (*start)));
}

char	**split_line(char *str)
{
	int		i;
	int		start;
	int		no_word;
	char	**words;

	str = setup_split_line(str, &i, &start, &no_word);
	words = malloc(sizeof(char *) * (split_line_counter(str) + 1));
	while (str[i] != '\0')
	{
		start = i;
		while (str[i] != '\'' && str[i] != '\"'
			&& str[i] != ' ' && str[i] != '	' && str[i] != '\0')
			i++;
		if (i > start)
		{
			words[no_word++] = add_word(str, &i, &start);
			continue ;
		}
		if (str[i] == '\'' || str[i] == '\"')
			words[no_word++] = handle_quote(str, &i, &start, &no_word);
		i++;
	}
	free(str);
	words[no_word] = NULL;
	return (words);
}
