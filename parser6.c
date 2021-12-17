/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 20:12:20 by mrahmani          #+#    #+#             */
/*   Updated: 2021/12/15 20:12:28 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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
	if (tab == NULL)
		return (NULL);
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