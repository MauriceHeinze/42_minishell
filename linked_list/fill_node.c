/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/10 17:58:44 by mheinze          ###   ########.fr       */
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

static void	init_fill_node(t_node **head, t_node **node, int *i)
{
	(*i) = 0;
	*head = setup_node();
	*node = *head;
}

static int	operator_statement(int *i)
{
	if (get_category(program->tokens[(*i)]) >= ARROW_LEFT
		&& get_category(program->tokens[(*i)]) <= DOUBLE_ARROW_RIGHT)
	{
		return (1);
	}
	return (0);
}

static int	operator_statement_2(t_node *node, int *i)
{
	if (program->tokens[(*i)])
	{
		if ((get_category(program->tokens[(*i)]) < ARROW_LEFT
				|| get_category(program->tokens[(*i)]) > PIPE)
			&& (get_command(program, &node, i) == 1))
			return (1);
	}
	return (0);
}

t_node	*fill_node(t_program *program)
{
	int		i;
	t_node	*head;
	t_node	*node;

	init_fill_node(&head, &node, &i);
	while (program->tokens[i] != NULL)
	{
		if (operator_statement(&i))
		{
			fill_fd(program, &node, &i);
			if (program->tokens[i] == NULL && program->tokens[i + 1] == NULL)
				break ;
			if (operator_statement_2(node, &i))
				return (free_head(head));
		}
		else if (get_command(program, &node, &i) == 1)
			return (free_head(head));
		if (add_tokens(&node, program->tokens, &i))
			return (head);
		if (get_category(program->tokens[i]) == PIPE)
			node = add_node(node, &i);
	}
	return (head);
}
