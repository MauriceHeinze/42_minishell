/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/10/18 20:57:14 by mheinze          ###   ########.fr       */
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

	node = malloc(sizeof(node));
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
	node->full_cmd = token;
	// printf("categroy is %d\n", category);
	// is undefined/not builtin
	if (category == 50 || category == 1900)
	{
		node->full_path = get_cmd_path(get_cmd_paths(program->envp), token);
	}
	// is builtin
	if (category > 50 && category <= 700)
	{
		node->full_path = token;
	}
	// is operator - redirection stuff
	else if (category >= 800 && category <= 1100)
	{
		printf("3\n");
		// handle_pipe()
	}
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
	// set type
	// get arguments
	// remove quotes
	// break if pipe is found
	// restart
	get_command(head, tokens[0], program);
	printf("%s\n", head->full_cmd);
	printf("%s\n", head->full_path);

	// node = head;
	// while (node != NULL)
	// {
	// 	printf("%s\n", node->full_cmd);
	// 	node = node->next;
	// }
	// while (tokens[i] != NULL)
	// {
	// 	// setup a new node
	// 	node->next = setup_node();
	// 	// categorize first token
	// 	// is builtin

	// 	// if (strncmp("<", tokens[i], 1))
	// 	// 	// open();
	// 	// if (strncmp(">", tokens[i], 1))
	// 	// 	// open()
	// 	// if (strncmp(">>", tokens[i], 2))
	// 	// 	// open()
	// 	// if (strncmp("<<", tokens[i], 2))
	// 	// 	// open()
	// 	// add arguments to node
	// 	// while (tokens[i] != NULL)
	// 	// {

	// 	// 	i++;
	// 	// 	if (get_category(tokens[i]) == PIPE)
	// 	// 		break ;
	// 	// }
	// }
	return (node);
}