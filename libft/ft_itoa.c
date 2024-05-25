/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:45:11 by ting              #+#    #+#             */
/*   Updated: 2023/09/25 19:32:31 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	countlp(int num)
{
	int	count;

	count = 0;
	if (num < 0)
	{
		count++;
		num = -num;
	}
	while (num > 9)
	{
		num = num / 10;
		count++;
	}
	count++;
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		counter;
	int		nbr;

	counter = countlp(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc((sizeof(char) * counter) + 1);
	if (!str)
		return (NULL);
	nbr = n;
	if (n < 0)
	{
		n = -n;
	}
	str[counter] = '\0';
	while (counter--)
	{
		str[counter] = n % 10 + '0';
		n = n / 10;
	}
	if (nbr < 0)
		str[0] = '-';
	return (str);
}
/*
int	main(int argc, char **argv)
{
	//int	num = -100;
	printf("%s\n", ft_itoa(ft_atoi(argv[1])));
	printf("%d", countlp(ft_atoi(argv[1])));
}
*/
