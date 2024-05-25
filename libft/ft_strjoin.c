/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:04:06 by ting              #+#    #+#             */
/*   Updated: 2023/09/19 22:14:43 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	char	*str1;
	char	*str2;

	str1 = (char *)s1;
	str2 = (char *)s2;
	if (!str1 || !str2)
		return (NULL);
	dest = (char *)malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, str1, ft_strlen(str1) + 1);
	ft_strlcpy(&dest[ft_strlen(str1)], str2, ft_strlen(str2) + 1);
	return (dest);
}
/*
int	main(void)
{
	char	s1[] = "hello";
	char	s2[] = "bye";
	printf("%s", ft_strjoin(s1, s2));
}
*/
