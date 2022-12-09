/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:49:49 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/08 13:27:28 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (fd_temp->mode == MODE_FILE)
				fd_temp->fd = open(fd_temp->meta, O_RDONLY);
			// else if (fd_temp->mode == MODE_HEREDOC)
			// 	fd_temp->fd = executor->heredoc;
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
			if (fd_temp->mode == MODE_FILE)
				fd_temp->fd = open(fd_temp->meta, O_TRUNC | O_CREAT | O_RDWR, 000644);
			else if (fd_temp->mode == MODE_APPEND)
				fd_temp->fd = open(fd_temp->meta, O_APPEND | O_CREAT | O_RDWR, 000644);
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

static int	child_process(t_executor	*executor, int pid,  t_var *envp, t_node *node)
{
	char	**args;
	char	**restored_envp;

	restored_envp = restore_envp(envp);
	args = ft_split(node->full_cmd_orig, ' ');
	dup2_close_other(executor, pid, node);
	// dprintf(2, "execve(%s, args, %s %s %s,restored_envp)\n", get_cmd_path(executor->cmd_paths, *args), args[0], args[1], args[2]);
	if (execve(get_cmd_path(executor->cmd_paths, *args), args, restored_envp) == -1)
	{
		while (*restored_envp != NULL)
			free(*restored_envp++);
		free(restored_envp);
		while (*args != NULL)
			free(*args++);
		free(args);
		close(node->fd_out);
		close(node->fd_in);
		exit_msg("CMD - command not found", 127);
	}
	return(0);
}

static void	init_executor(t_executor *executor, t_var *envp, t_node *node)
{
	executor->pipes = malloc(sizeof(int) * 2 * executor->num_pipes);
	executor->pids = malloc(sizeof(pid_t) * executor->num_processes);
	executor->cmd_paths = get_cmd_paths(envp);
	executor->status = 0;
	executor->first_node = node;
	executor->fd_out_original = dup(1);
	executor->fd_in_original = dup(0);
	// executor->fd1 = open("infile.txt", O_RDONLY);
	// 	if (executor->fd1 == -1)
	// 		perror("argv[1]");
	// executor->fd2 = 2; //open("make_new", O_TRUNC | O_CREAT | O_RDWR, 000644);
	// 	if (executor->fd2 == -1)
	// 		perror("argv[argc - 1]");
}

static void	fork_processes(t_executor *executor, t_var *envp, t_node *node)
{
	int		x;

	x = 0;
	// if (executor->limiter != NULL)
	// 	here_doc(argv[2], executor);
	while (node != NULL)
	{
		if (ft_strcmp(node->full_path, "builtin") != 0)
		{
			executor->pids[x] = fork();
			if (executor->pids[x] == -1)
				exit_msg("Fork error", EXIT_FAILURE);
			if (executor->pids[x] == 0)
			{
				fd_manager_output(node, executor);
				fd_manager_input(node, executor);
				// dprintf(2, "fd_out is %d and fd_in is %d", node->fd_out, node->fd_in);
				child_process(executor, x + 1, envp, node);
			}
			
		}
		else if (ft_strcmp(node->full_path, "builtin") == 0)
		{
			fd_manager_output(node, executor);
			fd_manager_input(node, executor);
			// dprintf(2, "fd_out is %d and fd_in is %d", node->fd_out, node->fd_in);
			// dup2_close_other(executor, x + 1, node);
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
		// if (ft_strcmp(node_tmp->full_path, "builtin") != 0)
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
		return;
	i = 0;
	node_tmp = node;
	while(node_tmp != NULL)
	{
		node_tmp->node_num = i++;
		node_tmp->fd_in_found = 0;
		node_tmp->fd_out_found = 0;
		node_tmp=node_tmp->next;
	}
}


int	executor(t_node *node, t_var *envp)
{
	t_executor	executor;
	int		i;

	i = 0;
	init_node_num(node);
	check_args (&executor, node);
	init_executor (&executor, envp, node);
	create_pipes(&executor);
	fork_processes(&executor, envp, node);
	close_fd(&executor);
	while (*executor.cmd_paths != NULL)
		free(*executor.cmd_paths++);
	// waitpid(-1, &executor.status, 0); 
	while (i < executor.num_processes)
	{
		waitpid(executor.pids[i], &(executor.status), 0);
		i++;
	}
	close_other_fd(&executor, -1, -1);
	// if (!WIFSIGNALED(executor.status))
	// 	set_exit_code(WEXITSTATUS(executor.status));
	// else if (WIFSIGNALED(executor.status))
	// 	set_exit_code(WTERMSIG(executor.status) + 128);
	return (0);
}

// int	main(int argc, char *argv[])
// {
// 	t_node	node1;
// 	t_node	node2;
// 	t_var *envp = NULL;
// 	node1.full_cmd = "cat";
// 	node1.fd = NULL;
// 	node1.full_cmd_orig = "cat input.txt";
// 	node1.full_path = "/bin/cat";
// 	node1.next = &node2;
// 	node1.pid= -1;
// 	node2.full_cmd = "cat";
// 	node2.fd = NULL;
// 	node2.full_cmd_orig = "cat";
// 	node2.full_path = "/bin/cat";
// 	node2.next = NULL;
// 	node2.pid= -1;
// 	return(executor(&node1, envp));
// }
