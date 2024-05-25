/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:41:53 by ting              #+#    #+#             */
/*   Updated: 2023/09/17 14:18:07 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		length;
	size_t	i;

	length = ft_strlen(little);
	i = 0;
	if (*little == '\0')
		return ((char *) big);
	while (big[i] != '\0' && i + length <= len)
	{
		if (ft_strncmp(&big[i], little, length) == 0)
			return ((char *) &big[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	strbig[] = "Foo Bar Baz";
	char	strlil[] = "Bar";
	size_t	len = 10;

	printf("ft_strnstr: %s", ft_strnstr(strbig, strlil, len));
}
*/
