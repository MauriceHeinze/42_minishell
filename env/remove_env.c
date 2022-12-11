/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:26:25 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/11 16:57:59 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_var(t_var *var)
{
	free(var->name);
	free(var->content);
	free(var->not_splitted);
	free(var);
}

void	remove_env(t_var *env, char *name)
{
	t_var	*head;
	t_var	*tmp;

	head = env;
	if (ft_strcmp(env->name, name) == 0)
	{
		head = env->next;
		free_var(env);
		g_program->envp = head;
	}
	while (env)
	{
		if (!env->next)
			break ;
		if (ft_strcmp(env->next->name, name) == 0)
		{
			tmp = env->next;
			env->next = tmp->next;
			free_var(tmp);
		}
		env = env->next;
	}
	g_program->envp = head;
}
