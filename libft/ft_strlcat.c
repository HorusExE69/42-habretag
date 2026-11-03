/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habretag <habretag@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 13:57:14 by habretag          #+#    #+#             */
/*   Updated: 2026/11/02 16:27:55 by habretag         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	len_tot;
	size_t	i;

	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	len_tot = len_src + len_dst;
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
	return (len_tot);
}
