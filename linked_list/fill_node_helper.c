/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/08 21:41:35 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	get_command_helper(t_node	*node, char *token, int category,
	int *pos)
{
	char	**paths;

	if (category == UNDEFINED || category == WORD)
	{
		paths = get_cmd_paths(program->envp);
		node->full_cmd_orig = ft_strdup(token);
		node->full_path = get_cmd_path(paths, token);
		if (node->full_path == NULL)
		{
			free_split(paths);
			return (1);
		}
		free_split(paths);
		(*pos)++;
	}
	else if (category > UNDEFINED && category <= EXIT)
	{
		node->full_cmd_orig = ft_strdup(token);
		node->full_path = "builtin";
		(*pos)++;
		free(token);
		token = NULL;
	}
	return (0);
}

int	get_command(t_program *program, t_node *node, int *pos)
{
	int		category;
	char	*token;
	char	*tmp;
	char	**paths;

	tmp = ft_strtrim(program->tokens[(*pos)], " ");
	token = remove_quotes(tmp);
	free(tmp);
	category = get_category(token);
	node->full_cmd = ft_strdup(token);
	return (get_command_helper(node, token, category, pos));
}

void	is_pipe(t_node *node, int *i)
{
	if (get_category(program->tokens[(*i)]) == PIPE)
	{
		node->next = setup_node();
		node = node->next;
		(*i)++;
	}
}
