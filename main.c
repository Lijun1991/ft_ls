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

// t_list	*ft_lsthead(t_list	*head)
// {
// 	head = (t_list*)malloc(sizeof(t_list) * 1);
// 	head->content = NULL;
// 	head->content_size = 0;
// 	head->next = NULL;
// 	return (head);
// }

void	get_lst(struct dirent *dir, t_list **all_lst, t_list **dir_lst)
{
	// struct stat *meta;
	struct stat sb;

	ft_lstadd(all_lst, ft_lstnew(dir, dir->d_reclen));
	if (stat(dir->d_name, &sb) == -1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	if (dir->d_name[0] != '.' && ((sb.st_mode & S_IFMT) == S_IFDIR))
		ft_lstadd(dir_lst, ft_lstnew(dir, dir->d_reclen));
}

void	print(t_list *elem)
{
	struct stat sb;
	struct dirent *dir;
	dir = elem->content;

	if (stat(dir->d_name, &sb) == -1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	if (dir->d_name[0] != '.')
	{
		ft_printf("%s\n", dir->d_name);
		// ft_printf("%d\n", dir->d_type);
	}
}

void	print_cap_r(t_list	*dir_lst)
{
	ft_putchar('\n');
	ft_lstiter(dir_lst, print);
}

int main(int ac, char **av)
{
	DIR *dirp;
	struct dirent *dir;
	t_list *all_lst;
	t_list	*dir_lst;

	dirp = opendir(".");
	if (dirp == NULL)
	{
		ft_putstr("error");
		return (0);
	}
	all_lst = NULL;
	dir_lst = NULL;
	while ((dir = readdir(dirp)))
	{
		get_lst(dir, &all_lst, &dir_lst);
	}
	// sort();
	ft_lstiter(all_lst, print);
	// ft_putchar('\n');
	print_cap_r(dir_lst);
	exit(EXIT_SUCCESS);
    if (!closedir(dirp))
    	return (-1);
	return (0);
}



