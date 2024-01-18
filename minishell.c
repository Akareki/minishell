/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 08:36:36 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/18 12:05:52 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_sig;

char	**init_builtins(void)
{
	static char	*builtins[8];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	return (builtins);
}

int	init_shell(t_shell *shell, char **env)
{
	char	*pwd;
	char	*tmp_str;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (-1);
	shell->envlst = env_lst_copy(env);
	if (!shell->envlst)
	{
		tmp_str = ft_strjoin("PWD=", pwd);
		if (!tmp_str || env_set_value(&shell->envlst, tmp_str) == -1)
			return (free(pwd), free(tmp_str), -1);
	}
	tmp_str = ft_strjoin(pwd, "$ ");
	if (!tmp_str)
		return (free(pwd), -1);
	shell->prompt = tmp_str;
	free(pwd);
	shell->builtins = init_builtins();
	return (0);
}

void	print_processlst(t_processlst *processlst)
{
	int	i;

	while (processlst)
	{
		i = 0;
		while (processlst->argv[i])
		{
			printf("%s ", processlst->argv[i]);
			i++;
		}
		printf("\n");
		printf("fd_in : %d\n", processlst->fd_in);
		printf("fd_out : %d\n", processlst->fd_out);
		printf("builtin_index : %d\n", processlst->builtin_index);
		processlst = processlst->next;
	}
}

int	minishell_loop(t_shell *shell)
{
	while (1)
	{
		if (clean_shell(shell) == -1)
			bi_exit(shell, NULL, 0, 1);
		shell->line = readline(shell->prompt);
		if (!shell->line)
			bi_exit(shell, NULL, 0, 1);
		add_history(shell->line);
		if (check_error(shell->line)
			|| parse_words(shell->line, &shell->wordlst)
			|| expand_words(shell->wordlst, shell->envlst, shell->last_status)
			|| parse_cmd(shell))
		{
			shell->last_status = 2;
			if (g_last_sig == SIGINT)
			{
				g_last_sig = 0;
				shell->last_status = 130;
			}
			continue ;
		}
		exec_signal_handler();
		exec_processlst(shell);
		main_signal_handlers();
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	rl_event_hook = void_event;
	if (main_signal_handlers() == -1)
		return (perror("minishell"), 1);
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (perror("minishell"), 1);
	if (init_shell(shell, env) == -1)
		return (1);
	return (minishell_loop(shell));
}
