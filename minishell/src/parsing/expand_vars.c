/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheired <hkheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:56:35 by hkheired          #+#    #+#             */
/*   Updated: 2024/12/23 12:13:45 by hkheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*handle_special_cases(char *result, char *str, int i, t_prompt *prompt)
{
	char	*var;
	char	*temp;

	if (str[i] == '$')
		var = ft_itoa(prompt->pid);
	else if (str[i] == '?')
		var = ft_itoa(g_status);
	else
		var = ft_strdup("");
	if (!var)
		return (result);
	temp = result;
	result = ft_strjoin(result, var);
	free(temp);
	free(var);
	return (result);
}

char	*handle_variable_expansion(char *result, char *str,
		int i, t_prompt *prompt)
{
	char	*var_name;
	char	*var_value;
	char	*temp;
	int		j;

	j = i + 1;
	if (str[j] == '$' || str[j] == '?')
		return (handle_special_cases(result, str, j, prompt));
	char *pwd = ft_strnstr(&str[j],"PWD",3);//add
    if (pwd && prompt->pwd != NULL)//add
		printf("%s\n",prompt->pwd);//add
	prompt->pwd =NULL;//add
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	var_name = ft_substr(str, i + 1, j - (i + 1));
	if (!var_name)
		return (result);
	var_value = mini_getenv(var_name, prompt->envp, ft_strlen(var_name));
	free(var_name);
	if (!var_value)
		var_value = ft_strdup("");
	if (!var_value)
		return (result);
	temp = result;
	result = ft_strjoin(result, var_value);
	free(temp);
	free(var_value);
	return (result);
}

int	update_index_after_expansion(char *str, int i)
{
	int	j;

	j = i + 1;
	if (str[j] == '$' || str[j] == '?')
		return (j);
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	return (j - 1);
}

char	*expand_vars(char *str, int i, int quotes[2], t_prompt *prompt)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && str[i] == '\\' && str[i + 1] == '$')
			result = handle_escaped_dollar(result, &i);
		else if (!quotes[0] && str[i] == '$' && ft_isdigit(str[i + 1]))
			i++;
		else if (!quotes[0] && str[i] == '$' && str[i + 1])
		{
			result = handle_variable_expansion(result, str, i, prompt);
			i = update_index_after_expansion(str, i);
		}
		else
			result = append_character(result, str[i]);
	}
	free(str);
	return (result);
}
