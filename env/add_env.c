/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:26:25 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/13 15:00:08 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_var	*add_env_helper(t_var *env, int exists, char *name,
	char *content)
{
	char	*tmp;

	if (exists)
	{
		free(env->name);
		env->name = name;
		free(env->not_splitted);
		free(env->content);
		env->content = content;
		tmp = ft_strjoin(name, "=");
		env->not_splitted = ft_strjoin(tmp, env->content);
		free(tmp);
	}
	else
	{
		env->next = setup_var_node();
		env = env->next;
		env->name = name;
		env->content = content;
		tmp = ft_strjoin(name, "=");
		env->not_splitted = ft_strjoin(tmp, env->content);
		free(tmp);
	}
	return (env);
}

t_var	*add_env(t_var *env, char *name, char *content)
{
	t_var	*head;
	int		exists;

	head = env;
	exists = 0;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			exists = 1;
			break ;
		}
		if (env->next)
			env = env->next;
		else
			break ;
	}
	env = add_env_helper(env, exists, name, content);
	return (head);
}
