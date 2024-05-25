/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:27:02 by ting              #+#    #+#             */
/*   Updated: 2023/09/21 19:34:26 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*string;
	char	cc;
	int		i;

	string = (char *) s;
	cc = (char) c;
	i = ft_strlen(string);
	while (i >= 0)
	{
		if (string[i] == cc)
			return (&string[i]);
		i--;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	string[] = "hello";
	int	c = 'w';

	printf("ft_strrchr: %s\n", ft_strrchr(string, c));
	printf("strrchr: %s\n", strrchr(string, c));
}
*/
