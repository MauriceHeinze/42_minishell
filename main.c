/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:12:18 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/08 18:10:18 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"
#include "./exec/executor.h"

static void	setup_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
	setup_signal_handler();
}

static void	free_program_loop(void)
{
	free_split(program->tokens);
	free_nodes();
}

int	main(int argc, char *argv[], char *envp[])
{
	char	**words;
	char	**subwords;
	char	*line;
	char	*expanded_line;

	program = malloc(sizeof(t_program));
	if (!program)
		return (0);
	program->envp = store_env(envp);
	set_exit_code(0);
	setup_term();
	while (1)
	{
		line = readline("minishell $ ");
		if (!line)
			break ;
		if (ft_strlen(line) == 0 || is_whitespace(line))
			continue ;
		track_history(line);
		expanded_line = expand_variables(line);
		words = split_line(expanded_line);
		subwords = split_subline(words);
		if (!check_syntax(subwords))
			continue ;
		program->tokens = subwords;
		program->nodes = fill_node(program);
		if (program->nodes == NULL)
		{
			printf("minishell: %s: command not found\n", program->tokens[0]);
			free_split(program->tokens);
			free_split(words);
			continue ;
		}
		execution_manager(program->nodes, program->envp);
		free_split(words);
		words = NULL;
		free_program_loop();
		// system("leaks minishell");
	}
	free_env();
	return (0);
}