/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habretag <habretag@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 13:54:53 by habretag          #+#    #+#             */
/*   Updated: 2026/11/02 14:43:39 by habretag         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	tot;

	if (count == 0 || size == 0)
		return (malloc(1));
	tot = count * size;
	if (tot / count != size)
		return (NULL);
	res = malloc(tot);
	if (!res)
		return (NULL);
	ft_bzero(res, tot);
	return (res);
}
