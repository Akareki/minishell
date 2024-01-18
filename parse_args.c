/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:12:06 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/18 12:41:02 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf/libft/libft.h"
#include "minishell.h"
#include <stdio.h>

char	*find_cmd(t_wordlst *wordlst, t_shell *shell)
{
	if (wordlst->type >= BUILTIN || ft_strchr(wordlst->word, '/'))
		return (ft_strdup(wordlst->word));
	else
		return (retrieve_absolute_path(shell->envlst, wordlst->word));
	return (NULL);
}

int	args_size(t_wordlst *wordlst)
{
	int			args_size;

	args_size = 0;
	while (wordlst && wordlst->type != PIPE)
	{
		if (wordlst->type == ARG || wordlst->type == CMD
			|| wordlst->type >= BUILTIN)
			args_size++;
		wordlst = wordlst->next;
	}
	return (args_size);
}

int	input_args(t_wordlst *wordlst, t_processlst *process,
				t_shell *shell, int *i)
{
	if (wordlst->type == CMD || wordlst->type >= BUILTIN)
	{
		process->builtin_index = wordlst->type - BUILTIN;
		process->argv[0] = find_cmd(wordlst, shell);
		if (!process->argv[0])
			return (perror("retrieve path"), -1);
	}
	if (wordlst->type == ARG)
	{
		process->argv[*i] = ft_strdup(wordlst->word);
		if (!process->argv[*i])
			return (perror("retrieve path"), -1);
		(*i)++;
	}
	return (0);
}

int	get_args(t_wordlst *wordlst, t_processlst *process, t_shell *shell)
{
	int	i;

	i = 1;
	process->argv = ft_calloc(args_size(wordlst) + 1, sizeof(char *));
	while (wordlst && wordlst->type != PIPE)
	{
		if (input_args(wordlst, process, shell, &i) == -1)
		{
			while (--i >= 0)
				free(process->argv[i]);
			free(process->argv);
			return (-1);
		}
		wordlst = wordlst->next;
	}
	process->argv[i] = NULL;
	return (0);
}
