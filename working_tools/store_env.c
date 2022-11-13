#include "../inc/minishell.h"

t_var	*setup_var_node(void)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);

	var->name = NULL;
	var->content = NULL;
	var->next = NULL;
	return (var);
}

static t_var	*setup_node(void)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);

	var->name = NULL;
	var->content = NULL;
    var->not_splitted = NULL;
	var->next = NULL;
	return (var);
}

t_var	*store_env(char *env[])
{
    t_var   *var;
    t_var   *head;
    int     last_pos;
    int     i;
    int     k;

    var = setup_node();
    head = var;
    last_pos = 0;
    i = 0;
	while (env[i])
    {
        k = 0;
        while (env[i][k] != '\0')
            k++;
        var->not_splitted = ft_substr(env[i], 0, k);
        k = 0;
        while (env[i][k] != '\0' && env[i][k] != '=')
            k++;
        last_pos = k;
        var->name = ft_substr(env[i], 0, k);
        if (env[i][k] == '=')
            k++;
        last_pos = k;
        while (env[i][k] != '\0')
            k++;
        var->content = ft_substr(env[i], last_pos, k);
        if (env[i + 1] != NULL)
        {
            var->next = setup_node();
            var = var->next;
        }
        i++;
    }
    return (head);
}

// TODO: Add check for double
t_var	*add_env(t_var *env, char *name, char* content)
{
    t_var *head;

    head = env;
    while (env->next != NULL)
        env = env->next;
    env->next = setup_node();
    env = env->next;
    env->name = name;
    env->content = content;
    env->not_splitted = ft_strjoin(name, "=");
    env->not_splitted = ft_strjoin(env->not_splitted, env->content);
    return (head);
}

void    remove_env(t_var *env, char *name)
{
    t_var *head;
    t_var *tmp;

    head = env;

    // check first element
    // printf("name: %s\n", env->name);
    if (ft_strcmp(env->name, name) == 0) // found it!
    {
        head = env->next;
        // free(env);
        program->envp = head;
    }
    // check next elements
    while (env)
    {
        if (!env->next)
            break;
        // printf("Here\n");
        if (ft_strcmp(env->next->name, name) == 0) // found it!
        {
            tmp = env->next;
            // remove next node
            // set pointer to next node
            env->next = tmp->next;
        }
        env = env->next;
    }
    program->envp = head;
}

char	*get_env(t_var *env, char *name)
{
	while (env)
    {
        if (ft_strcmp(env->name, name) == 0)
            return (env->content);
        env = env->next;
    }
    return (NULL);
}