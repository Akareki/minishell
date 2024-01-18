/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:43:58 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/17 12:45:32 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_words(t_wordlst *wordlst, t_envlst *envlst, int last_status)
{
	char	*tmp_str;

	while (wordlst)
	{
		tmp_str = wordlst->word;
		wordlst->word = string_expansion(wordlst->word, envlst, last_status);
		free(tmp_str);
		if (wordlst->word == NULL)
			return (-1);
		wordlst = wordlst->next;
	}
	return (0);
}
