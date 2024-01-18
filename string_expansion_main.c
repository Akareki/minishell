/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_expansion_main.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:06:10 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/18 11:46:08 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	number_of_interr(const char *str)
{
	size_t	i;
	size_t	count;
	int		flag;

	i = 0;
	count = 0;
	flag = 0;
	while (str[i])
	{
		flag = set_flag(str[i], flag);
		if (str[i + 1] && str[i] == '$' && str[i + 1] == '?' && flag != 1)
			count++;
		i++;
	}
	return (count);
}

void	expand_interr_loop(const char *s, char *to_return,
		char *last_status_str, size_t i)
{
	size_t	j;
	size_t	k;
	int		f;

	j = 0;
	k = 0;
	f = 0;
	while (s[++i])
	{
		f = set_flag(s[i], f);
		while (s[i] && s[i + 1] && s[i] == '$' && s[i + 1] == '?' && f != 1)
		{
			i += 2;
			while (last_status_str[k])
				to_return[j++] = last_status_str[k++];
			k = 0;
		}
		if (!s[i])
			break ;
		to_return[j] = s[i];
		j++;
	}
	to_return[j] = '\0';
}

char	*string_expansion(const char *str, t_envlst *envlst, int last_status)
{
	char	*last_status_str;
	char	*to_return;
	char	*to_return_w_variables;
	size_t	i;

	i = -1;
	last_status_str = ft_itoa(last_status);
	if (!last_status_str)
		return (NULL);
	to_return = malloc(sizeof(char) * (ft_strlen(last_status_str)
				* number_of_interr(str) + ft_strlen(str)
				- (number_of_interr(str) * 2) + 1));
	if (!to_return)
		return (NULL);
	expand_interr_loop(str, to_return, last_status_str, i);
	to_return_w_variables = expand_variables(to_return, envlst);
	free(to_return);
	free(last_status_str);
	return (to_return_w_variables);
}
