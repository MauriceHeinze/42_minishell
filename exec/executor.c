/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:38:32 by rpohl             #+#    #+#             */
/*   Updated: 2022/10/25 17:18:02 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "executor.h"

// Add to struct node
// int	infile_fd;
// int	outfile_fd;

// Question: is one status for all enough -> do not think so, one for each command
// new struct executor - handles all execution information which are required only once an dnot per child
// int pipe
// pid_t *pids
// int status




// Buildins need in field fullpath the command with
// How has exit ot be handeled? There must be some kind of signal from the child to the parent to exit minishell
void	command_executor(t_node *node, t_exec *executor, char *envp[])
{
	char	**cmd_paths = get_cmd_paths(envp);
	char	**args = ft_split(node->full_cmd, ' ');

	if (execve(get_cmd_path(cmd_paths, *args), args, envp) == -1)
		{
			perror("");
			exit(127);	
		}
	
	// while (*args != NULL)
	// 	free(*args++);
	// free(args);
}

// Handling of pipes is undefined now
// Open and redirect filedescriptors. First managing input, afterwards managing output
// Comment: no error handling for input pipe failure like in bash
void fd_manager_input(t_node *node, t_exec	*executor)
{
	t_fd	*fd_temp;
	t_fd	*fd_pipe;
	t_fd	*fd_former;
	
	fd_temp = node->fd;
	fd_pipe = node->fd;
	fd_former = NULL;
	// if (fd_temp == NULL && executor->x > 0 && executor->pipes > 0)
	// 	{
	// 		// int err = open("err", O_TRUNC | O_CREAT | O_RDWR, 000644);
	// 		// dprintf(err, "x = %d - pipes = %d", executor->x, executor->pipes);
	// 		dup2(executor->pipe[0], 0);
	// 	}

	while(fd_pipe != NULL)
	{
		if (fd_pipe->io == 1)
			break;
		if (fd_pipe->next == NULL)
			dup2(executor->pipe[0], 0);
		fd_pipe = fd_pipe->next;
	}
	fd_pipe = node->fd;
	
	while (fd_temp != NULL)
	{
		if (fd_temp->io == 0)
			fd_temp = fd_temp->next;
		else
		{
			dprintf(2, "Next infile is on run %d: %s\n", executor->x, fd_temp->meta);
			if (fd_temp->mode == MODE_FILE)
				fd_temp->fd = open(fd_temp->meta, O_RDONLY);
			// else if (fd_temp->mode == MODE_HEREDOC)
				//HEREDOC
			else if (fd_temp->mode == MODE_STDIN)
				fd_temp->fd = 0;
			if (fd_former != NULL)
				close(fd_former->fd);
			dup2(fd_temp->fd, 0);
			fd_former = fd_temp;
			fd_temp = fd_temp->next;
		}
	}
}

// Append mode for output have to be handled -> new outfile_mode needed
// definition of fd-nodes needed
void fd_manager_output(t_node *node, t_exec	*executor)
{
	t_fd	*fd_temp;
	t_fd	*fd_pipe;
	t_fd	*fd_former;
	
	fd_temp = node->fd;
	fd_pipe = node->fd;
	fd_former = NULL;

	// if (fd_temp == NULL && executor->x < executor->pipes && executor->pipes > 0)
	// {
	// 	int err = open("err", O_TRUNC | O_CREAT | O_RDWR, 000644);
	// 		dprintf(err, "x = %d - pipes = %d", executor->x, executor->pipes);
	// 	dup2(executor->pipe[1], 1);
	// }
	while(fd_pipe != NULL)
	{
		if (fd_pipe->io == 0)
			break;
		if (fd_pipe->next == NULL)
			dup2(executor->pipe[1], 1);
		fd_pipe = fd_pipe->next;
	}

	
	while (fd_temp != NULL)
	{
		if (fd_temp->io == 1)
			fd_temp = fd_temp->next;
		else
		{
			dprintf(2, "Next outfile is on run %d: %s\n", executor->x, fd_temp->meta);
			if (fd_temp->mode == MODE_FILE)
				fd_temp->fd = open(fd_temp->meta, O_TRUNC | O_CREAT | O_RDWR, 000644);
			else if (fd_temp->mode == MODE_STDIN)
				fd_temp->fd = 1;
			else if (fd_temp->mode == MODE_APPEND)
				fd_temp->fd = open(fd_temp->meta, O_APPEND | O_CREAT | O_RDWR, 000644);
			if (fd_former != NULL)
				close(fd_former->fd);
			dup2(fd_temp->fd, 1);
			fd_former = fd_temp;
			fd_temp = fd_temp->next;
		}
	}
}

// There needs ot be a definition if the standard input and output is a pipe aor not - defined by first, middle, last processes
void	process_executor(t_node *node, t_exec *executor, char *envp[])
{
	// dprintf(2, "executor started with %s\n", node->full_cmd);
	t_fd	*fd_temp;
	
	fd_temp = node->fd;
	fd_manager_output(node, executor);
	close(executor->pipe[1]);
	fd_manager_input(node, executor);
	close(executor->pipe[0]);
	// while(fd_temp != NULL)
	// {
	// 	close(fd_temp->fd);
	// 	fd_temp = fd_temp->next;	
	// }
	
	command_executor(node, executor, envp);
}


// The Execution manager is started with the linked list and is the central start point for execution
// Question: how are vaiable setting and deleting processes handled? Does the Executor has to do anything before the processes are created?
int	execution_manager (t_node *node, char *envp[])
{	
	// dprintf(2, "execution manager reached\nNode has command%s", node->full_cmd);
	t_exec	executor;
	t_node	*node_tmp;
	t_node	*node_wait;
	// pipe has do be creadet before forking. Need the pipe something in order to be reused?
	node_tmp = node;
	node_wait = node;
	// executor->num_processes = ft_lstsize(node); required?


	executor.pipes = 0;
	executor.x = 0;
	if (pipe(executor.pipe) < 0)
		perror("");
	// Temp pipe handler until included in node
	while(node_tmp->next)
	{
		executor.pipes += 1;
		node_tmp = node_tmp->next;
	}
	node_tmp = node;
	
	
	while (node_tmp != NULL)
	{
		node_tmp->pid = fork();
		// dprintf(2, "<%d>", node_tmp->pid);
		if (node_tmp->pid == -1)
			perror("");
		if (node_tmp->pid == 0)
		{
			process_executor(node_tmp, &executor, envp);
		}
		sleep(2);
		// else
		// 	waitpid(node_tmp->pid, &(executor.status), 0);
		node_tmp = node_tmp->next;
		executor.x++;
	}
	while (node_wait != NULL)
	{
		waitpid(node_wait->pid, &(executor.status), 0); // Should be status of process and reasign executor status afterqwars
		node_wait = node_wait->next;
	}
	// return (WEXITSTATUS(executor.status));
	return (0);
}