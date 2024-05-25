/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:04:35 by ting              #+#    #+#             */
/*   Updated: 2023/09/20 20:34:24 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, s + i);
		i++;
	}
}
/*
void     ftoupper(unsigned int i, char *c)
{
	i = 0;
        while ((c[i] >= 97 && c[i] <= 122) && c[i] != '\0')
	{
                c[i] = c[i] - 32;
		i++;
	}
}
int	main(void)
{
	char	string[] = "hello";
	ft_striteri(string, ftoupper);
	printf("%s", string);
}
*/
