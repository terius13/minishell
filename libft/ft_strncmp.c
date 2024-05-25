/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:27:24 by ting              #+#    #+#             */
/*   Updated: 2023/09/17 15:00:28 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	int				r;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	r = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (r == 0 && i < n)
	{
		if (str1[i] != str2[i] || (str1[i] || str2[i]))
		{
			r = str1[i] - str2[i];
		}
		else if (str1[i] == '\0' && str2[i] == '\0')
			return (0);
		i++;
	}
	return (r);
}
/*
#include <string.h>
int	main(void)
{
	char	s1[] = "a";
	char	s2[] = "";
	size_t	n = 3;
//	int	r;

	r = ft_strncmp(s1, s2, n);
	if (r == 0)
		printf("The string are equal");
	else if (r < 0)
		printf("s1 is bigger than s2");
	else
		printf("s1 is smaller than s2");

	printf("%i\n", ft_strncmp(s1, s2, n));
	printf("%i", strncmp(s1, s2, n));
}
*/
