/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:14:16 by ting              #+#    #+#             */
/*   Updated: 2023/09/11 13:11:31 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
/*
int	main(void)
{
	printf("The char is A, result: %d\n", ft_isalnum('A'));
	printf("The char is 4, result: %d\n", ft_isalnum('4'));
	printf("The char is -, result: %d\n", ft_isalnum('-'));
}
*/
