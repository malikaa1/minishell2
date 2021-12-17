/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:19:24 by mrahmani          #+#    #+#             */
/*   Updated: 2021/12/15 19:23:13 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
        {
            *quotes_num = *quotes_num + 1;
            i++;
            while (str[i] != '\0' && (str[i] != '\'' || str[i - 1] == '\\'))
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
    ft_delete_backslash(com);
    free(pos_tab);
}

void ft_delete_backslash(char *com)
{
    int i;
    int *pos;
    int j;
    int back_slash_nb;

    i = 0;
    j = 0;
    back_slash_nb = 0;
    while (com[i] != '\0')
    {
        if (com[i] == '\\' && com[i + 1] != '\0' && (com[i + 1] == '\'' || com[i + 1] == '\"' ))
            back_slash_nb++;
        i++;
    }
    pos = malloc(sizeof(int) * (back_slash_nb + 1));
    if (pos != NULL)
    {
        i = 0;
        while (com[i] != '\0')
        {
            if (com[i] == '\\' && com[i + 1] != '\0' && (com[i + 1] == '\'' || com[i + 1] == '\"' ))
            {
                pos[j] = i;
                j++;
            }
            i++;
        }
        pos[j] = '\0';

    	i = back_slash_nb - 1;
	    while (i >= 0)
	    {
		    ft_remove_char(com, pos[i]);
		    i--;
	    }
        free(pos);
    }
}