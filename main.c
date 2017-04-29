/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:08:44 by lwang             #+#    #+#             */
/*   Updated: 2017/04/18 00:03:43 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

void	ft_lstfree(t_list *lst)
{
	while (lst)
	{
		free(lst);
		lst = lst->next;
	}
}

int main(int ac, char **av)
{
	(void)ac;
	t_linfo *info;
	info = (t_linfo*)malloc(sizeof(t_linfo) * 1);
	ft_bzero(info, sizeof(t_linfo));

	info = parse_argument(av, info);
		// if (info->path)
		// 	;
	print_unvalid(info->invalid,info);
	print_file(info->file, info);
	print_directory(info);
	free(info);
	return (0);
}
