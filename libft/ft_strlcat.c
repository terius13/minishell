/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:10:00 by ting              #+#    #+#             */
/*   Updated: 2023/09/23 16:05:26 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;
	size_t	j;

	srclen = ft_strlen(src);
	i = 0;
	j = 0;
	while (i < size && dst[i] != '\0')
		i++;
	if (i == size)
		return (i + srclen);
	else
	{
		while (i + j + 1 < size && src[j] != '\0')
		{
			dst[i + j] = src[j];
			j++;
		}
		if (i + j < size)
			dst[i + j] = '\0';
	}
	return (i + srclen);
}
/*
#include <string.h>
int	main(void)
{
	char	string[] = "testing";
	char	dest[] = "123";
	size_t	i;

	i = ft_strlcat(dest, string, 11);
	printf("%zu\n", i);
	printf("%s\n", dest);
	printf("%ld\n", ft_strlen(dest));
//	printf("%zu", ft_strlcat(dest, string, size));
}
*/
