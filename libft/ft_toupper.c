/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:14:56 by ting              #+#    #+#             */
/*   Updated: 2023/09/12 18:15:50 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c = c - 32;
	return (c);
}
/*
int	main(void)
{
	printf("If the char is a, result:%c\n", ft_toupper('a'));
	printf("If the char is z, result:%c\n", ft_toupper('z'));
	printf("If the char is 4, result:%c\n", ft_toupper('4'));
}
*/
