/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:38:32 by rpohl             #+#    #+#             */
/*   Updated: 2022/11/16 19:00:06 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "executor.h"

char **restore_envp(t_var *envp)
{
	char 	**restored_envp;
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

void	command_executor(t_node *node, t_exec *executor, t_var *envpn)
{
	char	**cmd_paths;
	char	**args;
	char	**restored_envp;

	cmd_paths = get_cmd_paths(envpn);
	restored_envp = restore_envp(envpn);
	args = ft_split(node->full_cmd_orig, ' ');
	if (execve(get_cmd_path(cmd_paths, *args), args, restored_envp) == -1)
	{
		perror("CMD - command not found");
		free(restored_envp);
		if (executor->fd_out != 1 && executor->fd_out != 2)
			close(executor->fd_out);
		if (executor->fd_in != 0)
			close(executor->fd_in);
		exit(127);
	}
}

void heredoc(t_exec	*executor)
{
	int		file;
	char	*buffer;
	char	*ret;

	if (executor == NULL)
		return ;
	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
	{
		perror("heredoc tempfile error");
		return ;
	}
	while (1)
	{
		buffer = readline("HEREDOC:");
		if (buffer == NULL)
			perror("GNL Error");
		if (!ft_strncmp(executor->limiter, buffer, ft_strlen(executor->limiter)))
			break ;
		write(file, buffer, ft_strlen(buffer));
		write(file, "\n", 1);
		free(buffer);
	}
	free(buffer);
	close(file);
}

void	fd_manager_input(t_node *node, t_exec *executor)
{
	t_fd	*fd_temp;
	t_fd	*fd_former;
	int		found_fd;

	if (executor == NULL || node == NULL)
		return ;
	fd_temp = node->fd;
	fd_former = NULL;
	found_fd = 0;
	while (fd_temp != NULL)
	{
		if (fd_temp->io == 0)
			fd_temp = fd_temp->next;
		else
		{
			found_fd = 1;
			if (fd_temp->mode == MODE_FILE)
				fd_temp->fd = open(fd_temp->meta, O_RDONLY);
			else if (fd_temp->mode == MODE_HEREDOC)
				fd_temp->fd = executor->heredoc;
			if (fd_former != NULL)
				close(fd_former->fd);
			if (dup2(fd_temp->fd, 0) < 0)
				perror("Dup 2 input error");
			fd_former = fd_temp;
			executor->fd_in = fd_temp->fd;
			fd_temp = fd_temp->next;
		}
	}
	if (found_fd == 0 && node != executor->first_node)
	{
		if (dup2(executor->pipe[0], 0) < 0)
			perror("Dup 2 input pipe error");
	}
}

void	fd_manager_output(t_node *node, t_exec	*executor)
{
	t_fd	*fd_temp;
	t_fd	*fd_former;
	int		found_fd;

	if (executor == NULL || node == NULL)
		return ;
	fd_temp = node->fd;
	fd_former = NULL;
	found_fd = 0;
	while (fd_temp != NULL)
	{
		if (fd_temp->io == 1)
			fd_temp = fd_temp->next;
		else
		{
			found_fd = 1;
			if (fd_temp->mode == MODE_FILE)
				fd_temp->fd = open(fd_temp->meta, O_TRUNC | O_CREAT | O_RDWR, 000644);
			else if (fd_temp->mode == MODE_APPEND)
				fd_temp->fd = open(fd_temp->meta, O_APPEND | O_CREAT | O_RDWR, 000644);
			if (fd_former != NULL)
				close(fd_former->fd);
			if (dup2(fd_temp->fd, 1) < 0)
				perror("Dup 2 output error");
			fd_former = fd_temp;
			executor->fd_out = fd_temp->fd;
			fd_temp = fd_temp->next;
		}
	}
	if (found_fd == 0 && node->next != NULL)
	{
		if (dup2(executor->pipe[1], 1) < 0)
			perror("Dup 2 output pipe error");
	}
}

void	fd_manager_output_builtin(t_node *node, t_exec	*executor)
{
	t_fd	*fd_temp;
	t_fd	*fd_former;
	int		found_fd;

	if (executor == NULL || node == NULL)
		return ;
	fd_temp = node->fd;
	fd_former = NULL;
	found_fd = 0;
	while (fd_temp != NULL)
	{
		if (fd_temp->io == 1)
			fd_temp = fd_temp->next;
		else
		{
			found_fd = 1;
			if (fd_temp->mode == MODE_FILE)
				fd_temp->fd = open(fd_temp->meta, O_TRUNC | O_CREAT | O_RDWR, 000644);
			else if (fd_temp->mode == MODE_APPEND)
				fd_temp->fd = open(fd_temp->meta, O_APPEND | O_CREAT | O_RDWR, 000644);
			if (fd_former != NULL)
				close(fd_former->fd);
			fd_former = fd_temp;
			fd_temp = fd_temp->next;
		}
	}
	if (found_fd == 0)
		executor->fd_out = 1;
	else
		executor->fd_out = fd_former->fd;
	if (node->next != NULL)
		close(executor->pipe[0]);
}

void	process_executor(t_node *node, t_exec *executor, t_var *envp)
{
	if (executor == NULL || node == NULL || envp == NULL)
		return ;
	fd_manager_output(node, executor);
	fd_manager_input(node, executor);
	command_executor(node, executor, envp);
}

void	buildin_executor(t_node *node, t_exec *executor, t_var *envp)
{
	if (executor == NULL || node == NULL || envp == NULL)
		return ;
	fd_manager_output_builtin(node, executor);
	fd_manager_input(node, executor);
	executor->status = builtin_caller(node, executor, envp);
}

void	heredoc_handler(t_exec *executor, t_node *node_tmp)
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
			heredoc(executor);
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

void	init_exec_manager(t_exec *executor, t_node *node)
{
	t_node	*node_tmp;

	if (executor == NULL || node == NULL)
		return ;
	node_tmp = node;
	executor->pipes = 0;
	executor->pid_old = 1;
	executor->status = 0;
	executor->heredoc = -1;
	executor->first_node = node;
	while (node_tmp->next != NULL)
	{
		executor->pipes += 1;
		node_tmp = node_tmp->next;
	}
	if (executor->pipes > 0)
	{
		if (pipe(executor->pipe) < 0)
			perror("Pipe error");
	}
	executor->fd_out = 0;
}

int sub_exec(t_node *node, t_exec *executor, t_var *envp)
{
	int	exit_code;

	exit_code = 0;	
	if (ft_strcmp(node->full_path, "builtin") == 0)
		buildin_executor(node, executor, envp);
	else
	{
		node->pid = fork();
		if (node->pid == -1)
			perror("Fork failed");
		if (node->pid == 0)
			process_executor(node, executor, envp);
		else
			waitpid(node->pid, &(executor->status), 0);
	}
	if (node->next != NULL)
		exit_code = sub_exec(node->next, executor, envp);
	return (WEXITSTATUS(exit_code));
}

// env -i plus call let occure a seg vault - call was "env -i ./a.out"
int	execution_manager (t_node *node, t_var *envp)
{
	t_exec	executor;
	t_node	*node_tmp;

	if (node == NULL || envp == NULL || node->full_path == NULL)
		return (-1);
	node_tmp = node;
	init_exec_manager(&executor, node);
	heredoc_handler(&executor, node);
	executor.status = sub_exec(node, &executor, envp);
	// while (node != NULL && executor.pid_old > 0)
	// {
	// 	if (ft_strcmp(node->full_path, "builtin") == 0)
	// 		buildin_executor(node, &executor, envp);
	// 	else
	// 	{
	// 		node->pid = fork();
	// 		if (node->pid == -1)
	// 			perror("Fork failed");
	// 		if (node->pid == 0)
	// 			process_executor(node, &executor, envp);
	// 		else
	// 			waitpid(node->pid, &(executor.status), 0);
	// 		executor.pid_old = node->pid;
	// 	}
	// 	node = node->next;
	// }
	return (executor.status);
}
