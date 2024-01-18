/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:07:55 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/18 10:17:46 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	clean_envlst(t_envlst **envlst)
{
	t_envlst	*temp;
	t_envlst	*curr;

	if (!envlst || !*envlst)
		return ;
	curr = *envlst;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp->value);
		free(temp->key);
		free(temp);
	}
	*envlst = NULL;
}

int	free_shell(t_shell *shell_to_free)
{
	int	ret;

	ret = clean_processlst(&shell_to_free->processlst, shell_to_free);
	clean_wordlst(&shell_to_free->wordlst);
	clean_envlst(&shell_to_free->envlst);
	free_envarray(shell_to_free->envarray);
	free(shell_to_free->line);
	free(shell_to_free->prompt);
	free(shell_to_free);
	return (ret);
}

void	check_digits(char **args, t_shell *shell_to_free, int fd_out)
{
	size_t	i;

	i = 0;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			free_shell(shell_to_free);
			ft_putstr_fd("exit\n", fd_out);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(2);
		}
		i++;
	}
}

int	bi_exit(t_shell *shell_to_free, char **args, int fd_in, int fd_out)
{
	int	number;

	if (fd_in == 0 && fd_out == 1)
	{
		if (!args || !args[1])
		{
			number = free_shell(shell_to_free);
			ft_putstr_fd("exit\n", fd_out);
			exit(number & 255);
		}
		check_digits(args, shell_to_free, fd_out);
		if (args[2])
		{
			ft_putstr_fd("exit\n", fd_out);
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
		number = ft_atoi(args[1]);
		free_shell(shell_to_free);
		ft_putstr_fd("exit\n", fd_out);
		exit(number & 255);
	}
	return (0);
}
