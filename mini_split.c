/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:55:01 by ybesbes           #+#    #+#             */
/*   Updated: 2021/10/18 11:55:06 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_mini_count(char *s, char c)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	while (s[i])
	{
		ft_skip_quotes(s, &i, 1);
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

int		ft_mini_wordlen(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_skip_quotes(s, &i, 1);
		if (s[i] == c )
			break ;
		i++;

	}
	return (i);
}

void		*mini_leak(char **ptr, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

 char		**mini_fill(char  *s, int words, char c, char **ptr)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	while (++i < words)
	{
		while (*s == c)
			s++;
		len = ft_mini_wordlen(s, c);
		if (!(ptr[i] = (char *)malloc(sizeof(char) * (len + 1))))
			return (mini_leak(ptr, i));
		j = 0;
		while (j < len)
			ptr[i][j++] = *s++;
		ptr[i][j] = '\0';
	}
	ptr[i] = NULL;
	return (ptr);
}

char			**ft_mini_split(char *s, char c)
{
	char	**ptr;
	int		words;

	if (!s)
		return (NULL);
	words = ft_mini_count(s, c);
	if (!(ptr = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	ptr = mini_fill(s, words, c, ptr);
	return (ptr);
}