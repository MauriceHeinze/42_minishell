/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/12 01:59:42 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	node_null(t_node **node, t_fd **head, t_fd **fd)
{
	if ((*node)->fd != NULL)
	{
		*fd = (*node)->fd;
		*head = *fd;
		while ((*fd)->next != NULL)
			*fd = (*fd)->next;
		(*fd)->next = setup_fd();
		(*fd) = (*fd)->next;
		*head = *fd;
	}
	else
	{
		(*node)->fd = setup_fd();
		*fd = (*node)->fd;
		*head = *fd;
	}
}

static void	arrow_right(int token, int *pos, t_node **node, t_fd **fd)
{
	char	*tmp;
	char	*tmp_2;

	if (token == ARROW_RIGHT)
	{
		(*pos)++;
		(*fd)->io = OUTPUT;
		(*fd)->mode = MODE_FILE;
		tmp = ft_strjoin(get_env(g_program->envp, "PWD"), "/");
		tmp_2 = ft_strtrim(g_program->tokens[(*pos)], " ");
		(*fd)->meta = ft_strjoin(tmp, tmp_2);
		free(tmp);
		free(tmp_2);
		tmp = ft_strtrim((*node)->full_cmd, " ");
		free((*node)->full_cmd);
		if ((*node)->full_cmd)
			(*node)->full_cmd = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
		(*pos)++;
	}
}

static void	arrow_left(int token, int *pos, t_fd **fd)
{
	char	*tmp;
	char	*tmp_2;

	if (token == ARROW_LEFT)
	{
		(*pos)++;
		(*fd)->io = INPUT;
		(*fd)->mode = MODE_FILE;
		tmp = ft_strjoin(get_env(g_program->envp, "PWD"), "/");
		tmp_2 = ft_strtrim(g_program->tokens[(*pos)], " ");
		(*fd)->meta = ft_strjoin(tmp, tmp_2);
		free(tmp);
		free(tmp_2);
		tmp = NULL;
		(*pos)++;
	}
}

static void	double_arrow(int token, int *pos, t_fd **fd)
{
	char	*tmp;
	char	*tmp_2;

	if (token == DOUBLE_ARROW_LEFT)
	{
		(*pos)++;
		(*fd)->io = INPUT;
		(*fd)->mode = MODE_HEREDOC;
		(*fd)->meta = ft_strtrim(g_program->tokens[(*pos)], " 	");
		(*pos)++;
	}
	else if (token == DOUBLE_ARROW_RIGHT)
	{
		(*pos)++;
		(*fd)->io = OUTPUT;
		(*fd)->mode = MODE_APPEND;
		tmp = ft_strjoin(get_env(g_program->envp, "PWD"), "/");
		tmp_2 = ft_strtrim(g_program->tokens[(*pos)], " ");
		(*fd)->meta = ft_strjoin(tmp, tmp_2);
		free(tmp);
		free(tmp_2);
		tmp = NULL;
		(*pos)++;
	}
}

void	fill_fd(t_program *g_program, t_node **node, int *pos)
{
	t_fd	*fd;
	t_fd	*head;
	int		token;

	token = get_category(g_program->tokens[(*pos)]);
	node_null(node, &head, &fd);
	arrow_left(token, pos, &fd);
	arrow_right(token, pos, node, &fd);
	double_arrow(token, pos, &fd);
}
