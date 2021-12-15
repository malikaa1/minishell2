/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 20:09:41 by mrahmani          #+#    #+#             */
/*   Updated: 2021/12/15 21:35:29 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int tab_next_index(char **tab)
{
    int i;

    i = 0;
    while (tab[i] != NULL)
        i++;
    return (i);
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
    int char_to_extract;
    int char_to_add;
    char *buff;

    char_to_extract = 0;
    char_to_add = 0;
    str = malloc(sizeof(char *) * (char_numb(com, '$', 0, 0) + 1));
    if (str == NULL)
        return NULL;
    tab_init(str, char_numb(com, '$', 0, 0) + 1);
    getenv_doll(&char_to_extract, com, shell, str);
    char_to_add = caculate_char_to_add(str, com);
    buff = malloc(sizeof(char) * (ft_strlen(com) - char_to_extract + char_to_add + 1));
    if (buff == NULL)
        return NULL;
    dollar_between_quotes(str, com, buff);
    ft_free_tab(str);
    return (buff);
}