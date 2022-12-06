/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/06 14:19:57 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_node	*setup_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->full_cmd = NULL;
	node->full_cmd_orig = NULL;
	node->full_path = NULL;
	node->pid = -1;
	node->fd = NULL;
	node->next = NULL;
	return (node);
}

int	get_command(t_program *program, t_node	*node, int *pos)
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

t_node	*fill_node(t_program *program)
{
	int		i;
	t_node	*head;
	t_node	*node;
	char	**tokens;
	char	*tmp;
	char	*tmp_2;

	head = NULL;
	tokens = program->tokens;
	i = 0;
	head = setup_node();
	if (!head)
		return (NULL);
	node = head;
	while (program->tokens[i] != NULL)
	{
		if (get_category(tokens[i]) >= ARROW_LEFT && get_category(tokens[i]) <= DOUBLE_ARROW_RIGHT)
		{
			if (!fill_fd(program, node, &i))
				return (NULL);
			if (tokens[i] == NULL || tokens[i + 1] == NULL)
				break ;
			if (get_category(tokens[i]) < ARROW_LEFT || get_category(tokens[i]) > PIPE)
			{
				if (get_command(program, node, &i) == 1)
				{
					free(head->full_cmd_orig);
					head->full_cmd_orig = NULL;
					free(head);
					head = NULL;
					return (NULL);
				}
			}
		}
		else
		{
			if (get_command(program, node, &i) == 1)
			{
				free(head->full_cmd_orig);
				head->full_cmd_orig = NULL;
				free(head);
				head = NULL;
				return (NULL);
			}
		}
		while (get_category(tokens[i]) < ARROW_LEFT || get_category(tokens[i]) > PIPE)
		{
			if (tokens[i] == NULL)
				return (head);
			tmp = ft_strjoin(node->full_cmd, ";");
			free(node->full_cmd);
			node->full_cmd = ft_strjoin(tmp, tokens[i]);
			free(tmp);
			tmp_2 = remove_quotes(tokens[i]);
			tmp = ft_strjoin(node->full_cmd_orig, " ");
			free(node->full_cmd_orig);
			node->full_cmd_orig = ft_strjoin(tmp, tmp_2);
			free(tmp);
			free(tmp_2);
			i++;
		}
		if (get_category(program->tokens[i]) == PIPE)
		{
			node->next = setup_node();
			node = node->next;
			i++;
		}
	}
	return (head);
}
