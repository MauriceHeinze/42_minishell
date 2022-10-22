/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:38:32 by rpohl             #+#    #+#             */
/*   Updated: 2022/10/22 21:14:47 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




// typedef struct s_node {
// 	char				*full_cmd; // e.g. echo, cd etc.
// 	char				*full_path; // if builtin, then it's just full_cmd, else it's path to that cmd
// 	int					pid; // default -1, is set by executor
// 	int					infile_mode; // 1. file -> full path, 2. heredoc -> delimiter, 3. stdin -> nothing 4. pipe
// 	char				*infile_meta;
// 	int					outfile_mode; // 1. file -> full path, 2. heredoc -> delimiter, 3. stdin -> nothing 4. pipe
// 	char				*outfile_meta; // full path name || delimiter || pipe id
// 	struct s_node		*next;
// }				t_node;

// Add to struct node
// int	infile_fd;
// int	outfile_fd;

// Question: is one status for all enough -> do not think so, one for each command
// new struct executor - handles all execution information which are required only once an dnot per child
// int pipe
// pid_t *pids
// int status

// Open and redirect filedescriptors. First managing input, afterwards managing output
// Comment: no error handling for input pipe failure like in bash
void fd_manager_input(s_node *node)
{
	// s_fd fd_temp = node->fd;
	// int fd_before;
	// fd_before = 1;
	// while (fd_temp != NULL)
	if (node->infile_mode == 1)
		node->infile_fd = open(node->infile_meta, O_RDONLY);
	if (node->infile_mode == 2)
	{
		here_doc(node->infile_meta);
		node->infile_fd = open(".heredoc_temp", O_RDONLY);
	}
	if (node->infile_mode == 3)
		return ;
	if (node->infile_mode == 4)
		node->infile_fd = node->pipe[0];
	dup2(node->infile_fd, 0);
	// fd_temp = ft_temp->next;	
}

// Append mode for output have to be handled -> new outfile_mode needed
// definition of fd-nodes needed
void fd_manager_output(s_node *node)
	// s_fd fd_temp = node->fd;
	// int fd_before;
	// fd_before = 1;
	// while (fd_temp != NULL)
	if (node->outfile_mode == 1 && APPEND_MODE == true)
		open(node->outfile_meta, O_TRUNC | O_CREAT | O_RDWR, 000644) 
	if (node->outfile_mode == 1 && APPEND_MOODE == false)
		open(node->outfile_meta, O_TRUNC | O_CREAT | O_RDWR, 000644) 
	if (node->outfile_mode == 2)
		return ;
	if (node->outfile_mode == 3)
		return ;
	if (node->outfile_mode == 4)
		node->outfile_fd = node->pipe[1];
	dup2(node->outfile_fd, 0);
	// fd_temp = ft_temp->next;
}

void	fd_manager(s_node *node)
{
	fd_manager_input(s_node *node);
	fd_manager_output(s_node *node);
} 

// Buildins need in field fullpath the command with
// How has exit ot be handeled? There must be some kind of signal from the child to the parent to exit minishell
void	command_executor(s_node *node, s_exec *executor)
{
	
	
	
	if (execve(get_cmd_path(pipex->cmd_paths, *args), args, envp) == -1)
		exit_msg("CMD - command not found", 127);
	



	
}

void	process_executor(s_node *node, s_exec *executor)
{
	fd_manager(s_node *node);
	if (dup2(node->outfile_fd, 1) < 0)
		exit_msg("Dup 2 output - bad fd", EXIT_FAILURE);
	// close other end of the pipe, if infile_mode or outfile_mode is pipe
	if (node->infile_mode && node->outfile_mode == 4)
		// Question: what happens if both are piped - do we need 2 pipes instead of one?
	if (node->infile_mode == 4)
		close(executor.pipe[0]);
	if (node->outfile_mode == 4)
		close(executor.pipe[1]);
	dup2_close_other(pipex, pid);
	if (dup2(node->infile_fd, 0) < 0)
		exit_msg("Dup 2 output - bad fd", EXIT_FAILURE);
	// Process the command with our own recoded builtins or the original buildtins	
	command_executor(node, executor);

	
}


// The Execution manager is started with the linked list and is the central start point for execution
// Question: how are vaiable setting and deleting processes handled? Does the Executor has to do anything before the processes are created?
int	execution_manager (s_node *node)
{	
	s_exec executor;
	s_node node_tmp;
	s_node node_wait;
	// pipe has do be creadet before forking. Need the pipe something in order to be reused?

	node_tmp = node;
	node_wait = node;
	// executor->num_processes = ft_lstsize(node); required?
	if (pipe(executor.pipe) < 0)
		exit_msg("Pipe error", EXIT_FAILURE);
	while (node_tmp != NULL)
	{
		node_tmp->pid = fork();
		if (node_tmp->pid == -1)
			exit_msg("Fork error", EXIT_FAILURE);
		if (node_tmp->pid == 0)
			process_executor(node_tmp);
		node_tmp = node_tmp->next;
	}	
	while (node != NULL)
	{
		waitpid(node->pid, &(executor.status), 0); // Should be status of process and reasign executor status afterqwars
		node_tmp = node_tmp->next;
	}
	return (WEXITSTATUS(executor.status));
}