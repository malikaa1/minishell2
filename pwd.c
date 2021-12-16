/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:40:43 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/16 21:01:00 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *ft_get_pwd(void)
{
	char *str;
	char buf[1000];

	str = getcwd(buf, 1000);
	return (str);
}

int ft_pwd(void)
{
	char *str;
	char buf[1000];

	str = getcwd(buf, 1000);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	return (1);
}
