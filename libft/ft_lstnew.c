/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/16 21:12:15 by lwang             #+#    #+#             */
/*   Updated: 2016/10/20 15:24:07 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*dst;

	dst = (t_list*)malloc(sizeof(t_list));
	if (!dst)
		return (NULL);
	if (!content)
	{
		dst->content = NULL;
		dst->content_size = 0;
		dst->next = NULL;
		return (dst);
	}
	dst->content = (void *)malloc(content_size);
	if (dst->content == NULL)
		return (NULL);
	ft_memcpy((dst->content), content, content_size);
	dst->content_size = content_size;
	dst->next = NULL;
	return (dst);
}
