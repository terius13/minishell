/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:29:00 by ting              #+#    #+#             */
/*   Updated: 2023/09/20 19:23:07 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charinset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimstr;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	while (s1[start] && (ft_charinset(s1[start], set) == 1))
		start++;
	end = ft_strlen(s1);
	while (end > start && (ft_charinset(s1[end - 1], set) == 1))
		end--;
	trimstr = (char *)malloc(end - start + 1);
	if (trimstr == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		trimstr[i] = s1[start];
		i++;
		start++;
	}
	trimstr[i] = '\0';
	return (trimstr);
}
/*
int	main(void)
{
	char	string[] = "bye helbyelo bye";
	char	set[] = "bye";

	printf("%s", ft_strtrim(string, set));
}
*/
