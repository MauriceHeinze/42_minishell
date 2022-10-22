/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/10/22 23:33:34 by mheinze          ###   ########.fr       */
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

t_fd	*setup_fd(void)
{
	t_fd	*node;

	node = malloc(sizeof(t_fd));
	if (!node)
		return (NULL);

	node->io = OUTPUT;
	node->mode = -1;
	node->meta = "";
	node->fd = -1;
	node->next = NULL;
	return (node);
}

t_node	*setup_node(void)
{
	t_node	*node;
	t_fd	*fd;

	node = malloc(sizeof(t_node));
	fd = setup_fd();
	if (!node || !fd)
		return (NULL);
	node->full_cmd = "";
	node->full_path = "";
	node->pid = -1;
	node->fd = fd;
	node->next = NULL;
	return (node);
}

void	fill_fd(t_program *program, t_node *node, int *pos)
{
	t_fd	*fd;
	t_fd	*head;

	fd = node->fd;
	head = fd;
	while (fd->next != NULL)
		fd = fd->next;

	if (get_category(program->tokens[(*pos)]) == ARROW_RIGHT) // > // don't forget to check if next element is not NULL
	{
		// infile infos don't change
		(*pos)++;
		fd->io = OUTPUT;
		fd->mode = MODE_FILE;
		fd->meta = ft_strjoin(getenv("PWD"), "/");
		fd->meta = ft_strjoin(fd->meta, program->tokens[(*pos)]);
		fd->next = setup_fd();
		fd = fd->next;
		(*pos)++;
	}
	else if (get_category(program->tokens[(*pos)]) == ARROW_LEFT) // < stdin
	{
		(*pos)++;
		fd->io = INPUT;
		fd->mode = MODE_FILE;
		fd->meta = ft_strjoin(getenv("PWD"), "/");
		fd->meta = ft_strjoin(fd->meta, program->tokens[(*pos)]);
		fd->next = setup_fd();
		fd = fd->next;
		(*pos)++;
	}
	else if (get_category(program->tokens[(*pos)]) == DOUBLE_ARROW_LEFT) // << HEREDOC
	{
		(*pos)++;
		fd->io = INPUT;
		fd->mode = MODE_HEREDOC;
		fd->meta = program->tokens[(*pos)]; // delimiter
		fd->next = setup_fd();
		fd = fd->next;
		(*pos)++;
	}
	else if (get_category(program->tokens[(*pos)]) == DOUBLE_ARROW_RIGHT) // >> APPEND
	{
		(*pos)++;
		fd->io = OUTPUT;
		fd->mode = MODE_APPEND;
		fd->meta = ft_strjoin(getenv("PWD"), "/");
		fd->meta = ft_strjoin(fd->meta, program->tokens[(*pos)]);
		fd->next = setup_fd();
		fd = fd->next;
		(*pos)++;
	}
	fd = head;
}

int	get_command(t_program *program, t_node	*node, int *pos)
{
	int 	category;
	char	*token;
	char	**paths;

	// printf("pos: %d\n", (*pos));
	printf("1: %s\n", program->tokens[(*pos)]);
	token = program->tokens[(*pos)];
	category = get_category(token);
	node->full_cmd = remove_quotes(token);
	// is undefined/not builtin
	if (category == UNDEFINED || category == WORD)
	{
		paths = get_cmd_paths(program->envp);
		node->full_path = get_cmd_path(paths, token);
		free(paths);
		(*pos)++;
	}
	// is builtin
	else if (category > UNDEFINED && category <= EXIT)
	{
		node->full_path = token;
		printf("%s\n", node->full_path);
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

	head = NULL;
	tokens = program->tokens;
	i = 0;
	head = setup_node();
	if (!head)
		return (NULL);
	node = head;
	// printf("1: i is %d\n", i);
	// printf("%s\n", program->cmd_line);
	while (program->tokens[i] != NULL)
	{
		// if arrow, fill up fd list
		// first word is always command
		// copy arguments until you find pipe or arrows
		// if pipe is found, create new node

		// if arrow, fill up fd list
		if (get_category(tokens[i]) >= ARROW_LEFT && get_category(tokens[i]) <= DOUBLE_ARROW_RIGHT)
		{
			// printf("1. pos: %d\n", i);
			fill_fd(program, node, &i);
			// printf("2. pos: %d\n", i);
			// first word is always command
			if (tokens[i] == NULL || tokens[i + 1] == NULL)
				break ;
			if (get_category(tokens[i]) < ARROW_LEFT || get_category(tokens[i]) > PIPE)
				get_command(program, node, &i);
			// printf("3. pos: %d\n-----------\n", i);
			// printf("Command:	%s \n", node->full_cmd);
		}
		else
		{
			// printf("2. pos: %d\n", i);
			get_command(program, node, &i);
			// printf("3. pos: %d\n", i);
			// printf("Command:	%s \n", node->full_cmd);
		}
		// printf("Token:	%s \n", tokens[i]);
		// copy arguments until you find pipe or arrows
		while (get_category(tokens[i]) < ARROW_LEFT || get_category(tokens[i]) > PIPE)
		{
			node->full_cmd = ft_strjoin(node->full_cmd, " ; ");
			node->full_cmd = ft_strjoin(node->full_cmd, tokens[i]);
			// printf("HERE -> Command:	%s \n", node->full_cmd);
			i++;
		}
		// if pipe is found, create new node
		if (get_category(program->tokens[i]) == PIPE)
		{
			// printf("NEW NODE! %d\n-----------\n", i);
			node->next = setup_node();
			node = node->next;
			i++;
		}
	}
	// printf("\n2: i is %d\n", i);
	// printf("%s\n", head->fd->outfile_meta);
	// printf("%s\n", head->fd->next->outfile_meta);
	// printf("%s\n", head->fd->next->next->outfile_meta);
	return (head);
}