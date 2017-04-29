/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 19:05:48 by lwang             #+#    #+#             */
/*   Updated: 2017/04/28 19:05:50 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

void	print_unvalid(t_list *invalid, t_linfo *info)
{
	t_list *cur;

	cur = invalid;
	merge_sort(&cur, compare_fuc_file, info);
	while (cur)
	{
		ft_fprintf(2, "ls: %s: No such file or directory\n", (char*)cur->content);
		cur = cur->next;
	}
	ft_lstfree(invalid);
}

void	get_file_max_space(t_linfo *info, t_list *file)
{
	t_list *cur;
	struct stat sb;

	cur = file;
	while (cur)
	{
		if (lstat((char*)cur->content, &sb) == -1)
		{
			perror("stat3");
			exit(1);
		}
		get_max_space(info, sb);
		cur = cur->next;
	}
}

void	print_file(t_list *file, t_linfo *info)
{
	t_list *cur;
	struct stat sb;
	struct dirent *dir;

	cur = file;
	dir = NULL;

	get_file_max_space(info, file);
	if (info->flag & FLAG_R && info->flag & FLAG_T)
	{
		merge_sort(&cur, compare_fuc_file, info);
		merge_sort(&cur, compare_fuc_rt_file, info);
	}
	else if (info->flag & FLAG_R)
		merge_sort(&cur, compare_fuc_r_file, info);
	else if (info->flag & FLAG_T)
		merge_sort(&cur, compare_fuc_t_file, info);
	else
		merge_sort(&cur, compare_fuc_file, info);
	while(cur != NULL)
	{
		if (info->flag & FLAG_L)
		{
			info->is_file = 1;
			// if (info->is_file)
			// 	ft_printf("hello");
			if (lstat((char*)cur->content, &sb) == -1)
			{
				perror("stat2");
				exit(1);
			}
			info->file_path = ft_strdup((char*)cur->content);
			// ft_printf("info->file_path is %s\n", info->file_path);
			print_l(sb, dir, info);//0
		}
		else
			ft_printf("%s\n", (char*)cur->content);
		cur = cur->next;
	}
	ft_lstfree(file);
}

void	print_directory(t_linfo *info)
{
	t_list *cur;

	cur = info->directory;

	merge_sort(&cur, compare_fuc_file, info);
	while (cur)
	{
		info->dir_sign++;
		list_directory(cur->content, (int)ft_strlen((char*)cur->content), info, 0);
		cur = cur->next;
	}
	ft_lstfree(info->directory);
}
