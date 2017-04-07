/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 20:13:54 by lwang             #+#    #+#             */
/*   Updated: 2016/10/20 14:38:38 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	dst;
	int		len;
	int		i;

	dst = (char)c;
	len = ft_strlen(s);
	i = 0;
	while (len - i >= 0)
	{
		if (s[len - i] == c)
			return ((char*)(s + len - i));
		i++;
	}
	if (c == '\0')
		return ((char*)(s + len + 1));
	return (NULL);
}
