/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:54:57 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/09 14:20:00 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_set_value(t_envlst **envlst, char *keyvalue)
{
	size_t		key_len;
	t_envlst	*envlst_elem;

	if (!keyvalue)
		return (-1);
	key_len = 0;
	while (keyvalue[key_len] && keyvalue[key_len] != '=')
		key_len++;
	envlst_elem = *envlst;
	while (envlst_elem && !(ft_strlen(envlst_elem->key) == key_len
			&& ft_strncmp(envlst_elem->key, keyvalue, key_len) == 0))
		envlst_elem = envlst_elem->next;
	if (envlst_elem)
	{
		free(envlst_elem->value);
		envlst_elem->value
			= ft_calloc(ft_strlen(keyvalue) - key_len, sizeof(char));
		if (!envlst_elem->value)
			return (-1);
		env_putvalue(keyvalue, envlst_elem->value);
	}
	else
		return (env_lst_add(envlst, keyvalue));
	return (0);
}

char	*env_get_value(t_envlst *envlst, char *key)
{
	if (!key)
		return (NULL);
	while (envlst)
	{
		if (ft_strcmp(envlst->key, key) == 0)
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}
