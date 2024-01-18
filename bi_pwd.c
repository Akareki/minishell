/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:52:00 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/16 10:28:21 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_pwd(char **args, int fd_out)
{
	char	*cwd;

	if (args[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (-1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (-1);
	ft_putstr_fd(cwd, fd_out);
	ft_putstr_fd("\n", fd_out);
	free(cwd);
	return (0);
}
