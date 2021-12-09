/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:55:52 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/09 16:27:59 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*key;
	char			*separator;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	char			*name;
	char			*limiter;
	int				cmd;
	int				in;
	int				two;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				**cmd;
	t_redir				*in;
	t_redir				*out;
	struct s_command	*next;
}	t_command;

typedef struct s_arg
{
	t_command	*cmd;
	t_redir		*redir;
	t_env		*envp;
	char		*env;
	int			num;// count cmd
	int			**fd;
	int			errnum;
}	t_arg;

int		parser(t_arg *data, char *line);
char	*parse_line(char *line_const, t_arg *data);
int		check_syntax(char *line);
char	*env_replace(char *line, int *i, t_env *envp);
char	*single_quotes(char *line, int *i);
char	*double_quotes(char *line, int *i, t_env *envp);
char	*parse_redirects(char *line, int *i, t_arg *data);

void	parse_env(char **envp, t_arg *data);
t_env	*env_create_new(char *key, char *sep, char *value);
void	env_add_new(char *env_line, t_env **first);

void	ft_init_structs(t_arg **data);

int		ft_echo(t_arg *data);// echo with option -n
int		ft_pwd(t_arg *data);// pwd with no options
int		ft_cd(t_arg *data); //cd with only a relative or absolute path
int		ft_env(t_arg *data);// env with no options or arguments
int		ft_unset(t_command *cmd, t_arg *data);// unset with no options
int		ft_export(t_arg *data);//export with no options
void	ft_expor_unset_error(t_arg *data, char *str, char *namecmd);
void	ft_exit(int errnum, char *msg, t_arg *data); //exit with no options


#endif
