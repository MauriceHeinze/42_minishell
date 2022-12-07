/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:23:48 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/07 14:25:17 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	count_quote(char *str, int *i, int *no_word)
{
	if (str[(*i)] == '\'' || str[(*i)] == '\"')
	{
		if (str[(*i) + quote_length(str[(*i)], str, (*i)) + 2] == ' ')
			(*i) = (*i) + quote_length(str[(*i)], str, (*i)) + 2;
		else
			(*i) = (*i) + quote_length(str[(*i)], str, (*i)) + 1;
		(*no_word)++;
	}
}

int	count_words(char *str)
{
	int	i;
	int	start;
	int	no_word;

	i = 0;
	no_word = 0;
	while (str[i] != '\0')
	{
		start = i;
		while (!ft_strchr("\'\" 	", str[i]) && str[i] != '\0')
			i++;
		if (i > start)
		{
			if (ft_strchr(" 	", str[i]))
				i++;
			no_word++;
			continue ;
		}
		count_quote(str, &i, &no_word);
		i++;
	}
	return (no_word);
}
