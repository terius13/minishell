/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:10:30 by ting              #+#    #+#             */
/*   Updated: 2023/09/22 22:01:06 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char	const *s, unsigned int start, size_t len)
{
	char	*dest;
	char	*str;

	str = (char *) s;
	if (start >= ft_strlen(str))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(str) - start)
		len = ft_strlen(s) - start;
	dest = (char *)malloc(len + 1);
	if (str == NULL || dest == NULL)
		return (NULL);
	ft_strlcpy(dest, str + start, len + 1);
	return (dest);
}
/*
int	main(void)
{
	char	string[] = "hello i am bye";
	int	start = 3;
	size_t	len = 5;

	printf("%s", ft_substr(string, start, len));
}
*/
