/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheired <hkheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:40:29 by hkheired          #+#    #+#             */
/*   Updated: 2024/12/14 11:44:53 by hkheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_unset_export(char *argv, t_prompt *prompt)
{
	int		i;

	i = -1;
	while (prompt->export[++i])
	{
		if (!ft_strncmp(argv, prompt->export[i],
				ft_strchars_i(prompt->export[i], "=")))
		{
			ft_matrix_replace_in(&prompt->export, NULL, i);
			return ;
		}
	}
}

int	var_in_envp_unset(char *argv, char **envp, int ij[2])
{
	int	pos;

	ij[1] = 0;
	pos = ft_strchr_i(argv, '=');
	if (pos == -1)
		return (-1);
	while (envp[ij[1]])
	{
		if (!ft_strncmp(envp[ij[1]], argv, pos + 1))
			return (1);
		ij[1]++;
	}
	return (0);
}

int	mini_unset(t_prompt *prompt)
{
	char	**argv;
	char	*aux;
	int		ij[2];

	ij[0] = 0;
	argv = ((t_mini *)prompt->cmds->content)->full_cmd;
	if (ft_matrixlen(argv) >= 2)
	{
		while (argv[++ij[0]])
		{
			if (ft_strchars_i(argv[ij[0]], "=") == -1)
				handle_unset_export(argv[ij[0]], prompt);
			if (argv[ij[0]][ft_strlen(argv[ij[0]]) - 1] == '=')
				return (0);
			aux = ft_strjoin(argv[ij[0]], "=");
			free(argv[ij[0]]);
			argv[ij[0]] = aux;
			if (var_in_envp_unset(argv[ij[0]], prompt->envp, ij))
			{
				ft_matrix_replace_in(&prompt->envp, NULL, ij[1]);
				handle_unset_export(argv[ij[0]], prompt);
			}
		}
	}
	return (0);
}
