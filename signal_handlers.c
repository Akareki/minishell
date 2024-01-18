/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:03:34 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/18 11:24:28 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf/libft/libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

int	main_signal_handlers(void)
{
	struct sigaction	action;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	ft_bzero(&action, sizeof(action));
	action.sa_handler = main_sig_int_handler;
	action.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &action, NULL))
		return (-1);
	return (0);
}

int	heredoc_signal_handler(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = heredoc_sig_int_handler;
	action.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &action, NULL))
		return (-1);
	return (0);
}

void	fork_signal_handler(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
}

void	exec_signal_handler(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = exec_sig_int_handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
