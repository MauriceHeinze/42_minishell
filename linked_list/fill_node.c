/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/08 21:42:32 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	*setup_node(void)
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

int	add_tokens(t_node *node, t_node *head, char **tokens, int *i)
{
	char	*tmp;
	char	*tmp_2;

	while (get_category(tokens[(*i)]) < ARROW_LEFT
		|| get_category(tokens[(*i)]) > PIPE)
	{
		if (tokens[(*i)] == NULL)
			return (1);
		tmp = ft_strjoin(node->full_cmd, ";");
		free(node->full_cmd);
		node->full_cmd = ft_strjoin(tmp, tokens[(*i)]);
		free(tmp);
		tmp_2 = remove_quotes(tokens[(*i)]);
		tmp = ft_strjoin(node->full_cmd_orig, " ");
		free(node->full_cmd_orig);
		node->full_cmd_orig = ft_strjoin(tmp, tmp_2);
		free(tmp);
		free(tmp_2);
		(*i)++;
	}
	is_pipe(node, i);
	return (0);
}

static void	init_fill_node(t_node **head, t_node **node, int *i)
{
	(*i) = 0;
	*head = setup_node();
	*node = *head;
}

t_node	*fill_node(t_program *program)
{
	int		i;
	t_node	*head;
	t_node	*node;

	init_fill_node(&head, &node, &i);
	while (program->tokens[i] != NULL)
	{
		if (get_category(program->tokens[i]) >= ARROW_LEFT
			&& get_category(program->tokens[i]) <= DOUBLE_ARROW_RIGHT)
		{
			if (!fill_fd(program, node, &i))
				return (NULL);
			if (program->tokens[i] == NULL || program->tokens[i + 1] == NULL)
				break ;
			if ((get_category(program->tokens[i]) < ARROW_LEFT
					|| get_category(program->tokens[i]) > PIPE)
				&& (get_command(program, node, &i) == 1))
				return (free_head(head));
		}
		else if (get_command(program, node, &i) == 1)
			return (free_head(head));
		if (add_tokens(node, head, program->tokens, &i))
			return (head);
	}
	return (head);
}
