/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/04 14:58:11 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Check if operator is followed by word that is not an operator */
static int	valid_operator(char **tokens)
{
	int		i;

	i = 0;
	while (tokens[i])
	{
		if (is_operator(tokens[i]) >= ARROW_LEFT && is_operator(tokens[i]) <= PIPE)
		{
			if (tokens[i + 1] == NULL)
			{
				printf("minishell: syntax error near unexpected token `%s'\n", tokens[i]);
				return (0);
			}
			if (is_operator(tokens[i + 1]) >= ARROW_LEFT && is_operator(tokens[i + 1]) <= PIPE)
			{
				printf("minishell: syntax error near unexpected token `%s'\n", tokens[i + 1]);
				return (0);
			}
		}
		else if (is_operator(tokens[i]) == AND || is_operator(tokens[i]) == OR)
		{
			printf("minishell: syntax error near unexpected token `%s'\n", tokens[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

/* Check if quotes are closed */
static int	quotes_closed(char *token)
{
	int		i;
	char	quote;

	i = 0;
	if (token[i] == '\'' || token[i] == '\"')
	{
		quote = token[i];
		i++;
		while (token[i] && token[i] != quote)
			i++;
		if (quote == '\"' && token[i] != quote)
		{
			if (quote == '\'')
				special_error(SINGLE_QUOTE_MISSING);
			else if (quote == '\"')
				special_error(DOUBLE_QUOTE_MISSING);
			return (0);
		}
	}
	return (1);
}

/* Check if semicolon was used */
static int	no_semicolon(char *token)
{
	int		i;

	i = 0;
	if (token[0] != '\'' && token[0] != '\"')
	{
		while (token[i] != '\0')
		{
			if (token[i++] == ';')
			{
				special_error(SEMICOLON_USED);
				return (0);
			}
		}
	}
	return (1);
}

/* Check syntax */
int	check_syntax(char **tokens)
{
	int	i;

	i = 0;
	if (!valid_operator(tokens))
			return (0);
	while (tokens[i])
	{
		if (!no_semicolon(tokens[i]))
			return (0);
		if (!quotes_closed(tokens[i]))
			return (0);
		i++;
	}
	return (1);
}