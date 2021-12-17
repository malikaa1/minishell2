/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 22:15:38 by mrahmani          #+#    #+#             */
/*   Updated: 2021/12/17 12:55:41 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *str)
{
	if (ft_strcompare(str, "cd") == 1)
		return (1);
	if (ft_strcompare(str, "pwd") == 1)
		return (1);
	if (ft_strcompare(str, "export") == 1)
		return (1);
	if (ft_strcompare(str, "env") == 1)
		return (1);
	if (ft_strcompare(str, "echo") == 1)
		return (1);
	if (ft_strcompare(str, "unset") == 1)
		return (1);
	return (0);
}

int is_a_real_builtin(char *str)
{
	if (ft_strcompare(str, "cd") == 1)
		return (1);
	if (ft_strcompare(str, "export") == 1)
		return (1);
	if (ft_strcompare(str, "unset") == 1)
		return (1);
	if (ft_strcompare(str, "exit") == 1)
		return (1);
	return (0);
}

int ft_strcompare(char *str1, char *str2)
{
	if (ft_strncmp(str1, str2, ft_strlen(str1)) == 0 && ft_strlen(str1) == ft_strlen(str2))
		return (1);
	return (0);
}