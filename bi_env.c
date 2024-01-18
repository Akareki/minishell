/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:07:16 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/17 10:45:41 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_env(t_envlst *envlst, char **args, int fd_out)
{
	if (args[1])
		return (125);
	while (envlst != NULL)
	{
		ft_putstr_fd(envlst->key, fd_out);
		ft_putstr_fd("=", fd_out);
		ft_putstr_fd(envlst->value, fd_out);
		ft_putstr_fd("\n", fd_out);
		envlst = envlst->next;
	}
	return (0);
}
