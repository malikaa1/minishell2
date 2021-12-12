/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:33:55 by ybesbes           #+#    #+#             */
/*   Updated: 2021/09/27 15:33:59 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quotes(char *str, int *index, int *single_quotes, int *double_quotes)
{
	while (str != NULL && str[*index] != '\0')
	{
		if (str[*index] == '\"' && (*index == 0 || str[*index - 1] != '\\'))
		{
			*double_quotes += 1;
			*index += 1;
			while (str[*index] != '\0' && (str[*index] != '\"' || str[*index - 1] == '\\'))
				*index += 1;
			if (str[*index] == '\0')
				return (1);
			*double_quotes += 1;
		}
		if (str[*index] == '\'')
		{
			*single_quotes += 1;
			*index += 1;
			while (str[*index] != '\0' && str[*index] != '\'')
				*index += 1;
			if (str[*index] == '\0')
				return (1);
			*single_quotes += 1;
		}
		*index += 1;
	}
	return (0);
}

int check_inclosed_quotes(char *str)
{
	int i;
	int quotes_num;
	int double_quotes_num;

	i = 0;
	double_quotes_num = 0;
	quotes_num = 0;
	if (check_quotes(str, &i, &quotes_num, &double_quotes_num) == 1)
		return (1);
	if (quotes_num % 2 != 0 || double_quotes_num % 2 != 0)
		return (1);
	return (0);
}

int check_syntax_errors(char *str)
{
	int i;

	i = ft_strlen(str);
	if (check_inclosed_quotes(str) == 1)
		return (1);
	if (str != NULL && str[0] == '|')
		return (1);
	if (str != NULL && (str[i - 1] == '|' || str[i - 1] == '<' || str[i - 1] == '>'))
		return (1);
	return (0);
}

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
	return (0);
}

int ft_strcompare(char *str1, char *str2)
{
	if (ft_strncmp(str1, str2, ft_strlen(str1)) == 0 && ft_strlen(str1) == ft_strlen(str2))
		return (1);
	return (0);
}
