/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:46:30 by ybesbes           #+#    #+#             */
/*   Updated: 2021/10/31 17:04:34 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	executer(t_command com_struct, t_shellinfo shell, int i, char **commands)
{
	int ret;

	ret = 0;
	if(is_a_real_builtin(com_struct.com) == 0)
	{
		shell.execute = 1;
		pipe_cmd(com_struct, shell);
	}
	else if (i == 0 && commands[i + 1] == NULL)
	{
		if (execute_cmd(com_struct, shell) < 0)
			ret = -1;
	}
	else
	{
		shell.execute = 0;
		pipe_cmd(com_struct, shell);
	}
	return (ret);
}

char	*read_check_and_trim(t_shellinfo shell)
{
	char *str;
	char *tmp;

	str = readline("minishell->");
	add_history(str);
	if (str == NULL)
	{
		printf("\n");
		ft_exit(shell, 0);// ctrl_d
	}
	tmp = ft_strtrim(str, " \t\r\f\v\n");
	free(str);
	if (ft_strcompare(tmp, "exit") == 1) 
	{
		free(tmp);
		ft_exit(shell, 0);
	}
	if (check_syntax_errors(tmp) == 1)
	{
		printf("error : syntax_error\n");
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}

void	old_pipe_set(t_shellinfo *shell)
{
	shell->old_pipe[0] = malloc(sizeof(int));
	if (shell->old_pipe[0] == NULL)
		ft_exit(*shell, 0);
	shell->old_pipe[1] = malloc(sizeof(int));
	if (shell->old_pipe[1] == NULL)
		ft_exit(*shell, 0);
	shell->previous = 0;
}

void	minishell_loop(char **env)
{
	char **commands;
	t_shellinfo shell;
	char *tmp;
	t_command com_struct;
	int i;

	shell.env = NULL;
	init_env(&shell.env, env);
	while (1)
	{
		i = 0;
		tmp = read_check_and_trim(shell);
		if (tmp == NULL)
			continue ;
		commands = ft_mini_split(tmp, '|');
		free(tmp);
		old_pipe_set(&shell);
		while (commands && commands[i] != NULL)
		{
			shell.coming = (commands[i + 1] == NULL) ? 0 : 1;
			com_struct = get_cmd(commands[i]);
			if (executer(com_struct, shell, i, commands) == -1)
			{
				ft_free_cmd(&com_struct);
				break;
			}
			i++;
			shell.previous = 1;
			ft_free_cmd(&com_struct);
			if (g_shell_status != 0)
				break ;
		}
		ft_free_tab(commands);
		ft_free_old_pipe(shell);
	}
}

int main(int ac, char **av, char **env)
{
	if (ac > 1)
	{
		printf("ERROR :this program doesn't work with arguments\n");
		exit(EXIT_FAILURE);
	}
	av[1] = NULL;
	g_shell_status = 0;
	handle_ctrl_c();
	handle_ctrl_backslash();
	minishell_loop(env);
	return (g_shell_status);
}
