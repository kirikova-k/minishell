/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:05:39 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/12 15:28:36 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_cmd(t_command *cmd)
{
	int	res;

	res = 0;
	while (cmd)
	{
		res++;
		cmd = cmd->next;
	}
	return (res);
}

int	ft_count_envp(t_env *envp)
{
	int	res;

	res = 0;
	while (envp)
	{
		res++;
		envp = envp->next;
	}
	return (res);
}

void	ft_make_array(t_env *envp, char ***env, int len, t_arg *data)
{
	int		i;
	char	*arr;

	(void)data;
	i = -1;
	while (++i < len)
	{
		(*env)[i] = ft_strdup(envp->key);
		if (*envp->separator)
		{
			arr = ft_strjoin((*env)[i], envp->separator);
			free((*env)[i]);
			(*env)[i] = arr;
		}
		if (*envp->value)
		{
			arr = ft_strjoin((*env)[i], envp->value);
			free((*env)[i]);
			(*env)[i] = arr;
		}
		envp = envp->next;
	}
	(*env)[i] = NULL;
}

void	ft_env_list_to_array(t_env *envp, char ***env, t_arg *data)
{
	int		len;

	(void)data;
	len = ft_count_envp(envp);
	*env = malloc(sizeof(char *) * (len + 1));
	if (!*env)
		ft_exit(12, "malloc", data);
	ft_make_array(envp, env, len, data);

	len = -1;

	while ((*env[len]))
	{
		printf("%s\n", *env[len]);
		len++;
	}

}
