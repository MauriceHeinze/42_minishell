/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/10 17:07:12 by mheinze          ###   ########.fr       */
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

static void	one_arrow(int token, int *pos, t_node **node, t_fd **fd)
{
	char *tmp;

	if (token == ARROW_RIGHT) // > // don't forget to check if next element is not NULL
	{
		(*pos)++;
		(*fd)->io = OUTPUT;
		(*fd)->mode = MODE_FILE;
		tmp = ft_strjoin(get_env(program->envp, "PWD"), "/");
		(*fd)->meta = ft_strjoin(tmp, program->tokens[(*pos)]);
		free(tmp);
		tmp = ft_strtrim((*node)->full_cmd, " ");
		free((*node)->full_cmd);
		(*node)->full_cmd = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
		(*pos)++;
	}
	else if (token == ARROW_LEFT) // < stdin
	{
		(*pos)++;
		printf("token is: %s\n", program->tokens[(*pos)]);
		(*fd)->io = INPUT;
		(*fd)->mode = MODE_FILE;
		tmp = ft_strjoin(get_env(program->envp, "PWD"), "/");
		(*fd)->meta = ft_strjoin(tmp, program->tokens[(*pos)]);
		free(tmp);
		tmp = NULL;
		(*pos)++;
	}
}

static void	double_arrow(int token, int *pos, t_fd **fd)
{
	char *tmp;

	if (token == DOUBLE_ARROW_LEFT) // << HEREDOC
	{
		(*pos)++;
		(*fd)->io = INPUT;
		(*fd)->mode = MODE_HEREDOC;
		(*fd)->meta = program->tokens[(*pos)]; // delimiter
		(*pos)++;
	}
	else if (token == DOUBLE_ARROW_RIGHT) // >> APPEND
	{
		(*pos)++;
		(*fd)->io = OUTPUT;
		(*fd)->mode = MODE_APPEND;
		tmp = ft_strjoin(get_env(program->envp, "PWD"), "/");
		(*fd)->meta = ft_strjoin(tmp, program->tokens[(*pos)]);
		free(tmp);
		tmp = NULL;
		(*pos)++;
	}
}


void	fill_fd(t_program *program, t_node **node, int *pos)
{
	t_fd	*fd;
	t_fd	*head;
	int		token;
	char	*tmp;

	token = get_category(program->tokens[(*pos)]);
	node_null(node, &head, &fd);
	one_arrow(token, pos, node, &fd);
	double_arrow(token, pos, &fd);
}

// echo hallo > file.txt > file1.txt | echo hallo > 1file.txt > 2file.txt



// void	fill_fd(t_program *program, t_node *node, int *pos)
// {
// 	t_fd	*fd;
// 	t_fd	*head;
// 	int		token;
// 	char	*tmp;

// 	token = get_category(program->tokens[(*pos)]);
// 	if (node->fd != NULL)
// 	{
// 		fd = node->fd;
// 		head = fd;
// 		while (fd->next != NULL)
// 			fd = fd->next;
// 		fd->next = setup_fd();
// 		fd = fd->next;
// 		head = fd;
// 	}
// 	else
// 	{
// 		node->fd = setup_fd();
// 		fd = node->fd;
// 		head = fd;
// 	}
// 	if (token == ARROW_RIGHT) // > // don't forget to check if next element is not NULL
// 	{
// 		(*pos)++;
// 		fd->io = OUTPUT;
// 		fd->mode = MODE_FILE;
// 		tmp = ft_strjoin(get_env(program->envp, "PWD"), "/");
// 		fd->meta = ft_strjoin(tmp, program->tokens[(*pos)]);
// 		free(tmp);
// 		tmp = NULL;
// 		(*pos)++;
// 	}
// 	else if (token == ARROW_LEFT) // < stdin
// 	{
// 		(*pos)++;
// 		fd->io = INPUT;
// 		fd->mode = MODE_FILE;
// 		tmp = ft_strjoin(get_env(program->envp, "PWD"), "/");
// 		fd->meta = ft_strjoin(tmp, program->tokens[(*pos)]);
// 		free(tmp);
// 		tmp = NULL;
// 		(*pos)++;
// 	}
// 	else if (token == DOUBLE_ARROW_LEFT) // << HEREDOC
// 	{
// 		(*pos)++;
// 		fd->io = INPUT;
// 		fd->mode = MODE_HEREDOC;
// 		fd->meta = program->tokens[(*pos)]; // delimiter
// 		(*pos)++;
// 	}
// 	else if (token == DOUBLE_ARROW_RIGHT) // >> APPEND
// 	{
// 		(*pos)++;
// 		fd->io = OUTPUT;
// 		fd->mode = MODE_APPEND;
// 		tmp = ft_strjoin(get_env(program->envp, "PWD"), "/");
// 		fd->meta = ft_strjoin(tmp, program->tokens[(*pos)]);
// 		free(tmp);
// 		tmp = NULL;
// 		(*pos)++;
// 	}
// 	fd = head;
// }