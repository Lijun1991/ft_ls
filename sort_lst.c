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

int	compare_fuc_rt_dir(t_list *a, t_list *b, t_linfo *info)
{
	struct dirent *dir;
	struct dirent *diry;
	struct stat sb;
	struct stat sb1;
	char *sub_dir;
	char *sub_dir1;

	dir = a->content;
	diry = b->content;

	sub_dir = add_path(dir->d_name, info->path);
	sub_dir1 = add_path(diry->d_name, info->path);

	if (lstat(sub_dir, &sb) == -1 || lstat(sub_dir1, &sb1) == -1)
	{
		perror("stat");
		return (-1);
	}
	if ((sb.st_mtime) != (sb1.st_mtime))
		return ((sb.st_mtime) < (sb1.st_mtime));
	else
	{
		if ((sb.st_mtimespec.tv_nsec) != (sb1.st_mtimespec.tv_nsec))
			return ((sb.st_mtimespec.tv_nsec) < (sb1.st_mtimespec.tv_nsec));
		else
			return (ft_strcmp(sub_dir, sub_dir1) > 0);
	}
}

int	compare_fuc_r_dir(t_list *a, t_list *b, t_linfo *info)
{
	struct dirent *dir;
	struct dirent *diry;

	(void)info;
	dir = a->content;
	diry = b->content;
	return (ft_strcmp(dir->d_name, diry->d_name) > 0);
}

int	compare_fuc_t_dir(t_list *a, t_list *b, t_linfo *info)
{
	struct dirent *dir;
	struct dirent *diry;
	struct stat sb;
	struct stat sb1;
	char *sub_dir;
	char *sub_dir1;

	dir = a->content;
	diry = b->content;

	sub_dir = add_path(dir->d_name, info->path);
	sub_dir1 = add_path(diry->d_name, info->path);
	if (lstat(sub_dir, &sb) == -1 || lstat(sub_dir1, &sb1) == -1)
	{
		perror("stat");
		return (-1);
	}
	if ((sb.st_mtime) != (sb1.st_mtime))
		return ((sb.st_mtime) > (sb1.st_mtime));
	else
	{
		if ((sb.st_mtimespec.tv_nsec) != (sb1.st_mtimespec.tv_nsec))
			return ((sb.st_mtimespec.tv_nsec) > (sb1.st_mtimespec.tv_nsec));
		else
			return (ft_strcmp(sub_dir, sub_dir1) < 0);
	}
}

int	compare_fuc_dir(t_list *a, t_list *b, t_linfo *info)
{
	struct dirent *dir;
	struct dirent *diry;

	(void)info;
	dir = a->content;
	diry = b->content;
	return (ft_strcmp(dir->d_name, diry->d_name) <= 0);
}


int	compare_fuc_rt_file(t_list *a, t_list *b, t_linfo *info)
{
	char *file_name;
	char *file_name1;
	struct stat sb;
	struct stat sb1;

	(void)info;
	file_name = a->content;
	file_name1 = b->content;

	if (lstat(file_name, &sb) == -1 || lstat(file_name1, &sb1) == -1)
	{
		perror("stat");
		return (-1);
	}
	if ((sb.st_mtime) != (sb1.st_mtime))
		return ((sb.st_mtime) < (sb1.st_mtime));
	else
	{
		if ((sb.st_mtimespec.tv_nsec) != (sb1.st_mtimespec.tv_nsec))
			return ((sb.st_mtimespec.tv_nsec) < (sb1.st_mtimespec.tv_nsec));
		else
			return (ft_strcmp(file_name, file_name1) > 0);
	}
}

int	compare_fuc_t_file(t_list *a, t_list *b, t_linfo *info)
{
	char *file_name;
	char *file_name1;
	struct stat sb;
	struct stat sb1;

	(void)info;
	file_name = a->content;
	file_name1 = b->content;

	if (lstat(file_name, &sb) == -1 || lstat(file_name1, &sb1) == -1)
	{
		perror("stat");
		return (-1);
	}
	if ((sb.st_mtime) != (sb1.st_mtime))
		return ((sb.st_mtime) > (sb1.st_mtime));
	else
	{
		if ((sb.st_mtimespec.tv_nsec) != (sb1.st_mtimespec.tv_nsec))
			return ((sb.st_mtimespec.tv_nsec) > (sb1.st_mtimespec.tv_nsec));
		else
			return (ft_strcmp(file_name, file_name1) < 0);
	}
}

int	compare_fuc_r_file(t_list *a, t_list *b, t_linfo *info)
{
	char *dir;
	char *diry;

	(void)info;
	dir = a->content;
	diry = b->content;
	return (ft_strcmp(dir, diry) > 0);
}

int	compare_fuc_file(t_list *a, t_list *b, t_linfo *info)
{
	char *dir;
	char *diry;

	(void)info;
	dir = a->content;
	diry = b->content;
	return (ft_strcmp(dir, diry) <= 0);
}

static t_list *sorted_merge(t_list *a, t_list *b, t_linfo *info, int (*compare_fuc)(t_list *, t_list *, t_linfo *))
{
	t_list *result = NULL;
	
	if (a == NULL)
		return(b);
	else if (b==NULL)
		return(a);

	if (compare_fuc(a, b, info))
	{
		result = a;
		result->next = sorted_merge(a->next, b, info, compare_fuc);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next, info, compare_fuc);
	}
	return(result);
}

static void front_back_split(t_list *source, t_list **frontref, t_list **backref)
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

void merge_sort(t_list **headref, int (*compare_fuc)(t_list *, t_list *, t_linfo *), t_linfo *info)
{
	t_list *head = *headref;
	t_list *a;
	t_list *b;
 
	a = NULL;
	b = NULL;
	if ((head == NULL) || (head->next == NULL))
		return;
	front_back_split(head, &a, &b);
	merge_sort(&a, compare_fuc, info);
	merge_sort(&b, compare_fuc, info);
	*headref = sorted_merge(a, b, info, compare_fuc);
}


