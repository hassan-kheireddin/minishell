/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheired <hkheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:56:43 by hkheired          #+#    #+#             */
/*   Updated: 2024/12/23 10:27:46 by hkheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_mini	*mini_init(void)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->full_cmd = NULL;
	mini->full_path = NULL;
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	return (mini);
}

t_mini *get_params(t_mini *node, char **a[2], int *i, t_prompt *prompt)
{
    if (a[0][*i])
    {
        if (a[0][*i][0] == '>' && a[0][*i + 1] &&
            a[0][*i + 1][0] == '>' && a[0][*i + 2] && a[0][*i + 2][0] != '<' && a[0][*i + 2][0] != '>')
            node = get_outfile2(node, a[1], i);
        else if (a[0][*i][0] == '>' && a[0][*i + 1] &&
                 a[0][*i + 1][0] != '>' &&
                 a[0][*i + 1][0] != '<')
            node = get_outfile1(node, a[1], i);
        else if (a[0][*i][0] == '<' && a[0][*i + 1] &&
                 a[0][*i + 1][0] == '<' && a[0][*i + 2] && a[0][*i + 2][0] != '<' && a[0][*i + 2][0] != '>')
            node = get_infile2(node, a[1], i, prompt);
        else if (a[0][*i][0] == '<' && a[0][*i + 1] &&
                 a[0][*i + 1][0] != '<' &&
                 a[0][*i + 1][0] != '>')
            node = get_infile1(node, a[1], i);
        else if (a[0][*i][0] != '|')
            node->full_cmd = ft_extend_matrix(node->full_cmd, a[1][*i]);
        else
        {
            mini_perror(PIPENDERR, NULL, 2);
            *i = -2;
        }
        return (node);
    }
    mini_perror(PIPENDERR, NULL, 2);
    *i = -2;
    return (node);
}

// t_mini	*get_params(t_mini *node, char **a[2], int *i, t_prompt *prompt)
// {
// 	if (a[0][*i])
// 	{
// 		if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>' && a[0][*i + 2] && a[0][*i + 2][0] != '<') //add the third condition to check this
// 			node = get_outfile2(node, a[1], i);
// 		else if (a[0][*i][0] == '>')
// 			node = get_outfile1(node, a[1], i);
// 		else if (a[0][*i][0] == '<' && a[0][*i + 1] && 
// 			a[0][*i + 1][0] == '<' && a[0][*i + 2] && a[0][*i + 2][0] != '<'
// 				&& a[0][*i + 2][0] != '>')
// 			node = get_infile2(node, a[1], i, prompt);
// 		else if (a[0][*i][0] == '<')
// 			node = get_infile1(node, a[1], i);
// 		else if (a[0][*i][0] != '|')
// 			node->full_cmd = ft_extend_matrix(node->full_cmd, a[1][*i]);
// 		else
// 		{
// 			mini_perror(PIPENDERR, NULL, 2);
// 			*i = -2;
// 		}
// 		return (node);
// 	}
// 	mini_perror(PIPENDERR, NULL, 2);
// 	*i = -2;
// 	return (node);
// }

static char	**get_trimmed(char **args)
{
	char	**temp;
	char	*aux;
	int		j;

	j = -1;
	temp = ft_dup_matrix(args);
	while (temp && temp[++j])
	{
		aux = ft_strtrim_all(temp[j], 0, 0);
		free(temp[j]);
		temp[j] = aux;
	}
	return (temp);
}

static t_list	*stop_fill(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, free_content);
	ft_free_matrix(&temp);
	ft_free_matrix(&args);
	return (NULL);
}

t_list	*fill_nodes(char **args, int i, t_prompt *prompt)
{
	t_list	*cmds[2];
	char	**temp[2];

	cmds[0] = NULL;
	temp[1] = get_trimmed(args);
	while (args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(mini_init()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		temp[0] = args;
		cmds[1]->content = get_params(cmds[1]->content, temp, &i, prompt);
		if (i < 0)
			return (stop_fill(cmds[0], args, temp[1]));
		if (!args[i])
			break ;
	}
	ft_free_matrix(&temp[1]);
	ft_free_matrix(&args);
	return (cmds[0]);
}
