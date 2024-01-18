/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:13:19 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/18 12:14:19 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	clean_wordlst(t_wordlst **wordlst)
{
	t_wordlst	*word_elem;
	t_wordlst	*next_word_elem;

	word_elem = *wordlst;
	while (word_elem)
	{
		free(word_elem->word);
		next_word_elem = word_elem->next;
		free(word_elem);
		word_elem = next_word_elem;
	}
	*wordlst = NULL;
}

int	clean_processlst(t_processlst **processlst, t_shell *shell)
{
	int				i;
	t_processlst	*process;
	t_processlst	*next_process;
	int				status;

	process = *processlst;
	status = shell->last_status;
	while (process)
	{
		i = 0;
		status = process->status;
		while (process->argv[i])
			free(process->argv[i++]);
		free(process->argv);
		if (process->fd_in != 0 && process->fd_in != -1)
			close(process->fd_in);
		if (process->fd_out != 1 && process->fd_out != -1)
			close(process->fd_out);
		next_process = process->next;
		free(process);
		process = next_process;
	}
	*processlst = NULL;
	return (status);
}

int	clean_shell(t_shell *shell)
{
	char	*pwd;
	char	*tmp_str;

	clean_wordlst(&shell->wordlst);
	shell->last_status = clean_processlst(&shell->processlst, shell);
	if (g_last_sig == SIGINT || g_last_sig == SIGQUIT)
	{
		shell->last_status = 130 * (g_last_sig == SIGINT)
			+ 131 * (g_last_sig == SIGQUIT);
		g_last_sig = 0;
	}
	free_envarray(shell->envarray);
	shell->envarray = NULL;
	free(shell->line);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);
	tmp_str = ft_strjoin(pwd, "$ ");
	if (!tmp_str)
		return (perror("minishell"), free(pwd), -1);
	free(shell->prompt);
	shell->prompt = tmp_str;
	free(pwd);
	return (0);
}

void	free_envarray(char **envarray)
{
	int	i;

	i = 0;
	if (!envarray)
		return ;
	while (envarray[i])
		free(envarray[i++]);
	free(envarray);
}

void	exit_failed_fork(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	exit(1);
}
