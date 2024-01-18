/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:07:03 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/18 12:24:14 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_elem_case(t_envlst **envlst, t_envlst *curr, char **args, size_t i)
{
	if (ft_strcmp(curr->key, args[i]) == 0)
	{
		*envlst = curr->next;
		free(curr->value);
		free(curr->key);
		free(curr);
		return (0);
	}
	return (1);
}

void	unset_loop(t_envlst **envlst, t_envlst *curr, char **args, size_t i)
{
	t_envlst	*head;
	t_envlst	*temp;

	head = *envlst;
	curr = head;
	if (!first_elem_case(envlst, curr, args, i))
		return ;
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->next->key, args[i]) == 0)
		{
			temp = curr->next;
			curr->next = curr->next->next;
			free(temp->value);
			free(temp->key);
			free(temp);
			return ;
		}
		curr = curr->next;
	}
}

//not tested
int	bi_unset(char **args, t_envlst **envlst, int fd_in, int fd_out)
{
	t_envlst	*curr;
	size_t		i;

	i = 1;
	curr = NULL;
	if (fd_in == 0 && fd_out == 1)
	{
		if (!envlst || !*envlst)
			return (0);
		while (args[i])
		{
			unset_loop(envlst, curr, args, i);
			i++;
		}
	}
	return (0);
}
