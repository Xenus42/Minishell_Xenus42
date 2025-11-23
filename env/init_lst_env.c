/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:00:00 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/23 17:46:42 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_minimum_variables(t_env **envd, char *pwd_variable)
{
	add_or_update_env(envd, pwd_variable);
	free(pwd_variable);
	add_or_update_env(envd, "SHLVL=1");
	add_or_update_env(envd, "_=/usr/bin/env");
}

void	init_minimal_lst_env(t_env **envd)
{
	int		total_path_size;
	char	*cwd;
	char	*pwd_variable;

	pwd_variable = NULL;
	total_path_size = 4096;
	cwd = ft_calloc(total_path_size, sizeof(char));
	if (!cwd)
		exit(1);
	if (getcwd(cwd, total_path_size) == NULL)
	{
		free(cwd);
		return ;
	}
	pwd_variable = ft_strjoin("PWD=", cwd);
	if (!pwd_variable)
	{
		perror("Malloc failed");
		free(cwd);
		exit(1);
	}
	free(cwd);
	process_minimum_variables(envd, pwd_variable);
}

int	create_env_node(t_env **envd, char *env_var)
{
	t_env	*node;

	if (add_back_env(envd) == 1)
		return (1);
	node = ft_lstlast_env(*envd);
	if (!node)
		return (1);
	node->key = ft_strndup(env_var, ft_strchr(env_var, '=') - env_var);
	if (!node->key)
		return (1);
	node->value = ft_strdup(ft_strchr(env_var, '=') + 1);
	if (!node->value)
		return (1);
	return (0);
}

int	init_lst_env(t_env **envd, char **env)
{
	int	i;

	i = 0;
	if (!env || !env[0])
	{
		init_minimal_lst_env(envd);
		return (0);
	}
	while (env && env[i])
	{
		if (create_env_node(envd, env[i]) != 0)
		{
			free_lst_env(envd, false, 0);
			return (1);
		}
		i++;
	}
	return (0);
}
