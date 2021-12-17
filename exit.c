/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:59:29 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/17 15:03:27 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_status(t_shellinfo shell, char *s)
{
	int i;
	int stat;

	i = 0;
	stat = 0;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 0)
		{
			printf("exit\n");
			printf("exit: %s:  numeric argument required\n", s);
			ft_exit(shell, g_shell_status);
		}
		i++;
	}
	stat = ft_atoi(s);
	return (stat);
}

void exit_minishell(char **arg, t_shellinfo shell)
{
	int stat;

	stat = 0;
	if (arg[1] == NULL)
	{
		printf("exit\n");
		ft_exit(shell, g_shell_status);
	}
	else if (arg[2] != NULL)
	{
		printf("exit\n");
		printf("exit: too many arguments\n");
		ft_exit(shell, g_shell_status);
	}
	else
	{
		stat = get_status(shell, arg[1]);
		printf("exit\n");
		ft_exit(shell, stat);
	}
}

void ft_exit(t_shellinfo shell, int stat)
{
	free_env_list(shell.env);
	exit(stat);
}
