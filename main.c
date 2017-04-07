/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:08:44 by lwang             #+#    #+#             */
/*   Updated: 2017/04/06 17:49:15 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

// typedef struct	s_lstinfo
// {
// 	struct dirent *dir;
// 	struct stat *meta;
// }				t_lstinfo;

// t_list	*ft_lstadd_bottom(t_list *random_node, t_list *new)
// {
// 	if (random_node->next == NULL)
// 	{
// 		random_node->next = new;
// 		printf("added at begainning\n");
// 	}
// 	else
// 	{
// 		t_list *current;

// 		current = random_node;
// 		while (current->next != NULL)
// 		{
// 			current = current->next;
// 		}
// 		current->next = new;
// 		printf("added lator\n");
// 	}
// 	return (random_node);
// }

t_list	*ft_lsthead(t_list	*head)
{
	head = (t_list*)malloc(sizeof(t_list) * 1);
	head->content = NULL;
	head->content_size = 0;
	head->next = NULL;
	return (head);
}

void	get_dir_lst(struct dirent *dir, t_list *dir_head)
{
	// struct stat *meta;

	ft_lstadd(&dir_head, ft_lstnew(dir, sizeof(dir)));
}

// void	print_one_level(t_list *dir_info)
// {
// 	t_list *select;

// 	select = ft_lstmap(dir_info, )
// }

// void	print_result(int ac, char **av, t_list *dir_info)
// {
// 	if (ac == 1)
// 	{
// 		print_one_level(dir_info);//only print current direcotry (no dot file)
// 	}
// }

// void	print_dir_name(t_lstinfo *info)
// {
	
// }

int main(int ac, char **av)
{
	DIR *dirp;
	// t_lstinfo *info;
	t_list *dir_head;
	struct dirent *dir;
	// info = (t_lstinfo*)malloc(sizeof(t_lstinfo) * 1);//malloc for info#1

	dirp = opendir(".");
	if (dirp == NULL)
	{
		ft_putstr("error");
		return (0);
	}
	dir_head = ft_lsthead(dir_head);
	while ((dir = readdir(dirp)))
	{
		get_dir_lst(dir, dir_head);
		// ft_printf("%s\n", dir->d_name);
	}
	// sort();
	ft_lstiter(dir_head, ft_putstr(dir->d_name));
	// print_result(ac, av, info);
    if (!closedir(dirp))
    	return (-1);
	return (0);
}



