/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:33:55 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/16 15:54:52 by mrahmani         ###   ########.fr       */
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
		if (str[*index] == '\'' && (*index == 0 || str[*index - 1] != '\\'))
		{
			*single_quotes += 1;
			*index += 1;
			while (str[*index] != '\0' && (str[*index] != '\''|| str[*index - 1] == '\\'))
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

char *read_check_and_trim(t_shellinfo shell)
{
	char *str;
	char *tmp;
	int	i;
	int start;

	str = readline("minishell->");
	add_history(str);
	if (str == NULL)
	{
		printf("\n");
		ft_exit(shell, 0); // ctrl_d
	}
	tmp = ft_strtrim(str, " \t\r\f\v\n");
	free(str);
	if (ft_strncmp(tmp, "exit", 4) == 0)
	{
		if (ft_strcompare(tmp, "exit") == 0)
		{
			i = 4;
			while (ft_isspace(tmp[i]) == 1)
				i++;
			start = i;
			while (ft_isspace(tmp[i]) == 0)
				i++;
			str =  ft_substr(tmp, start, i - start);
			i = 0;
			while (str[i] != '\0')
			{
				if (str[i] < '0' || str[i] >'9')
					break ;
				i++;
			}
			if (i != (int)ft_strlen(str))
			{
				printf("exit\n");
				printf("minishell: exit: %s: numeric argument required\n", str);
				free(str);
				free(tmp);
				ft_exit(shell, 1);

			}
			else if (ft_atoi(str) != 0)
				printf("\n");
			else
				printf("exit\n");
			free(tmp);
			free(str);
			ft_exit(shell, 0);
		}
		else
		{
			printf("exit\n");
			free(tmp);
			ft_exit(shell, 0);
		}
	}
	if (check_syntax_errors(tmp) == 1)
	{
		printf("error : syntax_error\n");
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}
