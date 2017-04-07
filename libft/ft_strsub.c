/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 19:28:03 by lwang             #+#    #+#             */
/*   Updated: 2016/10/20 17:25:35 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*dst;
	int				i;
	unsigned long	j;
	int				t;

	if (!s)
		return (0);
	i = 0;
	t = 0;
	j = ft_strlen(s);
	dst = (char*)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (0);
	if (start + len > j)
		return (NULL);
	while (s[start + i] && len)
	{
		dst[i] = s[start + i];
		i++;
		len--;
	}
	dst[i] = '\0';
	return (dst);
}
