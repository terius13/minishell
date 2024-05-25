/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:14:40 by ting              #+#    #+#             */
/*   Updated: 2023/09/11 13:14:24 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
int	main(void)
{
	printf("The ascii value is 7, RESULT: %d\n", ft_isascii(7));
	printf("The ascii value is 99, RESULT: %d\n", ft_isascii(99));
	printf("The ascii value is -9, RESULT: %d\n", ft_isascii(-9));
}
*/
