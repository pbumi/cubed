/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:47:47 by pbumidan          #+#    #+#             */
/*   Updated: 2024/10/15 17:48:27 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;
	size_t	i;

	if (s == NULL)
		return (NULL);
	slen = gnl_strlen(s);
	if (start >= slen)
		len = 0;
	if (len > (slen - start))
		len = (slen - start);
	substr = (char *)malloc((sizeof(char)) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*gnl_strchr(const char *s, int c)
{
	size_t	i;
	size_t	slen;

	i = 0;
	if (!s)
		return (0);
	slen = gnl_strlen(s);
	while (i < slen +1)
	{
		if (s[i] == (char)c)
			return (&((char *)s)[i]);
		i++;
	}
	return (0);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	a;
	size_t	b;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = ((char *)malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1)));
	if (str == NULL)
		return (NULL);
	a = 0;
	while (s1[a])
	{
		str[a] = s1[a];
		a++;
	}
	b = 0;
	while (s2[b])
	{
		str[a] = s2[b];
		a++;
		b++;
	}
	str[a] = '\0';
	return (str);
}
