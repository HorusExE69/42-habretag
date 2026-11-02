/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habretag <habretag@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 13:57:00 by habretag          #+#    #+#             */
/*   Updated: 2026/11/02 13:57:00 by habretag         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *str, char c)
{
	size_t	i;
	size_t	count;
	int		in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if (c != str[i] && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (c == str[i])
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*malloc_word(const char *str, char c)
{
	size_t		i;
	char		*word;

	i = 0;
	while (str[i] && c != str[i])
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && c != str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**free_all(char	**strs, size_t j)
{
	while (j > 0)
	{
		j--;
		free(strs[j]);
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**split;
	size_t		i;
	size_t		j;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && c == s[i])
			i++;
		if (s[i] && s[i] != c)
		{
			split[j] = malloc_word(&s[i], c);
			if (!split[j])
				return (free_all(split, j));
			i += ft_strlen(split[j++]);
		}
	}
	split[j] = NULL;
	return (split);
}
