/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheired <hkheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:02:47 by hkheired          #+#    #+#             */
/*   Updated: 2024/12/13 09:02:48 by hkheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_matrixlen(char **m)
{
	int	i;

	i = 0;
	while (m && m[i])
		i++;
	return (i);
}
