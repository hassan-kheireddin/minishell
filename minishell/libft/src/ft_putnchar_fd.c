/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheired <hkheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:04:20 by hkheired          #+#    #+#             */
/*   Updated: 2024/12/13 09:04:21 by hkheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_putnchar_fd(char c, int fd, int n)
{
	int	count;

	count = 0;
	while (n-- > 0)
		count += (int)write(fd, &c, 1);
	return (count);
}
