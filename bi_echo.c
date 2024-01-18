/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:46:20 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/18 11:56:06 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	bi_echo(const char **args, int fd_out)
{
	bool	flag_newline;
	size_t	i;

	flag_newline = 0;
	if (!args[1])
	{
		write(fd_out, "\n", 1);
		return ;
	}
	i = 1;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n'
			&& args[i][2] == '\0')
	{
		flag_newline = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd((char *)args[i], fd_out);
		if (args[i + 1])
			ft_putstr_fd(" ", fd_out);
		i++;
	}
	if (flag_newline == 0)
		ft_putstr_fd("\n", fd_out);
}
