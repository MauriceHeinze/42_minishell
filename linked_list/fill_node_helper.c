/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/12 02:00:19 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	set_node_builtin(t_node	**node, char *token, int *pos)
{
	(*node)->full_cmd_orig = ft_strdup(token);
	(*node)->full_path = ft_strdup("builtin");
	(*pos)++;
	free(token);
}

static int	get_command_helper(t_node	**node, char *token, int category,
	int *pos)
{
	char	**paths;

	if (category == UNDEFINED || category == WORD)
	{
		paths = get_cmd_paths(g_program->envp);
		(*node)->full_cmd_orig = ft_strdup(token);
		(*node)->full_path = get_cmd_path_no_free(paths, token);
		free(token);
		if ((*node)->full_path == NULL)
		{
			free((*node)->full_cmd);
			(*node)->full_cmd = NULL;
			free_split(paths);
			return (1);
		}
		free_split(paths);
		(*pos)++;
	}
	else if (category > UNDEFINED && category <= EXIT)
		set_node_builtin(node, token, pos);
	return (0);
}

int	get_command(t_program *g_program, t_node **node, int *pos)
{
	int		category;
	char	*token;
	char	*tmp;

	tmp = ft_strtrim(g_program->tokens[(*pos)], " 	");
	token = remove_quotes(tmp);
	free(tmp);
	category = get_category(token);
	(*node)->full_cmd = ft_strdup(token);
	return (get_command_helper(node, token, category, pos));
}

int	add_tokens(t_node **node, char **tokens, int *i)
{
	char	*tmp;
	char	*tmp_2;

	while (get_category(tokens[(*i)]) < ARROW_LEFT
		|| get_category(tokens[(*i)]) > PIPE)
	{
		if (tokens[(*i)] == NULL)
			return (1);
		tmp = ft_strjoin((*node)->full_cmd, ";");
		free((*node)->full_cmd);
		(*node)->full_cmd = ft_strjoin(tmp, tokens[(*i)]);
		free(tmp);
		tmp_2 = remove_quotes(tokens[(*i)]);
		tmp = ft_strjoin((*node)->full_cmd_orig, " ");
		free((*node)->full_cmd_orig);
		(*node)->full_cmd_orig = ft_strjoin(tmp, tmp_2);
		free(tmp);
		free(tmp_2);
		(*i)++;
	}
	return (0);
}

t_node	*add_node(t_node *node, int *i)
{
	node->next = setup_node();
	node = node->next;
	(*i)++;
	return (node);
}
