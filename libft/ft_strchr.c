/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 18:12:09 by lwang             #+#    #+#             */
/*   Updated: 2016/10/20 15:20:41 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	dst;
	int		i;

	i = 0;
	dst = (char)c;
	while (s[i])
	{
		if (s[i] == c)
			return ((char*)(s + i));
		i++;
	}
	if (c == '\0')
		return ((char*)(s + i));
	return (NULL);
}
