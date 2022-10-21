/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/10/21 19:27:45 by mheinze          ###   ########.fr       */
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
	t_fd	*fd;

	fd = malloc(sizeof(t_fd));
	if (!fd)
		return (NULL);

	fd->infile_mode = -1;
	fd->infile_meta = "";
	fd->outfile_mode = -1;
	fd->outfile_meta = "";
	fd->next = NULL;
	return (fd);
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

void	fill_fds(t_program *program, t_node *node, int *pos)
{
	t_fd	*fd;
	t_fd	*head;

	// printf("---> 1\n");
	fd = node->fd;
	head = fd;
	while (fd->next != NULL)
		fd = fd->next;
	// printf("---> 2\n");
	while (program->tokens[(*pos)] != NULL)
	{
		// printf("---> 3\n");
		if (get_category(program->tokens[(*pos)]) == ARROW_RIGHT) // > // don't forget to check if next element is not NULL
		{
			fd->outfile_mode = MODE_FILE;
			fd->outfile_meta = ft_strjoin(getenv("PWD"), "/");
			fd->outfile_meta = ft_strjoin(fd->outfile_meta, program->tokens[(*pos) + 1]);
			fd->next = setup_fd();
			fd = fd->next;
			(*pos)++;
		}
		else if (get_category(program->tokens[(*pos)]) == ARROW_LEFT) // < stdin
		{
			fd->infile_mode = MODE_STDIN;
			fd->next = setup_fd();
			fd = fd->next;
			(*pos)++;
		}
		else if (get_category(program->tokens[(*pos)]) == DOUBLE_ARROW_LEFT) // << HEREDOC
		{
			fd->outfile_mode = MODE_HEREDOC;
			fd->outfile_meta= program->tokens[(*pos)]; // delimiter
			fd->next = setup_fd();
			fd = fd->next;
			(*pos)++;
		}
		else if (get_category(program->tokens[(*pos)]) == DOUBLE_ARROW_RIGHT) // >> APPEND
		{
			fd->infile_mode = MODE_STDIN; // e.g. echo 'Hello world!'
			fd->outfile_mode = MODE_FILE; // e.g. >> outfile
			fd->outfile_meta = ft_strjoin(getenv("PWD"), "/");
			fd->outfile_meta = ft_strjoin(fd->outfile_meta, program->tokens[(*pos) + 1]);
			fd->next = setup_fd();
			fd = fd->next;
			(*pos)++;
		}
		(*pos)++;
	}
}

int	get_command(t_node	*node, t_program *program, int pos)
{
	int 	category;
	char	*token;
	char	**paths;

	token = program->tokens[pos];
	category = get_category(token);
	node->full_cmd = remove_quotes(token);
	// printf("%d\n", category);
	// is undefined/not builtin
	if (category == UNDEFINED || category == WORD)
	{
		paths = get_cmd_paths(program->envp);
		node->full_path = get_cmd_path(paths, token);
		free(paths);
	}
	// is builtin
	if (category > UNDEFINED && category <= EXIT)
	{
		node->full_path = token;
		printf("%s\n", node->full_path);
	}
	return (0);
}

t_node	*fill_node(t_program *program)
{
	int		*i;
	t_node	*head;
	t_node	*node;
	char	**tokens;

	tokens = program->tokens;
	*i = 0;
	head = setup_node();
	if (!head)
		return (NULL);
	// node = head;
	// printf("1: i is %d\n", *i);
	fill_fds(program, head, i);
	// printf("2: i is %d\n", *i);
	// printf("%s\n", head->fd->outfile_meta);
	// printf("%s\n", head->fd->next->outfile_meta);
	// printf("%s\n", head->fd->next->next->outfile_meta);
	return (head);
}