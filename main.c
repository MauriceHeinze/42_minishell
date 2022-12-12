/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 17:29:19 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/12 01:35:20 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"
#include "./executor/executor.h"

static void	setup_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
	default_signal_handler();
}

static void	free_program_loop(void)
{
	free_split(g_program->tokens);
	free_nodes();
	free(g_program->unknown_cmd);
	g_program->unknown_cmd = NULL;
}

static void	init_main(char *envp[])
{
	g_program = malloc(sizeof(t_program));
	if (!g_program)
		exit (1);
	if (envp[0] != NULL)
		g_program->envp = store_env(envp);
	else
		g_program->envp = store_env_single(&(envp[1]));
	set_exit_code(0);
	setup_term();
}

static int	handle_line(char *line)
{
	char	**words;
	char	**subwords;
	char	*expanded_line;

	track_history(line);
	expanded_line = expand_variables(line);
	words = split_line(expanded_line);
	subwords = split_subline(words);
	if (!check_syntax(subwords))
		return (1);
	g_program->tokens = subwords;
	g_program->nodes = fill_node(g_program);
	if (g_program->nodes == NULL)
	{
		printf("minishell: %s: command not found\n", g_program->unknown_cmd);
		free_split(g_program->tokens);
		free_split(words);
		free(g_program->unknown_cmd);
		g_program->unknown_cmd = NULL;
		return (1);
	}
	free_split(words);
	words = NULL;
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	init_main(envp);
	while (1)
	{
		default_signal_handler();
		line = readline("minishell $ ");
		if (!line)
			break ;
		if (ft_strlen(line) == 0 || is_whitespace(line))
			continue ;
		if (handle_line(line))
			continue ;
		executor(g_program->nodes, g_program->envp);
		free_program_loop();
	}
	free_env();
	free(g_program->unknown_cmd);
	g_program->unknown_cmd = NULL;
	return (0);
}
