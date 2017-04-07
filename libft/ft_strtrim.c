/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 16:58:43 by lwang             #+#    #+#             */
/*   Updated: 2016/10/20 14:34:20 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		skip_whitespace(char const *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (i);
		i++;
	}
	return (0);
}

static int		b_skip(char const *str)
{
	int		len;
	int		j;

	j = 0;
	len = ft_strlen(str);
	while (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\n')
	{
		len--;
	}
	return (len);
}

char			*ft_strtrim(char const *s)
{
	int		start_char;
	int		dst_len;
	char	*dst;

	if (!s)
		return (0);
	start_char = skip_whitespace(s);
	dst_len = b_skip(s) - skip_whitespace(s);
	dst = ft_strsub(s, start_char, dst_len);
	return (dst);
}
