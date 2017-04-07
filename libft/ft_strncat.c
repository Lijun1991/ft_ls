/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 21:47:27 by lwang             #+#    #+#             */
/*   Updated: 2016/10/20 15:13:45 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	int		i;
	int		j;
	char	*ps1;
	int		len;

	i = 0;
	j = 0;
	ps1 = (char*)s1;
	len = ft_strlen(s1);
	while (s2[j] && n > 0)
	{
		ps1[len + j] = s2[j];
		j++;
		n--;
	}
	ps1[len + j] = '\0';
	return (ps1);
}
