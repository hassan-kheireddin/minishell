/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdel-f <rabdel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:44:09 by rabdel-f          #+#    #+#             */
/*   Updated: 2024/12/12 11:44:09 by rabdel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//add this function to change g_status every time
void	handle_error(char *error)
{
	g_status = 1;
	ft_putstr_fd(error, 2);
}

int	cd_normal(t_prompt *p, char **str[2])
{
	char	*aux;

	aux = getcwd(NULL, 0);
	str[1] = ft_extend_matrix(str[1], aux);
	free(aux);
	cd_error(p, str);
	if (!g_status && (mini_getenv("PWD", p->envp, 3))) //add condition related to mini_getenv
		p->envp = mini_setenv("OLDPWD", str[1][1], p->envp, 6);
	else// add else condition
		p->envp = mini_setenv("OLDPWD", NULL, p->envp, 6);
	aux = getcwd(NULL, 0);
	if (!aux)
		aux = ft_strdup("");
	//delete the below commented one and add non-commented one
	// str[1] = ft_extend_matrix(str[1], aux);
	// free(aux);
	// p->envp = mini_setenv("PWD", str[1][2], p->envp, 3);
	// ft_free_matrix(&str[1]);
	if(!mini_getenv("PWD",p->envp,3))
		p->pwd = aux;
	else
	{
	str[1] = ft_extend_matrix(str[1], aux);
	free(aux);
	p->envp = mini_setenv("PWD", str[1][2], p->envp, 3);
	}
	ft_free_matrix(&str[1]);
	return (g_status);
}


void	cd_dash(t_prompt *p)
{
	char	*old;

	old = mini_getenv("OLDPWD", p->envp, 4);
	printf("%s\n", old);
	chdir(old);
	free(old);
	return ;
}

void	cd_error(t_prompt *p, char **str[2])
{
	DIR		*dir;

	dir = NULL;
	if (str[0][1] && str[0][2])
	{
		handle_error("minishell: cd: too many arguments\n");//change to handle error
		return ;
	}
	if (str[0][1] && !str[0][2])
		dir = opendir(str[0][1]);
	if (!str[0][1] && str[1][0] && !str[1][0][0])
		handle_error("minishell: HOME not set\n");//change to handle error
	if (str[1][0] && !str[0][1])
		g_status = chdir(str[1][0]) == -1;
	if (str[0][1] && dir && access(str[0][1], F_OK) != -1)
		chdir(str[0][1]);
	else if (str[0][1] && str[0][1][0] == '-' && str[0][1][1] == '\0')
		cd_dash(p);
	else if (str[0][1] && access(str[0][1], F_OK) == -1)
		mini_perror(NDIR, str[0][1], 1);
	else if (str[0][1])
		mini_perror(NOT_DIR, str[0][1], 1);
	if (str[0][1] && dir)
		closedir(dir);
}

int	mini_cd(t_prompt *p)
{
	char	**str[2];
	char	*aux;

	g_status = 0;
	str[0] = ((t_mini *)p->cmds->content)->full_cmd;
	aux = mini_getenv("HOME", p->envp, 4);
	if (!aux)
		aux = ft_strdup("");
	str[1] = ft_extend_matrix(NULL, aux);
	free(aux);
	cd_normal(p, str);
	return (g_status);
}
