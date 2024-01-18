/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:24:37 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/18 12:12:59 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	void_event(void)
{
	return (0);
}

void	main_sig_int_handler(int sig)
{
	(void)sig;
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	exec_sig_int_handler(int sig)
{
	g_last_sig = sig;
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)", 2);
	write(0, "\n", 1);
}

void	heredoc_sig_int_handler(int sig)
{
	g_last_sig = sig;
	rl_done = 1;
}
