/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:29:28 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/02 11:29:35 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void    substitute_and_delete(t_shellinfo shell,char **tab)
{
	char *c_tmp;
    int i;

    i = 0;
	while (tab[i] != NULL)
	{
		c_tmp = substitute_env_var(shell, tab[i]);
		if (tab[i] != NULL)
			free(tab[i]);
		tab[i] = c_tmp;
		ft_delete_quotes(tab[i]);
		i++;
	}
}

void case_of_0_cpid(t_command com, t_shellinfo shell, int new_pipe[])
{
    ft_read_from_shell(com, 1);
    if (ft_infile(com, 1) < 0)
        exit(EXIT_FAILURE);
    if(com.in_file_num > 0)
        shell.previous = 1;
    if (shell.previous) // if there is a previous command
    {
        dup2(*shell.old_pipe[0], 0);
        close(*shell.old_pipe[0]);
        close(*shell.old_pipe[1]);
    }
    if (ft_outfile(com, 1) < 0 || ft_outfile_append(com, 1) < 0)
        exit(EXIT_FAILURE);
    if (shell.coming && com.out_file_num == 0 && com.out_file_app_num == 0) // if there is a coming command
    {
        close(new_pipe[0]);
        dup2(new_pipe[1], 1);
        close(new_pipe[1]);
    }
    if(shell.execute && ft_strlen(com.com) > 0)
        exit(execute_cmd(com, shell));
    exit(EXIT_SUCCESS);
}

	
void case_of_positive_cpid(pid_t cpid, t_shellinfo shell, int new_pipe[])
{
    if (shell.previous) // previous command
    {
        close(*shell.old_pipe[0]);
        close(*shell.old_pipe[1]);
    }
	waitpid(cpid, &g_shell_status, 0);
    if (shell.coming) // comming command
    {
        *shell.old_pipe[0] = new_pipe[0];
        *shell.old_pipe[1] = new_pipe[1];
    }
}

int    check_for_files(t_command com)
{
    if(is_a_real_builtin(com.com) == 1)
    {
        ft_read_from_shell(com, 0);
        if (ft_infile(com, 0) < 0 || ft_outfile(com, 0) < 0 || ft_outfile_append(com, 0) < 0)
            return (1);
    }
    return (-1);
}

int find_and_execute(t_shellinfo shell, char **arg)
{
	char *full_cmd;
    int ret;
    char **tab;

	ret = 0;
    full_cmd = find_cmd_path(shell, arg[0]);
    if (full_cmd != NULL)
    {
        arg[0] = full_cmd;
        tab = convert_list_to_tab(shell.env);
        ret = execve(arg[0], arg, tab); 
    }
    else
    {
        if ( arg[0][0] == '?')
        {
            if (g_shell_status == 130)
                printf("minishell: command not found : %d%s\n", g_shell_status, arg[0] + 1);
            else
                printf("minishell: command not found : %d%s\n", WEXITSTATUS(g_shell_status), arg[0] + 1);
        }
        else
            printf("minishell: command not found : %s\n", arg[0]);
        ret = 127;
    }
    return (ret);
}