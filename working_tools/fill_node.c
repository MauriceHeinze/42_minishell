/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/10/19 19:29:36 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char				*full_cmd; // e.g. echo, cd etc.
// char				*full_path; // if builtin, then it's just full_cmd, else it's path to that cmd
// int					pid; // default -1, is set by executor
// int					infile_mode; // 1. file -> full path, 2. heredoc -> delimiter, 3. stdin -> nothing 4. pipe
// char				*infile_meta; // full path name || delimiter | NULL || pipe id
// int					outfile_mode; // 1. file -> full path, 2. heredoc -> delimiter, 3. stdin -> nothing 4. pipe
// char				*outfile_meta; // full path name || delimiter || pipe id

// < redirection fd ist nicht stdin, sondern fd
// > redirection fd ist nicht stdout, sondern fd
// << redirection fd ist nicht stdin, sondern heredoc
// >> output ist in appendmode -> cat text >> cat text1
// check pipex manual

t_node	*setup_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->full_cmd = "";
	node->full_path = "";
	node->pid = -1;
	node->infile_mode = -1;
	node->infile_meta = "";
	node->outfile_mode = -1;
	node->outfile_meta = "";
	node->next = NULL;
	return (node);
}

void	get_command(t_node	*node, char *token, t_program *program)
{
	int category;

	category = get_category(token);
	node->full_cmd = remove_quotes(token);
	// is undefined/not builtin
	if (category == 50 || category == 1900)
	{
		node->full_path = get_cmd_path(get_cmd_paths(program->envp), token);
	}
	// is builtin
	if (category > 50 && category <= 700)
	{
		node->full_path = token;
		printf("%s\n", node->full_path);
	}
	// // is operator - redirection stuff
	// else if (category >= 800 && category <= 1100)
	// {
	// 	printf("3\n");
	// 	// handle_pipe()
	// }
}

t_node	*fill_node(t_program *program)
{
	int	i;
	t_node	*head;
	t_node	*node;
	char	**tokens;

	tokens = program->tokens;
	i = 0;
	head = setup_node();
	if (!head)
		return (NULL);
	node = head;
	while (tokens[i] != NULL)
	{
		// store command
		get_command(node, program->tokens[i], program);
		i++;
		// store arguments to command
		while (get_category(tokens[i]) != PIPE && tokens[i] != NULL)
		{
			tokens[i] = remove_quotes(tokens[i]);
			node->infile_meta = ft_strjoin(node->infile_meta, tokens[i]);
			i++;
		}
		// fill node
		if (tokens[i] != NULL)
		{
			node->next = setup_node();
			node = node->next;
			i++;
		}
	}
	return (head);
}