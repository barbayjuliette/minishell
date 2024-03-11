/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:06:28 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/25 16:47:26 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *string)
{
	int	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i] != '\0')
		i++;
	return (i);
}
