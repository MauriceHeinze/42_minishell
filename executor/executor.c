/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:49:49 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/11 11:45:37 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	free_double_ptr(char **ptr, int head)
{
	while (*ptr != NULL)
		free(*ptr++);
}

int	check_char(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '1')
		return (1);
	return (0);
}

void	sub_write_loop(int file, t_var *envp, char **split, int *i)
{
	int		var_length;
	char	*var;

	while (split[*i] != NULL)
	{
		var_length = 0;
		while (check_char(split[*i][var_length]))
			var_length++;
		var = malloc(sizeof(char) * (var_length + 1));
		ft_strlcpy(var, split[*i], var_length + 1);
		var[var_length] = '\0';
		if (get_env(envp, var))
			write(file, get_env(envp, var), ft_strlen(get_env(envp, var)));
		while (split[*i][var_length] != '\0')
			write(file, &(split[*i][var_length++]), 1);
		free(var);
		*i = *i + 1;
	}
}

void	sub_write(int file, char *buffer, t_var *envp, char **split)
{
	int		i;
	int		var_length;
	char	*var;

	i = 0;
	if (*buffer != '$')
	{
		write(file, split[i], ft_strlen(split[i]));
		i++;
	}
	while (split[i] != NULL)
	{
		var_length = 0;
		while (check_char(split[i][var_length]))
			var_length++;
		var = malloc(sizeof(char) * (var_length + 1));
		ft_strlcpy(var, split[i], var_length + 1);
		var[var_length] = '\0';
		if (get_env(envp, var))
			write(file, get_env(envp, var), ft_strlen(get_env(envp, var)));
		while (split[i][var_length] != '\0')
			write(file, &(split[i][var_length++]), 1);
		free(var);
		i++;
	}
}

void	heredoc(t_executor	*executor, t_var *envp)
{
	int		file;
	char	*buffer;
	char	*ret;
	char	**split;

	if (executor == NULL)
		return ;
	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		return ;
	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL)
			perror("HEREDOC ERROR");
		if (!ft_strncmp(executor->limiter, buffer,
				ft_strlen(executor->limiter)))
			break ;
		split = ft_split(buffer, '$');
		sub_write(file, buffer, envp, split);
		write(file, "\n", 1);
		free_double_ptr(split, 1);
		free(buffer);
	}
	close(file);
}

void	heredoc_handler(t_executor *executor, t_node *node_tmp, t_var *envp)
{
	t_fd	*fd_temp;

	if (executor == NULL || node_tmp == NULL)
		return ;
	fd_temp = node_tmp->fd;
	while (fd_temp != NULL)
	{
		if (fd_temp->mode == MODE_HEREDOC)
		{
			executor->limiter = fd_temp->meta;
			heredoc(executor, envp);
			executor->heredoc = open(".heredoc_tmp", O_RDONLY);
			if (executor->heredoc < 0)
			{
				unlink(".heredoc_tmp");
				perror("Read heredoc failed");
			}
		}
		fd_temp = fd_temp->next;
	}
}

char	**restore_envp(t_var *envp)
{
	char	**restored_envp;
	t_var	*temp;
	int		counter;
	int		i;

	if (envp == NULL)
		return (NULL);
	temp = envp;
	counter = 0;
	i = 0;
	while (temp != NULL)
	{
		counter++;
		temp = temp->next;
	}
	restored_envp = malloc(sizeof(char *) * (counter + 1));
	temp = envp;
	while (temp != NULL)
	{
		restored_envp[i] = temp->not_splitted;
		temp = temp->next;
		i++;
	}
	restored_envp[i] = NULL;
	return (restored_envp);
}

int	oi(char *meta, int mode, int heredoc)
{
	int	fd;

	fd = 1;
	if (mode == MODE_FILE)
	{
		fd = open(meta, O_RDONLY);
		if (fd == -1)
			dprintf(2, "File not openable %s", meta);
	}
	else if (mode == MODE_HEREDOC)
		fd = heredoc;
	return (fd);
}

void	fd_manager_input(t_node *node, t_executor *executor)
{
	t_fd	*fd_temp;
	t_fd	*fd_former;

	if (executor == NULL || node == NULL)
		return ;
	node->fd_in = 0;
	fd_temp = node->fd;
	fd_former = NULL;
	while (fd_temp != NULL)
	{
		if (fd_temp->io == 0)
			fd_temp = fd_temp->next;
		else
		{
			node->fd_in_found = 1;
			fd_temp->fd = oi(fd_temp->meta, fd_temp->mode, executor->heredoc);
			if (fd_former != NULL)
				close(fd_former->fd);
			fd_former = fd_temp;
			node->fd_in = fd_temp->fd;
			fd_temp = fd_temp->next;
		}
	}
	if (node->fd_in_found == 0 && node != executor->first_node)
		node->fd_in = executor->pipes[(node->node_num - 1) * 2];
}

int	oo(char *meta, int mode)
{
	int	fd;

	fd = 1;
	if (mode == MODE_FILE)
		fd = open(meta, O_TRUNC | O_CREAT | O_RDWR, 000644);
	else if (mode == MODE_APPEND)
		fd = open(meta, O_APPEND | O_CREAT | O_RDWR, 000644);
	return (fd);
}

void	fd_manager_output(t_node *node, t_executor	*executor)
{
	t_fd	*fd_temp;
	t_fd	*fd_former;

	if (executor == NULL || node == NULL)
		return ;
	node->fd_out = 1;
	fd_temp = node->fd;
	fd_former = NULL;
	while (fd_temp != NULL)
	{
		if (fd_temp->io == 1)
			fd_temp = fd_temp->next;
		else
		{
			node->fd_out_found = 1;
			fd_temp->fd = oo(fd_temp->meta, fd_temp->mode);
			if (fd_former != NULL)
				close(fd_former->fd);
			fd_former = fd_temp;
			node->fd_out = fd_temp->fd;
			fd_temp = fd_temp->next;
		}
	}
	if (node->fd_out_found == 0 && node->next != NULL)
		node->fd_out = executor->pipes[node->node_num * 2 + 1];
}

static int	child_process(t_executor *ex, int pid, t_var *envp, t_node *node)
{
	char	**args;
	char	**re;

	re = restore_envp(envp);
	args = ft_split(node->full_cmd_orig, ' ');
	dup2_close_other(ex, pid, node);
	if (execve(get_cmd_path(ex->cmd_paths, *args), args, re) == -1)
	{
		free_double_ptr(re, 1);
		free_double_ptr(args, 1);
		close(node->fd_out);
		close(node->fd_in);
		exit_msg("CMD - command not found", 127);
	}
	return (0);
}

static void	init_executor(t_executor *executor, t_var *envp, t_node *node)
{
	if (executor->num_pipes > 0)
		executor->pipes = malloc(sizeof(int) * 2 * executor->num_pipes);
	executor->pids = malloc(sizeof(pid_t) * executor->num_processes);
	executor->cmd_paths = get_cmd_paths(envp);
	executor->status = 0;
	executor->first_node = node;
}

void	prepare_child_process(t_executor *executor,
t_var *envp, t_node *node, int x)
{
	executor->pids[x] = fork();
	if (executor->pids[x] == -1)
		exit_msg("Fork error", EXIT_FAILURE);
	if (executor->pids[x] == 0)
	{
		fd_manager_output(node, executor);
		fd_manager_input(node, executor);
		child_process(executor, x + 1, envp, node);
	}
}

static void	fork_processes(t_executor *executor, t_var *envp, t_node *node)
{
	int		x;

	x = 0;
	while (node != NULL)
	{
		if (node->full_path == NULL && node->full_cmd == NULL
			&& node->full_cmd_orig == NULL)
		{
			fd_manager_output(node, executor);
			fd_manager_input(node, executor);
		}
		if (ft_strcmp(node->full_path, "builtin") != 0)
			prepare_child_process(executor, envp, node, x);
		else if (ft_strcmp(node->full_path, "builtin") == 0)
		{
			fd_manager_output(node, executor);
			fd_manager_input(node, executor);
			builtin_caller(node, executor, envp);
		}
		x++;
		node = node->next;
	}
}

static void	check_args(t_executor *executor, t_node *node)
{
	t_node	*node_tmp;

	if (executor == NULL || node == NULL)
		return ;
	executor->num_processes = 0;
	executor->num_pipes = 0;
	node_tmp = node;
	while (node_tmp != NULL)
	{
		executor->num_processes += 1;
		node_tmp = node_tmp->next;
	}
	node_tmp = node;
	while (node_tmp->next != NULL)
	{
		executor->num_pipes += 1;
		node_tmp = node_tmp->next;
	}
}

void	init_node_num(t_node *node)
{
	t_node	*node_tmp;
	int		i;

	if (node == NULL)
		return ;
	i = 0;
	node_tmp = node;
	while (node_tmp != NULL)
	{
		node_tmp->node_num = i++;
		node_tmp->fd_in_found = 0;
		node_tmp->fd_out_found = 0;
		node_tmp = node_tmp->next;
	}
}

int	executor(t_node *node, t_var *envp)
{
	t_executor	executor;
	int			i;

	i = 0;
	init_node_num(node);
	check_args (&executor, node);
	init_executor (&executor, envp, node);
	create_pipes(&executor);
	heredoc_handler(&executor, node, envp);
	fork_processes(&executor, envp, node);
	while (i < executor.num_processes)
		waitpid(executor.pids[i++], &(executor.status), 0);
	if (!WIFSIGNALED(executor.status))
		set_exit_code(WEXITSTATUS(executor.status));
	else if (WIFSIGNALED(executor.status))
		set_exit_code(WTERMSIG(executor.status) + 128);
	close_other_fd(&executor, -1, -1);
	if (executor.num_pipes > 0)
		free(executor.pipes);
	free(executor.pids);
	free_double_ptr(executor.cmd_paths, 0);
	return (0);
}
