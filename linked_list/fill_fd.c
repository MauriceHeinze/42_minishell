/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/06 14:21:26 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	if (token == ARROW_RIGHT || token == ARROW_LEFT
		|| token == DOUBLE_ARROW_RIGHT || token == DOUBLE_ARROW_LEFT)
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
	if (token == ARROW_RIGHT)
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
	else if (token == ARROW_LEFT)
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
	else if (token == DOUBLE_ARROW_LEFT)
	{
		(*pos)++;
		fd->io = INPUT;
		fd->mode = MODE_HEREDOC;
		fd->meta = program->tokens[(*pos)];
		(*pos)++;
	}
	else if (token == DOUBLE_ARROW_RIGHT)
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
