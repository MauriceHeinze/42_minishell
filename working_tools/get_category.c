/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_category.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:07:17 by mheinze           #+#    #+#             */
/*   Updated: 2022/10/18 22:35:35 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int		is_command(char *word)
{
	if (ft_strcmp(word, "echo") == 0)
		return (ECHO);
	else if (ft_strcmp(word, "cd") == 0)
		return (CD);
	else if (ft_strcmp(word, "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(word, "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(word, "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(word, "env") == 0)
		return (ENV);
	else if (ft_strcmp(word, "exit") == 0)
		return (EXIT);
	return (0);
}

static int		is_operator(char *word)
{
	if (ft_strcmp(word, ">") == 0)
		return (ARROW_LEFT);
	else if (ft_strcmp(word, ">>") == 0)
		return (DOUBLE_ARROW_LEFT);
	else if (ft_strcmp(word, "<") == 0)
		return (ARROW_RIGHT);
	else if (ft_strcmp(word, "<<") == 0)
		return (DOUBLE_ARROW_RIGHT);
	else if (ft_strcmp(word, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(word, "||") == 0)
		return (OR);
	else if (ft_strcmp(word, "&&") == 0)
		return (AND);
	else if (ft_strcmp(word, "NULL") == 0)
	{
		// printf("Here\n");
		return (EXIT);
	}
	return (0);
}

int		get_category(char *word)
{
	if (word == NULL)
		return (0);
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