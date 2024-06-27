/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:19:28 by ting              #+#    #+#             */
/*   Updated: 2024/06/27 20:56:03 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, char *s2, int size)
{
	char	*string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	string = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (string == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		string[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0' && j < size)
	{
		string[i] = s2[j];
		i++;
		j++;
	}
	string[i] = '\0';
	return (string);
}

void	ft_bzero(void *s, size_t n)
{
	int				i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (n > 0)
	{
		p[i] = '\0';
		i++;
		n--;
	}
}

char	*ft_strchr(const char *s, int c)
{
	char	*string;
	char	cc;
	int		i;

	i = 0;
	string = (char *)s;
	cc = (char) c;
	if (!string)
		return (NULL);
	while (string[i] != cc)
	{
		if (string[i] == '\0')
			return (NULL);
		i++;
	}
	return (&string[i]);
}


