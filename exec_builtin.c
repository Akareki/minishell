/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:32:03 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/18 11:50:08 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	exec_builtin(t_processlst *processlst, t_shell *shell)
{
	if (processlst->builtin_index == 0)
	{
		bi_echo((const char **)processlst->argv, processlst->fd_out);
		return (0);
	}
	else if (processlst->builtin_index == 1)
		return (bi_cd(processlst->argv, processlst->fd_in,
				processlst->fd_out, &shell->envlst));
	else if (processlst->builtin_index == 2)
		return (bi_pwd(processlst->argv, processlst->fd_out));
	else if (processlst->builtin_index == 3)
		return (bi_export(processlst->argv,
				&shell->envlst, processlst->fd_in, processlst->fd_out));
	else if (processlst->builtin_index == 4)
		return (bi_unset(processlst->argv, &shell->envlst,
				processlst->fd_in, processlst->fd_out));
	else if (processlst->builtin_index == 5)
		return (bi_env(shell->envlst, processlst->argv, processlst->fd_out));
	else if (processlst->builtin_index == 6)
		return (bi_exit(shell, processlst->argv,
				processlst->fd_in, processlst->fd_out));
	return (-1);
}
