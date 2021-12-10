/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 21:03:47 by mrahmani          #+#    #+#             */
/*   Updated: 2021/11/30 22:20:19 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_shell_status;

void ctrl_c_handler(int sig, siginfo_t *info, void *context)
{
    (void) info;
    (void) context;
    printf("\n");
    if (sig == SIGINT)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        g_shell_status = 130;
    }
}

void handle_ctrl_c()
{
    struct sigaction sa;

    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = ctrl_c_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa, NULL);
}

void ctrl_backslash_handler(int sig, siginfo_t *info, void *context)
{
    (void) context;
    (void) sig;
    if (info->si_pid == 0)
    {
        printf("Quit\n");
    }
    else
        printf("\b\b  \b\b");
}

void handle_ctrl_backslash()
{
    struct sigaction sa;

    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = ctrl_backslash_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGQUIT, &sa, NULL);
}