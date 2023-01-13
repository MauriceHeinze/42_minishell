/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:23:00 by mheinze           #+#    #+#             */
/*   Updated: 2023/01/13 14:31:20 by mheinze          ###   ########.fr       */
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
	free_double_ptr(g_program->tokens);
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
	free_double_ptr(words);
	words = NULL;
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	(void) argc;
	(void) argv;
	init_main(envp);
	while (1)
	{
		default_signal_handler();
		line = readline("\x01\x02minishell $ \x01\x02");
		if (!line)
			break ;
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		if (handle_line(line))
			continue ;
		executor(g_program->nodes, g_program->envp);
		free_program_loop();
	}
	free_env();
	free(g_program->unknown_cmd);
	return (0);
}
