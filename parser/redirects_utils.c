/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:51:22 by fbeatris          #+#    #+#             */
/*   Updated: 2021/12/26 17:33:43 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_redirect(char *line, int start, int end)
{
	int	len;
	int	i;

	len = end - start;
	i = 0;
	(void)line;
	while (line[end + i])
	{
		line[start + i] = line[end + i];
		i++;
	}
	line[start + i] = '\0';
	while (line[start + i + 1])
	{
		line[start + i + 1] = '\0';
		i++;
	}
}

static char	*save_redir_name(char *line, int *i)
{
	int		begin;
	int		save;
	int		count;
	char	*result;

	save = *i;
	count = 0;
	while (line[*i] && (line[*i] == '>' || line[*i] == '<'))
		(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	begin = *i;
	while (line[*i] && line[*i] != ' ')
		(*i)++;
	result = ft_substr(line, begin, *i - begin);
	remove_redirect(line, save, *i);
	*i = save;
	return (result);
}

void	data_redir_list(t_redir *new, t_arg *data)
{
	t_redir	*temp;
	int		i;

	i = 1;
	temp = data->redir;
	if (data->redir == NULL)
	{
		data->redir = new;
		data->redir->cmd = 1;
	}
	else
	{
		while (data->redir->data_next)
		{
			data->redir = data->redir->data_next;
			i++;
		}
		data->redir->data_next = new;
		data->redir->data_next->cmd = data->num_cmd;
		data->redir = temp;
	}
}

void	new_in_redir(char *line, int *i, t_redir *new)
{
	if (line[*i + 1] && line[*i + 1] != '<')
	{
		new->name = save_redir_name(line, i);
		new->two = 0;
		new->in = 1;
	}
	else if (line[*i + 1] && line[*i + 1] == '<')
	{
		new->limiter = save_redir_name(line, i);
		new->name = ft_strdup("heredoc");
		new->two = 1;
		new->in = 1;
	}
}

t_redir	*new_redir(char *line, int *i, t_arg *data)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (line[*i + 1] && line[*i] == '>' && line[*i + 1] != '>')
	{
		new->name = save_redir_name(line, i);
		new->two = 0;
		new->in = 0;
	}
	else if (line[*i + 1] && line[*i] == '>' && line[*i + 1] == '>')
	{
		new->name = save_redir_name(line, i);
		new->two = 1;
		new->in = 0;
	}
	else if (line[*i] && line[*i] == '<')
		new_in_redir(line, i, new);
	new->next = NULL;
	new->data_next = NULL;
	data_redir_list(new, data);
	return (new);
}
