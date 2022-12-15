/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_counter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:00:11 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/12 02:01:38 by mheinze          ###   ########.fr       */
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
	return (tmp);
}

static void	handle_quote(char *str, int *i)
{
	if (str[(*i) + quote_length(str[(*i)], str, (*i)) + 2] == ' '
		|| str[(*i) + quote_length(str[(*i)], str, (*i)) + 2] == '	')
		(*i) = (*i) + quote_length(str[(*i)], str, (*i)) + 2;
	else
		(*i) = (*i) + quote_length(str[(*i)], str, (*i)) + 1;
}

int	split_line_counter(char *str)
{
	int		i;
	int		start;
	int		no_words;
	char	*tmp;

	tmp = setup_split_line(str, &i, &start, &no_words);
	while (str[i] != '\0')
	{
		start = i;
		while (str[i] != '\'' && str[i] != '\"'
			&& str[i] != ' ' && str[i] != '	' && str[i] != '\0')
			i++;
		if (i > start)
			no_words++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			no_words++;
			handle_quote(str, &i);
		}
		i++;
	}
	free(tmp);
	return (no_words);
}
