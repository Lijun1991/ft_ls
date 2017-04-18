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

t_list *sorted_merge(t_list *a, t_list *b)//(void)(*f)(int flag)
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
		result->next = sorted_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next);
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

// t_list *sorted_merge_unvalid(t_list *a, t_list *b)

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
