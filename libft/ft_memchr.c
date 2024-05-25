/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:27:41 by ting              #+#    #+#             */
/*   Updated: 2023/09/15 20:47:46 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;
	unsigned char	cc;
	size_t			i;

	string = (unsigned char *) s;
	cc = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (string[i] == cc)
			return (&string[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	string[] = "";
	int	c = 0;
	size_t	n = 3;

	printf("ft_memchr:%p\n", ft_memchr(string, c, n));
	printf("memchr:%p\n", memchr(string, c, n));
}
*/
