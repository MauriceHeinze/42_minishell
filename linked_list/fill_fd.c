/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/03 18:50:37 by mheinze          ###   ########.fr       */
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
	node->meta = NULL;
	node->fd = -1;
	node->next = NULL;
	return (node);
}

int	fill_fd(t_program *program, t_node *node, int *pos)
{
	t_fd	*fd;
	t_fd	*head;
	int		token;
	char	*tmp;

	token = get_category(program->tokens[(*pos)]);
	if (token == ARROW_RIGHT || token == ARROW_LEFT || token == DOUBLE_ARROW_RIGHT || token == DOUBLE_ARROW_LEFT)
	{
		if (!program->tokens[(*pos + 1)])
			return (0);
	}
	if (node->fd != NULL)
	{
		fd = node->fd;
		head = fd;
		while (fd->next != NULL)
			fd = fd->next;
		fd->next = setup_fd();
		fd = fd->next;
		head = fd;
	}
	else
	{
		node->fd = setup_fd();
		fd = node->fd;
		head = fd;
	}
	if (token == ARROW_RIGHT) // > // don't forget to check if next element is not NULL
	{
		(*pos)++;
		fd->io = OUTPUT;
		fd->mode = MODE_FILE;
		tmp = ft_strjoin(get_env(program->envp, "PWD"), "/");
		fd->meta = ft_strjoin(tmp, program->tokens[(*pos)]);
		free(tmp);
		tmp = ft_strtrim(node->full_cmd, " ");
		free(node->full_cmd);
		node->full_cmd = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
		(*pos)++;
	}
	else if (token == ARROW_LEFT) // < stdin
	{
		(*pos)++;
		fd->io = INPUT;
		fd->mode = MODE_FILE;
		tmp = ft_strjoin(get_env(program->envp, "PWD"), "/");
		fd->meta = ft_strjoin(tmp, program->tokens[(*pos)]);
		free(tmp);
		tmp = NULL;
		(*pos)++;
	}
	else if (token == DOUBLE_ARROW_LEFT) // << HEREDOC
	{
		(*pos)++;
		fd->io = INPUT;
		fd->mode = MODE_HEREDOC;
		fd->meta = program->tokens[(*pos)]; // delimiter
		(*pos)++;
	}
	else if (token == DOUBLE_ARROW_RIGHT) // >> APPEND
	{
		(*pos)++;
		fd->io = OUTPUT;
		fd->mode = MODE_APPEND;
		tmp = ft_strjoin(get_env(program->envp, "PWD"), "/");
		fd->meta = ft_strjoin(tmp, program->tokens[(*pos)]);
		free(tmp);
		tmp = NULL;
		(*pos)++;
	}
	fd = head;
	return (1);
}
