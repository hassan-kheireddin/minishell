/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheired <hkheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:49:09 by hkheired          #+#    #+#             */
/*   Updated: 2024/12/23 12:29:23 by hkheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_only_export(char *argv, t_prompt *prompt)
{
	int		i;
	char	**export;

	export = prompt->export;
	i = -1;
	//if condtion added
	if(ft_strchars_i("0123456789",argv) >= 0)
	{
		printf("minishell: '%s' not a valid identifier\n", argv);
		return ;
	}
	while (export[++i])
	{
		if (!ft_strncmp(argv, export[i], ft_strlen(argv)))
		{
			return ;
		}	
	}
	prompt->export = ft_extend_matrix(prompt->export, argv);
}

void	add_env(t_prompt *prompt, char *argv)
{
	int		i;
	char	*new_entry;

	i = -1;
	while (prompt->envp[++i])
	{
		if (!ft_strncmp(argv, prompt->envp[i],
				ft_strchars_i(prompt->envp[i], "=")))
		{
			free(prompt->envp[i]);
			new_entry = ft_strdup(argv);
			if (!new_entry)
				return ;
			prompt->envp[i] = new_entry;
			break ;
		}
	}
	add_export(prompt, argv);
	return ;
}

void	add_export(t_prompt *prompt, char *argv)
{
	int		i;
	char	*new_entry;

	i = -1;
	while (prompt->export[++i])
	{
		if (!ft_strncmp(argv, prompt->export[i], \
			ft_strchars_i (prompt->export[i], "=")))
		{
			free(prompt->export[i]);
			new_entry = ft_strdup(argv);
			if (!new_entry)
				return ;
			prompt->export[i] = new_entry;
			return ;
		}
	}
}

void	print_error_export(t_prompt *prompt, char *argv)
{
	printf("minishell: '%s' not a valid identifier\n", argv);
	if (argv[0] == '=' && !argv[1])
		return ;
	if (ft_strchars_i(argv, "~{}-#!+@.") >= 0)
		return ;
	prompt->export = ft_extend_matrix(prompt->export, argv);
}

void	extend_env_export(t_prompt *prompt, char *argv)
{
	int		i;
	int		flag;
	char	*new_variable;

	flag = 0;
	i = -1;
	prompt->envp = ft_exted_nmatrix(prompt->envp, argv);
	while (prompt->export[++i])
	{
		if (!ft_strncmp(argv, prompt->export[i], ft_strchars_i(argv, "=")))
		{
			free(prompt->export[i]);
			new_variable = ft_strdup(argv);
			if (!new_variable)
				return ;
			prompt->export[i] = new_variable;
			flag = 1;
			return ;
		}
	}
	if (flag == 0)
		prompt->export = ft_extend_matrix(prompt->export, argv);
}