/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheired <hkheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:57:35 by hkheired          #+#    #+#             */
/*   Updated: 2024/12/23 12:04:36 by hkheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**split_all(char **args, t_prompt *prompt)
{
	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, quotes, prompt);
		args[i] = expand_path(args[i], -1, quotes,
				mini_getenv("HOME", prompt->envp, 4));
		subsplit = ft_cmdsubsplit(args[i], "<|>");
		if (has_invalid_redirection(subsplit) == 1)
		{
			mini_perror(14, NULL, 2);
			ft_free_matrix(&subsplit);
			ft_free_matrix(&args);
			return (NULL);
		}
		ft_matrix_replace_in(&args, subsplit, i);
		i += ft_matrixlen(subsplit) - 1;
		ft_free_matrix(&subsplit);
	}
	return (args);
}

static void	*parse_args(char **args, t_prompt *p)
{
	char	**argument;
	int		is_exit;
	int		i;

	is_exit = 0;
	argument = split_all(args, p);
	if (!argument)
		return (p);
	p->cmds = fill_nodes(argument, -1, p);
	if (!p->cmds)
		return (p);
	i = ft_lstsize(p->cmds);
	g_status = builtin(p, p->cmds, &is_exit, 0);
	while (i-- > 0)
		waitpid(-1, &g_status, 0);
	if (!is_exit && g_status == 13)
		g_status = 0;
	if (g_status > 255)
		g_status = g_status / 256;
	if (args && is_exit)
	{
		ft_lstclear(&p->cmds, free_content);
		return (NULL);
	}
	return (p);
}

char	**trim_space(char *out)
{
	char	**a;

	a = ft_cmdtrim(out, " ");
	free(out);
	if (!a)
		mini_perror(QUOTE, NULL, 1);
	return (a);
}

void	handle_quote_hd(char **a, t_prompt *p)
{
	int		i;
	int		j;

	i = 0;
	while (a[i])
	{
		j = 0;
		if (ft_strncmp(a[i], "<<", 2) == 0 && a[i + 1])
		{
			while (a[i][j])
			{
				if (a[i + 1][j] == '"' || a[i + 1][j] == '\'')
					p->flag++;
				j++;
			}
		}
		// add this condition to check if no space
		else if (ft_strncmp(a[i], "<<", 2) == 0 && a[i] != NULL && a[i + 1] == NULL)
		{
			while (a[i][j])
			{
				if (a[i][j] == '"' || a[i][j] == '\'')
					p->flag++;
				j++;
			}
		}
		i++;
	}
}

void	*check_args(char *out, t_prompt *p)
{
	char	**a;
	t_mini	*n;

	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);
	a = trim_space(out);
	if (!a)
		return ("");
	handle_quote_hd(a, p);
	p = parse_args(a, p);
	if (p && p->cmds)
		n = p->cmds->content;
	if (p && p->cmds && n && n->full_cmd && ft_lstsize(p->cmds) == 1)
		p->envp = mini_setenv("_", n->full_cmd[ft_matrixlen(n->full_cmd) - 1],
				p->envp, 1);
	if (p && p->cmds)
		ft_lstclear(&p->cmds, free_content);
	return (p);
}
