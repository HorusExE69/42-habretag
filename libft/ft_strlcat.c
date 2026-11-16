/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habretag <habretag@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 13:57:14 by habretag          #+#    #+#             */
/*   Updated: 2026/11/16 10:52:22 by habretag         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;

	len_src = ft_strlen(src);
	len_dst = 0;
	while (len_dst < size && dst[len_dst] != '\0')
		len_dst++;
	if (len_dst == size)
		return (size + len_src);
	i = len_dst;
	if (size == 0)
		return (len_src);
	else if (len_dst >= size)
		return (size + len_src);
	while (i < size - 1 && src[i - len_dst])
	{
		dst[i] = src[i - len_dst];
		i ++;
	}
	dst[i] = '\0';
	return (len_src + len_dst);
}
