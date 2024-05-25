/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:15:13 by ting              #+#    #+#             */
/*   Updated: 2023/09/15 20:45:35 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*pd;
	unsigned const char	*ps;

	pd = (unsigned char *)dest;
	ps = (unsigned const char *)src;
	if (dest < src)
		ft_memcpy(dest, src, n);
	else if (src < dest)
		while (n--)
			pd[n] = ps[n];
	return (dest);
}
/*
int	main(void)
{
	char	destination[] = "Hello";
	char	source[] = "Bye";
	size_t	n = 3;
	ft_memmove(destination, source, n);
	printf("ft_memmove, result: %s\n", destination);
	memmove(destination, source, n);
	printf("memmove, result: %s\n", destination);
}
*/
