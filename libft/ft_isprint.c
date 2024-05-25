/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:14:55 by ting              #+#    #+#             */
/*   Updated: 2023/09/11 13:17:16 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
int	main(void)
{
	printf("The ascii value is 66, RESULT: %d\n", ft_isprint(66));
	printf("The ascii value is 99, RESULT: %d\n", ft_isprint(99));
	printf("The ascii value is 5, RESULT: %d\n", ft_isprint(5));
}
*/
