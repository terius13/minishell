/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:12:19 by ting              #+#    #+#             */
/*   Updated: 2023/09/12 18:14:20 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c = c + 32;
	return (c);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("The char is A, result:%c\n", ft_tolower('A'));
	printf("The char is Z, result:%c\n", ft_tolower('Z'));
	printf("The char is 4, result:%c\n", ft_tolower('4'));
}
*/
