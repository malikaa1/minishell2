/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 13:20:37 by ybesbes           #+#    #+#             */
/*   Updated: 2021/10/26 21:35:00 by mrahmani         ###   ########.fr       */
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
	return ft_strdup("");
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

void sum_quotes(int *quotes_num, int *double_quotes_num, char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
		{
			*double_quotes_num = *double_quotes_num + 1;
			i++;
			while (str[i] != '\0' && (str[i] != '\"' || str[i - 1] == '\\'))
				i++;
			*double_quotes_num = *double_quotes_num + 1;
		}
		if (str[i] == '\'')
		{
			*quotes_num = *quotes_num + 1;
			i++;
			while (str[i] != '\0' && str[i] != '\'')
				i++;
			*quotes_num = *quotes_num + 1;
		}
		i++;
	}
}
int quotes_enum(char *str)
{
	int quotes_num;
	int double_quotes_num;

	double_quotes_num = 0;
	quotes_num = 0;
	sum_quotes(&quotes_num, &double_quotes_num, str);
	return (quotes_num + double_quotes_num);
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

void check_double_quotes(char *com, int *pos_tab, int *i, int *j)
{
	pos_tab[*j] = *i;
	*j += 1;
	*i += 1;
	while (com[*i] != '\0' && (com[*i] != '\"' || com[*i - 1] == '\\'))
		*i += 1;
	pos_tab[*j] = *i;
	*j += 1;
}

void check_single_quotes(char *com, int *pos_tab, int *i, int *j)
{
	pos_tab[*j] = *i;
	*j += 1;
	*i += 1;
	while (com[*i] != '\0' && com[*i] != '\'')
		*i += 1;
	pos_tab[*j] = *i;
	*j += 1;
}

void ft_delete_quotes(char *com)
{
	int i;
	int *pos_tab;
	int j;

	i = 0;
	j = 0;
	pos_tab = malloc(sizeof(int) * (quotes_enum(com) + 1));
	while (com[i] != '\0')
	{
		if (com[i] == '\"' && (i == 0 || com[i - 1] != '\\'))
		{
			check_double_quotes(com, pos_tab, &i, &j);
		}
		if (com[i] == '\'')
		{
			check_single_quotes(com, pos_tab, &i, &j);
		}
		i++;
	}
	pos_tab[j] = '\0';
	remove_quotes(com, pos_tab);
	free(pos_tab);
}

int is_it_between_simple_quotes(char *str, int pos)
{

	int i;
	int result;

	i = 0;
	result = 0;
	while (i < pos)
	{
		if (str[i] == '\'')
			result++;
		i++;
	}
	if (result % 2 != 0)
		return (1);
	return (0);
}

int is_it_between_quotes(char *str, int pos)
{
	int i;
	int result;
	int result1;

	i = 0;
	result = 0;
	result1 = 0;
	while (i < pos)
	{
		if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
		{
			result1++;
			while ((str[i] != '\"' || str[i - 1] == '\\') && str[i] != '\0')
				i++;
		}
		if (str[i] == '\'')
			result++;
		i++;
	}
	if (result % 2 != 0 || result1 % 2 != 0)
		return (1);
	return (0);
}

int caculate_char_to_add(char **str, char *com)
{
	int i;
	int char_to_add;

	i = 0;
	char_to_add = 0;
	while (i < char_numb(com, '$', 0, 0))
	{
		if (str[i] != NULL)
			char_to_add = char_to_add + ft_strlen(str[i]);
		i++;
	}
	return (char_to_add);
}

void tab_init(char **str, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		str[i] = NULL;
		i++;
	}
}

void getenv_doll(int *char_to_extract, char *com, t_shellinfo shell, char **str)
{
	char *env;
	int j;
	unsigned int i;
	int tmp;

	j = 0;
	i = 0;
	while (i < ft_strlen(com))
	{
		if (com[i] == '$')
		{
			i++;
			tmp = i;
			while (ft_isalnum(com[i]) == 1)
				i++;
			env = ft_substr(com, tmp, i - tmp);
			*char_to_extract = *char_to_extract + ft_strlen(env) + 1;
			str[j] = getenv_value_from_list(shell, env);
			free(env);
			j++;
		}
		i++;
	}
}

char *substitute_env_var(t_shellinfo shell, char *com)
{
	char **str;
	char *doll;
	int char_to_extract;
	int char_to_add;

	char_to_extract = 0;
	char_to_add = 0;
	str = malloc(sizeof(char *) * (char_numb(com, '$', 0, 0) + 1));
	if (str == NULL)
		return NULL;
	tab_init(str, char_numb(com, '$', 0, 0) + 1);
	getenv_doll(&char_to_extract, com, shell, str);
	char_to_add = caculate_char_to_add(str, com);
	doll = dollar_between_quotes(str, com, char_to_extract, char_to_add);
	ft_free_tab(str);
	return (doll);
}
