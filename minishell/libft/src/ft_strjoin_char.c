/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheired <hkheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:57:50 by hkheired          #+#    #+#             */
/*   Updated: 2024/12/18 13:58:45 by hkheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin_char(char *str, char c)
{
	size_t	len;
	char	*result;

	len = ft_strlen(str);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, len + 1);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}
