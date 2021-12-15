/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:46:19 by ybesbes           #+#    #+#             */
/*   Updated: 2021/10/31 16:22:58 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_word(char *command, int *i)
{
	int tmp;

	while (ft_isspace(command[*i]) == 1)
		*i = *i + 1;
	tmp = *i;
	while (ft_isspace(command[*i]) == 0 && command[*i] != '\0')
		*i = *i + 1;
	return (ft_substr(command, tmp, *i - tmp));
}

void parse_single_input_redirect(char *command, int *position, t_command *com_struct)
{
	if (command[*position] == '<' && command[(*position) + 1] != '<')
	{
		*position += 1;
		com_struct->inputfiles[tab_next_index(com_struct->inputfiles)] = get_word(command, position);
	}
}

void parse_double_input_redirect(char *command, int *position, t_command *com_struct)
{
	if (command[*position] == '<' && command[(*position) + 1] == '<')
	{
		*position += 2;
		com_struct->read_from_shell[tab_next_index(com_struct->read_from_shell)] = get_word(command, position);
	}
}

void parse_single_output_redirect(char *command, int *position, t_command *com_struct)
{
	if (command[*position] == '>' && command[(*position) + 1] != '>')
	{
		*position += 1;
		com_struct->outputfiles[tab_next_index(com_struct->outputfiles)] = get_word(command, position);
	}
}

void parse_double_output_redirect(char *command, int *position, t_command *com_struct)
{
	if (command[*position] == '>' && command[(*position) + 1] == '>')
	{
		*position += 2;
		com_struct->output_files_append[tab_next_index(com_struct->output_files_append)] = get_word(command, position);
	}
}

void parse_cmd(char *command, t_command *com_struct)
{
	int i;
	int offset;

	i = 0;
	offset = 0;
	com_struct->args = malloc(sizeof(char *) * (ft_strlen(command) + 1));
	while (command[i] != '\0')
	{
		parse_single_input_redirect(command, &i, com_struct);
		parse_double_input_redirect(command, &i, com_struct);
		parse_single_output_redirect(command, &i, com_struct);
		parse_double_output_redirect(command, &i, com_struct);

		com_struct->args[offset++] = command[i];
		i++;
	}
	com_struct->args[offset] = '\0';
	if (ft_strchr(com_struct->args, ' ') && ft_strchr(com_struct->args, ' ') - com_struct->args > 0)
		com_struct->com = ft_substr(com_struct->args, 0, ft_strchr(com_struct->args, ' ') - com_struct->args);
	if (com_struct->com == NULL)
		com_struct->com = ft_strdup(com_struct->args);
}

void init_command(char *command, t_command *com_struct)
{
	com_struct->out_file_app_num = char_numb(command, '>', 1, 1);
	com_struct->out_file_num = char_numb(command, '>', 0, 1);
	com_struct->in_file_num = char_numb(command, '<', 0, 1);
	com_struct->expected_words_num = char_numb(command, '<', 1, 1);
}

void init_inputfile_param(t_command *com_struct)
{
	if (com_struct->in_file_num == 0)
		com_struct->inputfiles = NULL;
	else
	{
		com_struct->inputfiles = malloc(sizeof(char *) * (com_struct->in_file_num + 1));
		tab_init(com_struct->inputfiles, com_struct->in_file_num + 1);
	}
}

void init_outputfile_param(t_command *com_struct)
{
	if (com_struct->out_file_num == 0)
		com_struct->outputfiles = NULL;
	else
	{
		com_struct->outputfiles = malloc(sizeof(char *) * (com_struct->out_file_num + 1));
		tab_init(com_struct->outputfiles, com_struct->out_file_num + 1);
	}
}



void cmd_init(char *command, t_command *com_struct)
{
	init_command(command, com_struct);
	init_inputfile_param(com_struct);
	init_outputfile_param(com_struct);
	if (com_struct->expected_words_num == 0)
		com_struct->read_from_shell = NULL;
	else
	{
		com_struct->read_from_shell = malloc(sizeof(char *) * (com_struct->expected_words_num + 1));
		tab_init(com_struct->read_from_shell, com_struct->expected_words_num + 1);
	}
	if (com_struct->out_file_app_num == 0)
		com_struct->output_files_append = NULL;
	else
	{
		com_struct->output_files_append = malloc(sizeof(char *) * (com_struct->out_file_app_num + 1));
		tab_init(com_struct->output_files_append, com_struct->out_file_app_num + 1);
	}
	com_struct->com = NULL;
	com_struct->args = NULL;
}

t_command get_cmd(char *command)
{
	t_command com_struct;
	char *com_trim;

	cmd_init(command, &com_struct);
	com_trim = ft_strtrim(command, " \t\r\f\v\n");
	parse_cmd(com_trim, &com_struct);
	free(com_trim);
	return com_struct;
}

void ft_skip_quotes(char *str, int *i, int skip_double_q)
{
	if (skip_double_q == 1)
	{
		if (str[*i] == '\"' && (*i == 0 || str[*i - 1] != '\\'))
		{
			*i = *i + 1;
			while ((str[*i] != '\"' || str[*i - 1] == '\\') && str[*i] != '\0')
				*i = *i + 1;
			;
		}
	}
	if (str[*i] == '\'')
	{
		*i = *i + 1;
		while (str[*i] != '\'' && str[*i] != '\0')
			*i = *i + 1;
	}
}

int char_numb(char *str, char c, int two, int skip_double_q)
{
	int i;
	int r;
	int rd;

	r = 0;
	rd = 0;
	i = 0;
	while (i < (int)ft_strlen(str))
	{
		ft_skip_quotes(str, &i, skip_double_q);
		if (str[i] == c)
		{
			if (str[i + 1] != c)
				r++;
			else
			{
				rd++;
				i++;
			}
		}
		i++;
	}
	if (two == 0)
		return (r);
	return (rd);
}

int space_calcul(char *str)
{
	int i;
	int r;

	r = 0;
	i = 0;
	while (str[i] != '\0')
	{
		ft_skip_quotes(str, &i, 1);
		if (str[i] == ' ')
		{
			r++;
			i++;
			while (str[i] == ' ')
				i++;
		}
		else
			i++;
	}
	return (r);
}

char **read_from_input(char *str)
{
	int input_double_num;
	char **input_double;
	char *tmp;
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	input_double_num = char_numb(str, '<', 1, 1);
	input_double = malloc(sizeof(char **) * input_double_num + 1);
	if (input_double == NULL)
		return (NULL);
	tmp = NULL;
	input_double[input_double_num] = 0;
	while (str[i] != '\0' && k < input_double_num)
	{
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '\0')
		{
			tmp = malloc(sizeof(char *) * ft_strlen(str - 2));
			if (tmp == NULL)
			{
				free(input_double);
				return NULL;
			}
			j = 0;
			i = i + 2;
			while (str[i] == ' ')
				i++;
			while (str[i] != ' ' && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != '\0')
				tmp[j++] = str[i++];
			tmp[j] = '\0';
			input_double[k++] = tmp;
		}
		else
			i++;
	}
	return (input_double);
}