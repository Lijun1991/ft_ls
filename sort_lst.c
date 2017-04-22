/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 22:15:44 by lwang             #+#    #+#             */
/*   Updated: 2017/04/13 22:15:47 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

t_list *sorted_merge_t(t_list *a, t_list *b, t_linfo *info)
{
	t_list *result = NULL;
	struct dirent *dir;
	struct dirent *diry;
	struct stat sb;
	struct stat sb1;
	char *sub_dir;
	char *sub_dir1;

	if (a == NULL)
		return(b);
	else if (b==NULL)
		return(a);
	dir = a->content;
	diry = b->content;

	sub_dir = add_path(dir->d_name, info->path);
	sub_dir1 = add_path(diry->d_name, info->path);

	if (stat(sub_dir, &sb) == -1 || stat(sub_dir1, &sb1) == -1)
	{
		perror("stat");
		return (NULL);
	}
	if ((sb.st_mtime) > (sb1.st_mtime))
	{
		result = a;
		result->next = sorted_merge_t(a->next, b, info);
	}
	else
	{
		result = b;
		result->next = sorted_merge_t(a, b->next, info);
	}
	return(result);
}

t_list *sorted_merge_r_dir(t_list *a, t_list *b)
{
	t_list *result = NULL;
	struct dirent *dir;
	struct dirent *diry;

	if (a == NULL)
		return(b);
	else if (b==NULL)
		return(a);
	dir = a->content;
	diry = b->content;
	
	if (ft_strcmp(dir->d_name, diry->d_name) > 0)
	{
		result = a;
		result->next = sorted_merge_r_dir(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge_r_dir(a, b->next);
	}
	return(result);
}

t_list *sorted_merge_dir(t_list *a, t_list *b)
{
	t_list *result = NULL;
	struct dirent *dir;
	struct dirent *diry;

	if (a == NULL)
		return(b);
	else if (b==NULL)
		return(a);
	dir = a->content;
	diry = b->content;
	
	if (ft_strcmp(dir->d_name, diry->d_name) <= 0)
	{
		result = a;
		result->next = sorted_merge_dir(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge_dir(a, b->next);
	}
	return(result);
}

t_list *sorted_merge_file(t_list *a, t_list *b)
{
	t_list *result = NULL;
	char *dir;
	char *diry;

	if (a == NULL)
		return(b);
	else if (b==NULL)
		return(a);
	dir = a->content;
	diry = b->content;
	
	if (ft_strcmp(dir, diry) <= 0)
	{
		result = a;
		result->next = sorted_merge_file(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge_file(a, b->next);
	}
	return(result);
}

void front_back_split(t_list *source, t_list **frontref, t_list **backref)
{
	t_list *fast;
	t_list *slow;
	if (source==NULL || source->next==NULL)
	{
		*frontref = source;
		*backref = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*frontref = source;
		*backref = slow->next;
		slow->next = NULL;
	}
}

void merge_sort_time(t_list **headref, t_list *(*f)(t_list *, t_list *, t_linfo *), t_linfo *info)
{
	t_list *head = *headref;
	t_list *a;
	t_list *b;
 
	a = NULL;
	b = NULL;
	if ((head == NULL) || (head->next == NULL))
		return;
	front_back_split(head, &a, &b);
	merge_sort_time(&a, f, info);
	merge_sort_time(&b, f, info);
	*headref = f(a, b, info);
}

void merge_sort(t_list **headref, t_list *(*f)(t_list *, t_list *))
{
	t_list *head = *headref;
	t_list *a;
	t_list *b;
 
	a = NULL;
	b = NULL;
	if ((head == NULL) || (head->next == NULL))
		return;
	front_back_split(head, &a, &b);
	merge_sort(&a, f);
	merge_sort(&b, f);
	*headref = f(a, b);
}

