/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/11/27 21:32:58 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char				*full_cmd; // e.g. echo, cd etc.
// char				*full_path; // if builtin, then it's just full_cmd, else it's path to that cmd
// int				pid; // default -1, is set by executor
// int				infile_mode; // 1. file -> full path, 2. heredoc -> delimiter, 3. stdin -> nothing 4. pipe
// char				*infile_meta; // full path name || delimiter | NULL || pipe id
// int				outfile_mode; // 1. file -> full path, 2. heredoc -> delimiter, 3. stdin -> nothing 4. pipe
// char				*outfile_meta; // full path name || delimiter || pipe id

// < redirection fd ist nicht stdin, sondern fd
// > redirection fd ist nicht stdout, sondern fd
// << redirection fd ist nicht stdin, sondern heredoc
// >> output ist in appendmode -> cat text >> cat text1
// check pipex manual

static t_node	*setup_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->full_cmd = "";
	node->full_cmd_orig = "";
	node->full_path = "";
	node->pid = -1;
	node->fd = NULL;
	node->next = NULL;
	return (node);
}

int	get_command(t_program *program, t_node	*node, int *pos)
{
	int 	category;
	char	*token;
	char	*token_dup;
	char	**paths;

	token = ft_strtrim(program->tokens[(*pos)], " ");
	category = get_category(token);
	node->full_cmd = remove_quotes(token);
	// is undefined/not builtin
	if (category == UNDEFINED || category == WORD)
	{
		paths = get_cmd_paths(program->envp);
		node->full_cmd_orig = ft_strdup(token);
		node->full_path = get_cmd_path(paths, token);
		free(paths);
		(*pos)++;
	}
	// is builtin
	else if (category > UNDEFINED && category <= EXIT)
	{
		node->full_cmd = ft_strdup(token);;
		node->full_cmd_orig = ft_strdup(token);;
		node->full_path = "builtin";
		free(token);
		(*pos)++;
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

	head = NULL;
	tokens = program->tokens;
	i = 0;
	head = setup_node();
	if (!head)
		return (NULL);
	node = head;
	while (program->tokens[i] != NULL)
	{
		// if arrow, fill up fd list
		// first word is always command
		// copy arguments until you find pipe or arrows
		// if pipe is found, create new node

		// if arrow, fill up fd list
		if (get_category(tokens[i]) >= ARROW_LEFT && get_category(tokens[i]) <= DOUBLE_ARROW_RIGHT)
		{
			fill_fd(program, node, &i);
			// first word is always command
			if (tokens[i] == NULL || tokens[i + 1] == NULL)
				break ;
			if (get_category(tokens[i]) < ARROW_LEFT || get_category(tokens[i]) > PIPE)
				get_command(program, node, &i);
		}
		else
			get_command(program, node, &i);
		// copy arguments until you find pipe or arrows
		while (get_category(tokens[i]) < ARROW_LEFT || get_category(tokens[i]) > PIPE)
		{
			if (tokens[i] == NULL)
				return (head);
			tmp = ft_strjoin(node->full_cmd_orig, " ");
			node->full_cmd_orig = ft_strjoin(tmp, tokens[i]);
			free(tmp);
			tmp = ft_strjoin(node->full_cmd, ";");
			node->full_cmd = ft_strjoin(tmp, tokens[i]);
			free(tmp);
			i++;
		}
		// if pipe is found, create new node
		if (get_category(program->tokens[i]) == PIPE)
		{
			node->next = setup_node();
			node = node->next;
			i++;
		}
	}
	return (head);
}