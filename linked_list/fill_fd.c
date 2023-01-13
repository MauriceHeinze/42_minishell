/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2023/01/13 18:06:56 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	arrow_right(int token, int *pos, t_node **node, t_fd **fd)
{
	char	*tmp;
	char	*tmp_2;

	if (token == ARROW_RIGHT)
	{
		(*pos)++;
		(*fd)->io = OUTPUT;
		(*fd)->mode = MODE_FILE;
		if (g_program->tokens[(*pos)][0] == '/')
			(*fd)->meta = ft_strdup(g_program->tokens[(*pos)]);
		else
		{
			tmp = ft_strjoin(get_env(g_program->envp, "PWD"), "/");
			tmp_2 = ft_strtrim(g_program->tokens[(*pos)], " ");
			(*fd)->meta = ft_strjoin(tmp, tmp_2);
			free_multiple(tmp, tmp_2, NULL, NULL);
			tmp = ft_strtrim((*node)->full_cmd, " ");
			free((*node)->full_cmd);
			if ((*node)->full_cmd)
				(*node)->full_cmd = ft_strdup(tmp);
			free_multiple(tmp, NULL, NULL, NULL);
		}
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
		if (g_program->tokens[(*pos)][0] == '/')
			(*fd)->meta = ft_strtrim(g_program->tokens[(*pos)], " ");
		else
		{
			tmp = ft_strjoin(get_env(g_program->envp, "PWD"), "/");
			tmp_2 = ft_strtrim(g_program->tokens[(*pos)], " ");
			(*fd)->meta = ft_strjoin(tmp, tmp_2);
			free_multiple(tmp, tmp_2, NULL, NULL);
		}
		(*pos)++;
	}
}

static void	double_arrow_left(int token, int *pos, t_fd **fd)
{
	if (token == DOUBLE_ARROW_LEFT)
	{
		(*pos)++;
		(*fd)->io = INPUT;
		(*fd)->mode = MODE_HEREDOC;
		(*fd)->meta = ft_strtrim(g_program->tokens[(*pos)], " 	");
		(*pos)++;
	}
}

static void	double_arrow_right(int token, int *pos, t_fd **fd)
{
	char	*tmp;
	char	*tmp_2;

	if (token == DOUBLE_ARROW_RIGHT)
	{
		(*pos)++;
		(*fd)->io = OUTPUT;
		(*fd)->mode = MODE_APPEND;
		if (g_program->tokens[(*pos)][0] == '/')
			(*fd)->meta = ft_strtrim(g_program->tokens[(*pos)], " ");
		else
		{
			tmp = ft_strjoin(get_env(g_program->envp, "PWD"), "/");
			tmp_2 = ft_strtrim(g_program->tokens[(*pos)], " ");
			(*fd)->meta = ft_strjoin(tmp, tmp_2);
			free_multiple(tmp, tmp_2, NULL, NULL);
		}
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
	double_arrow_left(token, pos, &fd);
	double_arrow_right(token, pos, &fd);
}
