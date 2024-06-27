/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:12:37 by ting              #+#    #+#             */
/*   Updated: 2024/06/27 17:02:13 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int					i;
	unsigned char		*pd;
	unsigned const char	*ps;

	pd = (unsigned char *)dest;
	ps = (unsigned const char *)src;
	i = 0;
	if (ps == NULL && pd == NULL)
		return (NULL);
	while (n > 0)
	{
		pd[i] = ps[i];
		i++;
		n--;
	}
	return (dest);
}
/*
int	main(void)
{
	char	destination[] = "hello";
	char	source[] = "me";
	size_t	n = 2;

	ft_memcpy(destination, source, n);
	printf("%s\n", destination);
}
*/
