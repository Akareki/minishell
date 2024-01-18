/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:19:06 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/18 11:08:44 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	replace_by_env(char *to_return, const char *str,
			size_t j, t_envlst *envlst)
{
	size_t	k;
	char	*env_value;
	char	*variable;

	variable = grab_variable(str);
	env_value = env_get_value(envlst, variable);
	free(variable);
	if (!env_value)
		return (0);
	k = 0;
	while (env_value[k])
	{
		to_return[j] = env_value[k];
		j++;
		k++;
	}
	return (k);
}

size_t	len_without_quotes(const char *str)
{
	size_t	i;
	size_t	count;
	bool	single_quote_flag;
	bool	double_quote_flag;

	i = 0;
	count = 0;
	single_quote_flag = 0;
	double_quote_flag = 0;
	while (str[i])
	{
		if (str[i] == '\'' && double_quote_flag == 0)
			single_quote_flag = !single_quote_flag;
		else if (str[i] == '"' && single_quote_flag == 0)
			double_quote_flag = !double_quote_flag;
		else
			count++;
		i++;
	}
	return (count);
}

char	*remove_quotes(const char *str)
{
	char	*to_return;
	ssize_t	i;
	ssize_t	j;
	bool	single_quote_flag;
	bool	double_quote_flag;

	i = -1;
	j = -1;
	single_quote_flag = 0;
	double_quote_flag = 0;
	to_return = malloc(sizeof(char) * (len_without_quotes(str) + 1));
	if (!to_return)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '\'' && double_quote_flag == 0)
			single_quote_flag = !single_quote_flag;
		else if (str[i] == '"' && single_quote_flag == 0)
			double_quote_flag = !double_quote_flag;
		else
			to_return[++j] = str[i];
	}
	to_return[j + 1] = '\0';
	return (to_return);
}

void	string_expansion_loop(const char *str, t_envlst *envlst,
				char *to_return, int flag)
{
	ssize_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		flag = set_flag(str[i], flag);
		while (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
			&& flag != 1)
		{
			j += replace_by_env(to_return, &str[i + 1], j, envlst);
			i += len_for_variable(str, i + 1) + 1;
		}
		if (!str[i])
			break ;
		to_return[j] = str[i];
		j++;
	}
	to_return[j] = '\0';
}

char	*expand_variables(const char *str, t_envlst *envlst)
{
	char	*to_return;
	char	*to_return_without_quote;
	int		flag;

	to_return = malloc(sizeof(char) * (ft_strlen(str)
				+ len_of_variables_values(str, envlst)
				- len_of_variables(str) + 1));
	if (!to_return)
		return (NULL);
	flag = 0;
	string_expansion_loop(str, envlst, to_return, flag);
	to_return_without_quote = remove_quotes(to_return);
	free(to_return);
	return (to_return_without_quote);
}
