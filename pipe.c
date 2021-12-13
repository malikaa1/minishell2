/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:09:57 by ybesbes           #+#    #+#             */
/*   Updated: 2021/10/31 17:13:59 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_envsize(t_env *env)
{
	int i;

	i = 0;
	while (env && env->var)
	{
		i++;
		env = env->next;
	}
	return i;
}

char **convert_list_to_tab(t_env *env)
{
	char **tab;
	int tablen;
	int i;

	i = 0;
	tablen = ft_envsize(env);
	tab = malloc(sizeof(char *) * (tablen + 1));
	while (env && env->var)
	{
		tab[i] = env->var;
		i++;
		env = env->next;
	}
	tab[i] = NULL;
	return (tab);
}

void is_double_quotes(t_command com, int *i, int *j, char **tab)
{
	int tmp;

	tmp = *i;
	*i += 1;
	while (com.args[*i] != '\0' && (com.args[*i] != '\"' || com.args[*i - 1] == '\\'))
		*i += 1;
	tab[*j] = ft_substr(com.args, tmp, *i - tmp + 1);
	*j += 1;
	*i += 1;
}

void is_single_quotes(t_command com, int *i, int *j, char **tab)
{
	int tmp;

	tmp = *i;
	*i += 1;
	while (com.args[*i] != '\0' && com.args[*i] != '\'')
		*i += 1;
	tab[*j] = ft_substr(com.args, tmp, *i - tmp + 1);
	*j += 1;
	*i += 1;
}

void is_char(t_command com, int *i, int *j, char **tab)
{
	int tmp;

	tmp = *i;
	while ((ft_isspace(com.args[*i]) == 0 && com.args[*i] != '\0') || is_it_between_quotes(com.args, *i) == 1)
		*i += 1;
	tab[*j] = ft_substr(com.args, tmp, *i - tmp);
	*j += 1;
}

char **create_tab(t_command com, t_shellinfo shell)
{
	char **tab;
	int i;
	int j;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (space_calcul(com.args) + 2));
	while (com.args[i] != '\0')
	{
		if (com.args[i] == '\"' && (i == 0 || com.args[i - 1] != '\\')) // si double cote
			is_double_quotes(com, &i, &j, tab);
		else if (com.args[i] == '\'') // si cote
			is_single_quotes(com, &i, &j, tab);
	
		else if (ft_isspace(com.args[i]) == 0) // si caractere
			is_char(com, &i, &j, tab);
		else
			i++;
	}
	tab[j] = NULL;
	substitute_and_delete(shell, tab);
	return (tab);
}

int execute_cmd(t_command com, t_shellinfo shell)
{
	char **arg;
	int ret;

	ret = 0;
	ret = check_for_files(com);
	arg = create_tab(com, shell);
	if (ft_strcompare(arg[0], "pwd") == 1)
		ret = ft_pwd();
	else if (ft_strcompare(arg[0], "cd") == 1)
		ret = ft_cd(arg);
	else if (ft_strcompare(arg[0], "echo") == 1)
		ret = ft_echo(arg);
	else if (ft_strcompare(arg[0], "env") == 1)
		ret = ft_env(shell.env);
	else if (ft_strcompare(arg[0], "export") == 1)
		ret = ft_export(shell.env, arg);
	else if (ft_strcompare(arg[0], "unset") == 1)
		ret = ft_unset(&shell.env, arg);
	else
		ret = find_and_execute(shell, arg);
	ft_free_tab(arg);
	return ret;
}

void pipe_cmd(t_command com, t_shellinfo shell)
{
	int new_pipe[2];
	pid_t cpid;

	ft_memset(new_pipe, 0x00, sizeof(new_pipe));
	if (shell.coming)
		pipe(new_pipe);
	cpid = fork();
	if (cpid == 0) // child
		case_of_0_cpid(com, shell, new_pipe);
	else if (cpid > 0) // parent
		case_of_positive_cpid(shell, new_pipe);
	else
	{
		perror("creating fork failed");
		g_shell_status = -1;
	}
	waitpid(cpid, &g_shell_status, 0);
}