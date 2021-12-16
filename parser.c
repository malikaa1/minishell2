/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 13:20:37 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/16 21:29:43 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *getenv_value_from_list(t_shellinfo shell, char *env)
{
	while (shell.env && shell.env->var)
	{
		if (ft_strcompare(shell.env->name, env) == 1)
			return (shell.env->value);
		shell.env = shell.env->next;
	}
	return (ft_strdup(""));
}

char **get_paths()
{
	char *path;
	char **path_tab;

	path = getenv("PATH");
	path_tab = ft_split(path, ':');
	return (path_tab);
}
int is_absolute_path(char *cmd)
{
	if (cmd == NULL)
		return (-1);
	if (cmd[0] == '/')
	{
		return (1);
	}
	return (0);
}

int is_relative_path(char *cmd)
{
	if (cmd == NULL)
		return (-1);
	if ((cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/') || (cmd[0] == '.' && cmd[1] == '/'))
	{
		return (1);
	}
	return (0);
}

char *handle_relative_absolute_path(char *cmd)
{
	char *tmp;
	char *tmp2;

	if (is_absolute_path(cmd))
		return (ft_strdup(cmd));
	if (is_relative_path(cmd))
	{
		tmp = ft_strjoin("/", cmd);
		tmp2 = ft_strjoin(ft_get_pwd(), tmp);
		free(tmp);
		return (tmp2);
	}
	return (NULL);
}

char *find_cmd_path(char *cmd)
{
	char **path_tab;
	int i;
	char *tmp;
	char *tmp2;

	i = 0;
	tmp = handle_relative_absolute_path(cmd);
	if (tmp != NULL)
		return (tmp);
	path_tab = get_paths();
	while (path_tab[i] != NULL)
	{
		tmp2 = ft_strjoin(path_tab[i], "/");
		tmp = ft_strjoin(tmp2, cmd);
		free(tmp2);
		if (access(tmp, F_OK) == 0)
		{
			ft_free_tab(path_tab);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	ft_free_tab(path_tab);
	return (NULL);
}

void ft_remove_char(char *str, int pos)
{
	while (str[pos] != '\0')
	{
		str[pos] = str[pos + 1];
		pos++;
	}
}

void remove_quotes(char *str, int *pos_tab)
{
	int i;

	i = quotes_enum(str) - 1;
	while (i >= 0)
	{
		ft_remove_char(str, pos_tab[i]);
		i--;
	}
}
