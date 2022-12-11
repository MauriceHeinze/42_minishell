/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handle_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/11 16:57:59 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_fd	*fd_redirect_output(t_node *node, t_fd *fd, int *pos)
{
	char	*tmp;
	char	*tmp_2;

	(*pos)++;
	fd->io = OUTPUT;
	fd->mode = MODE_FILE;
	tmp = ft_strjoin(get_env(g_program->envp, "PWD"), "/");
	tmp_2 = ft_strtrim(g_program->tokens[(*pos)], " ");
	fd->meta = ft_strjoin(tmp, tmp_2);
	free(tmp);
	free(tmp_2);
	tmp = ft_strtrim(node->full_cmd, " ");
	free(node->full_cmd);
	node->full_cmd = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	(*pos)++;
	return (fd);
}

static t_fd	*fd_stdin(t_node *node, t_fd *fd, int *pos)
{
	char	*tmp;

	(*pos)++;
	fd->io = INPUT;
	fd->mode = MODE_FILE;
	tmp = ft_strjoin(get_env(g_program->envp, "PWD"), "/");
	fd->meta = ft_strjoin(tmp, g_program->tokens[(*pos)]);
	free(tmp);
	tmp = NULL;
	(*pos)++;
	return (fd);
}

static t_fd	*fd_heredoc(t_node *node, t_fd *fd, int *pos)
{
	(*pos)++;
	fd->io = INPUT;
	fd->mode = MODE_HEREDOC;
	fd->meta = g_program->tokens[(*pos)];
	(*pos)++;
	return (fd);
}

static t_fd	*fd_append(t_node *node, t_fd *fd, int *pos)
{
	char	*tmp;

	(*pos)++;
	fd->io = OUTPUT;
	fd->mode = MODE_APPEND;
	tmp = ft_strjoin(get_env(g_program->envp, "PWD"), "/");
	fd->meta = ft_strjoin(tmp, g_program->tokens[(*pos)]);
	free(tmp);
	tmp = NULL;
	(*pos)++;
	return (fd);
}

void	fd_handle_redirection(int category, t_node *node, t_fd *fd, int *pos)
{
	if (category == ARROW_RIGHT)
		fd_redirect_output(node, fd, pos);
	else if (category == ARROW_LEFT)
		fd_stdin(node, fd, pos);
	else if (category == DOUBLE_ARROW_LEFT)
		fd_heredoc(node, fd, pos);
	else if (category == DOUBLE_ARROW_RIGHT)
		fd_append(node, fd, pos);
}
