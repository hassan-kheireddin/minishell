/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheired <hkheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:46:28 by rabdel-f          #+#    #+#             */
/*   Updated: 2024/12/19 10:41:47 by hkheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	has_invalid_redirection(char **tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
	{
		if (tokens[i][0] == '>' || tokens[i][0] == '<')
		{
			if (tokens[i + 1] && (tokens[i + 1][0] == '>'
				|| tokens[i + 1][0] == '<' || tokens[i + 1][0] == '|'))
			{
				if (tokens[i + 1][0] == '|')
					return (1);
				if (tokens[i + 2] && (tokens[i + 2][0] == '>'
					|| tokens[i + 2][0] == '<' || tokens[i + 2][0] == '|'))
					return (1);
			}
		}
		i++;
	}
	return (0);
}
