/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheired <hkheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:02:26 by hkheired          #+#    #+#             */
/*   Updated: 2024/12/18 14:03:29 by hkheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*handle_escaped_dollar(char *result, int *i)
{
	char	*temp;

	temp = result;
	result = ft_strjoin_char(result, '$');
	free(temp);
	(*i)++;
	return (result);
}

char	*append_character(char *result, char c)
{
	char	*temp;

	temp = result;
	result = ft_strjoin_char(result, c);
	free(temp);
	return (result);
}

static int	validate_rules(char *str, int i, int quotes[2])
{
	if ((!quotes[0] && !quotes[1] && str[i] == '~')
		&& (i == 0 || (str[i - 1] == ' '))
		&& (str[i + 1] == '\0' || str[i + 1] == ' ' || str[i + 1] == '/'))
		return (1);
	return (0);
}

char	*expand_path(char *str, int i, int quotes[2], char *var)
{
	char	*path;
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (validate_rules(str, i, quotes))
		{
			aux = ft_substr(str, 0, i);
			path = ft_strjoin(aux, var);
			free(aux);
			aux = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, aux);
			free(aux);
			free(path);
			return (expand_path(str, i + ft_strlen(var) - 1, quotes, var));
		}
	}
	free(var);
	return (str);
}
