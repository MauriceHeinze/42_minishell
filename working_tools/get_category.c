/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_category.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:07:17 by mheinze           #+#    #+#             */
/*   Updated: 2022/10/17 17:39:32 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int		is_command(char *word)
{
	// printf("result:	%d\n", ft_strcmp(word, "echo"));
	if (ft_strcmp(word, "echo") == 0)
		return (ECHO_CMD);
	if (ft_strcmp(word, "cd") == 0)
		return (CD);
	if (ft_strcmp(word, "pwd") == 0)
		return (PWD);
	if (ft_strcmp(word, "export") == 0)
		return (EXPORT);
	if (ft_strcmp(word, "unset") == 0)
		return (UNSET);
	if (ft_strcmp(word, "env") == 0)
		return (ENV);
	if (ft_strcmp(word, "exit") == 0)
		return (EXIT);
	return (0);
}

static int		is_operator(char *word)
{
	if (ft_strcmp(word, ">") == 0)
		return (ARROW_LEFT);
	if (ft_strcmp(word, ">>") == 0)
		return (DOUBLE_ARROW_LEFT);
	if (ft_strcmp(word, "<") == 0)
		return (ARROW_RIGHT);
	if (ft_strcmp(word, "<<") == 0)
		return (DOUBLE_ARROW_RIGHT);
	if (ft_strcmp(word, "|") == 0)
		return (PIPE);
	if (ft_strcmp(word, "||") == 0)
		return (OR);
	if (ft_strcmp(word, "&&") == 0)
		return (AND);
	if (word == NULL)
		return (EXIT);
	return (0);
}

int		get_category(char *word)
{
	if (is_command(word) > 0)
		return (is_command(word));
	else if (is_operator(word) > 0)
		return (is_operator(word));
	else if ((ft_strcmp(word, " ") == 0) || (ft_strcmp(word, "	") == 0))
		return (WHITE_SPACE);
	else if (ft_strcmp(word, "\'") == 0)
		return (QUOTE);
	else if (ft_strcmp(word, "\"") == 0)
		return (DOUBLE_QUOTE);
	else
		return (WORD);
	return (0);
}