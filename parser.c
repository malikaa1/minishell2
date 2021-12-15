/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 13:20:37 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/15 20:09:50 by mrahmani         ###   ########.fr       */
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

char *find_cmd_path(char *cmd)
{
	char **path_tab;
	int i;
	char *tmp;
	char *tmp2;

	i = 0;
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
