/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:09:29 by ting              #+#    #+#             */
/*   Updated: 2023/09/11 13:32:17 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
/*
int	main(void)
{
	char	str[] = "I love 42";
	char	str1[] = "I love 42";
	size_t	n = 5;

	ft_bzero(str, n);
	printf("Function: %s\n", str);
	bzero(str1, n);
	printf("bzero   : %s\n", str1);
	return (0);
}
*/
