/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:13:13 by ting              #+#    #+#             */
/*   Updated: 2023/09/16 21:11:32 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int				i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (n > 0)
	{
		p[i] = (unsigned char)c;
		n--;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	char	string[] = "Hello";
	int	c = '/';
	size_t n = 3;

	ft_memset(string, c, n);
	printf("%s", string);
}
*/
