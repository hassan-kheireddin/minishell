/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheired <hkheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:57:25 by hkheired          #+#    #+#             */
/*   Updated: 2024/12/23 10:09:53 by hkheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*join_strs(char *str[2])
{
	char	*temp;

	temp = str[1];
	str[1] = ft_strjoin(str[1], str[0]);
	free(temp);
	free(str[0]);
	return (str[1]);
}

static char	*handle_flag(char *str[2], int quotes[2], t_prompt *prompt)
{
	char	*expand;

	expand = expand_vars(str[0], -1, quotes, prompt);
	return (expand);
}

static char	*get_here_str(char *str[2], size_t len,
				char *limit, t_prompt *prompt)
{
	char	*temp;
	int		quotes[2];

	setup_signal_handlers(1);
	while (g_status != 130 && (!str[0] || ft_strncmp(str[0], limit, len) \
		|| ft_strlen(limit) != len))
	{
		str[1] = join_strs(str);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("minishell: warning: here-document (wanted `%s\')\n", limit);
			break ;
		}
		if (!prompt->flag)
			str[0] = handle_flag(str, quotes, prompt);
		prompt->flag = 0;
		temp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(temp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	setup_signal_handlers(0);
	return (str[1]);
}

int	get_here_doc(char *str[2], char *aux[2], t_prompt *prompt)
{
	int		fd[2];

	g_status = 0;
	if (pipe(fd) == -1)
	{
		mini_perror(PIPERR, NULL, 1);
		return (-1);
	}
	str[1] = get_here_str(str, 0, aux[0], prompt);
	if (!str[1])
	{
		close(fd[WRITE_END]);
		close(fd[READ_END]);
		return (-1);
	}
	write(fd[WRITE_END], str[1], ft_strlen(str[1]));
	free(str[1]);
	close(fd[WRITE_END]);
	if (g_status == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}
