/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 13:47:17 by lwang             #+#    #+#             */
/*   Updated: 2017/04/22 22:17:54 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

char	*add_path(char *dname, char *path)
{
	char *dst;

	dst = path;
	if (ft_strcmp(path, ".") == 0)
		dst = dname;
	else
	{
		dst = ft_strjoin(dst, "/");
		dst = ft_strjoin(dst, dname);
	}
	return (dst);
}

// void	lst_print_all(t_list *lst)
// {
// 	t_list *cur;
// 	struct dirent *dir;

// 	cur = lst;
// 	while(cur != NULL)
// 	{
// 		dir = cur->content;
// 		if (dir->d_name[0] != '.')
// 		{
// 			ft_printf("123%s\n", dir->d_name);
// 		}
// 		cur = cur->next;
// 	}
// }


char	*get_path(char *path, char *name)
{
	char *dst;

	dst = ft_strjoin(path, "/");
	// ft_printf("\nmiddle is: %s\n", dst);
	dst = ft_strjoin(dst, name);

	return (dst);
}

char *get_link_path(char *lname, char *lpath)
{
	ssize_t len;
	int tmp;
	char *s;

	len = 0;
	tmp = 0;
	s = (char*)malloc(sizeof(char) * 226);

	tmp = readlink(get_path(lpath, lname), s, 225);
	if (tmp != -1)
		len = tmp;
	s[len] = '\0';

	// ft_printf("\nget link path is: %s\n", s);
	return (s);
}

void	print_helper(struct dirent *dir, struct stat sb, char *path, t_linfo *info)
{
	if (((sb.st_mode & S_IFMT) == S_IFLNK) && (info->flag & FLAG_L))
	{
		ft_printf("%s -> %s\n", dir->d_name, get_link_path(dir->d_name, path));
	}
	else 
	{
		ft_printf("%s\n", dir->d_name);
	}
}

void	lst_print_all_rec(t_list *lst, t_linfo *info)
{
	t_list *cur;
	struct stat sb;
	struct dirent *dir;
	char *sub_dir;

	cur = lst;

	if ((info->flag & FLAG_L && info->is_dir) || (info->flag & FLAG_L && info->is_file))
		ft_printf("total %lld\n", info->block_size);

	while(cur != NULL)
	{
		dir = cur->content;
		sub_dir = add_path(dir->d_name, info->path);
		if (lstat(sub_dir, &sb) == -1)
		{
			perror("stat2");
			return ;
		}

		if (info->flag & FLAG_A && info->flag & FLAG_L && ((sb.st_mode & S_IFMT) == S_IFDIR))
			print_l(sb, dir, info);//1
		else if (info->flag & FLAG_A && (info->flag & FLAG_L) && dir->d_name[0] != '.')
			print_l(sb, dir, info);//0
		else if (info->flag & FLAG_A && (info->flag & FLAG_L) && dir->d_name[0] == '.')
			print_l(sb, dir, info);//1

		else if (info->flag & FLAG_A && dir->d_name[0] != '.' && ((sb.st_mode & S_IFMT) == S_IFDIR))
			print_helper(dir, sb, info->path, info);
		else if (info->flag & FLAG_A && dir->d_name[0] != '.')
			print_helper(dir, sb, info->path, info);
		else if (info->flag & FLAG_A && dir->d_name[0] == '.'&& ((sb.st_mode & S_IFMT) == S_IFDIR))
			print_helper(dir, sb, info->path, info);
		else if (info->flag & FLAG_A && dir->d_name[0] == '.')
			print_helper(dir, sb, info->path, info);


		else if ((info->flag & FLAG_L) && dir->d_name[0] != '.' && ((sb.st_mode & S_IFMT) == S_IFDIR))
			print_l(sb, dir, info);//1
		else if ((info->flag & FLAG_L) && dir->d_name[0] != '.')
			print_l(sb, dir, info);//0

		else if (dir->d_name[0] != '.' && ((sb.st_mode & S_IFMT) == S_IFDIR))
			print_helper(dir, sb, info->path, info);
		else if (dir->d_name[0] != '.')
			print_helper(dir, sb, info->path, info);

		cur = cur->next;
	}
}

void	get_max_space(t_linfo *info, struct stat sb)
{
	struct passwd *s;
	struct group *t;

	s = getpwuid(sb.st_uid);
	t = getgrgid(sb.st_gid);
	info->max_link = sb.st_nlink > info->max_link ? sb.st_nlink : info->max_link;
	info->max_bytes_nbr = sb.st_size > info->max_bytes_nbr ? sb.st_size : info->max_bytes_nbr;
	info->block_size += (long long) sb.st_blocks;
	info->max_on = (int)ft_strlen(s->pw_name) > info->max_on ? (int)ft_strlen(s->pw_name) : info->max_on;
	info->max_gn = (int)ft_strlen(t->gr_name) > info->max_gn ? (int)ft_strlen(t->gr_name) : info->max_gn;
	// if (S_ISBLK(sb.st_mode) || S_ISCHR(sb.st_mode))
	// {
	// 	info->max_major = major(sb.st_rdev) > info->max_major ? major(sb.st_rdev) : info->max_major;
	// 	info->max_minor = minor(sb.st_rdev) > info->max_minor ? minor(sb.st_rdev) : info->max_minor;
	// }
}

void	get_lst(struct dirent *dir, t_list **all_lst, t_list **dir_lst, t_linfo *info)
{
	struct stat sb;
	char *sub_dir;

	sub_dir = add_path(dir->d_name, info->path);
	if (lstat(sub_dir, &sb) == -1)
	{
		// perror("stat1");
		exit(1) ;
	}
	if ((info->flag & FLAG_L) && (info->flag & FLAG_A))
		get_max_space(info, sb);
	else if (dir->d_name[0] != '.' && (info->flag & FLAG_L))
		get_max_space(info, sb);

	ft_lstadd(all_lst, ft_lstnew(dir, dir->d_reclen));
	if (dir->d_name[0] != '.' && ((sb.st_mode & S_IFMT) == S_IFDIR))
	{
		info->is_dir = 1;
		ft_lstadd(dir_lst, ft_lstnew(dir, dir->d_reclen));
	}
	if (dir->d_name[0] == '.' && info->flag & FLAG_A && ft_strlen(dir->d_name) > 1 && dir->d_name[1] != '.' && ((sb.st_mode & S_IFMT) == S_IFDIR))
	{
		info->is_dir = 1;
		ft_lstadd(dir_lst, ft_lstnew(dir, dir->d_reclen));
	}
	if (info->flag & FLAG_A)
		info->is_dir = 1;

	if (dir->d_name[0] != '.')
		info->is_dir = 1;
}


void	change_sort_way(t_list **lst, t_linfo *info)
{
	if ((info->flag & FLAG_R) && (info->flag & FLAG_T))
	{
		merge_sort(lst, compare_fuc_r_file, info);
		merge_sort(lst, compare_fuc_rt_dir, info);
	}
	else if (info->flag & FLAG_R)
		merge_sort(lst, compare_fuc_r_dir, info);
	else if (info->flag & FLAG_T)
	{
		merge_sort(lst, compare_fuc_file, info);
		merge_sort(lst, compare_fuc_t_dir, info);
	}
	else
		merge_sort(lst, compare_fuc_dir, info);
}

char *extract_path(char *path)
{
	int len;

	len = ft_strlen(path);
	while (len--)
		if (path[len] == '/')
			return (&path[len + 1]);
	return (path);
}

int	list_directory(char *path, int len, t_linfo *info, int sign)
{
	DIR *dirp;
	struct dirent *dir;
	char *newpath;
	t_list *all_lst;
	t_list	*dir_lst;

	all_lst = NULL;
	dir_lst = NULL;

	if (info->invalid || info->file)
		ft_printf("\n%s:\n", path);
	else if (info->count_arg > 1 && info->dir_sign == 1)
		ft_printf("%s:\n", path);
	else if (info->count_arg > 1 && info->dir_sign > 1)
		ft_printf("\n%s:\n", path);

	if (info->flag & FLAG_CAP_R && sign)
		ft_printf("\n%s:\n", path);

	dirp = opendir(path);
	if (dirp == NULL)
	{
		ft_printf("ls: %s: ", extract_path(path));
		perror("");
		return (2);
	}
	info->block_size = 0;
	info->is_dir = 0;
	info->max_bytes_nbr = 0;
	info->max_link = 0;
	info->max_on = 0;
	info->max_gn = 0;

	info->is_file = 0;

	info->max_major = 0;
	info->max_minor = 0;

	info->path = ft_strdup(path);
	while ((dir = readdir(dirp)))
		get_lst(dir, &all_lst, &dir_lst, info);

	change_sort_way(&all_lst, info);

	lst_print_all_rec(all_lst, info);

	change_sort_way(&dir_lst, info);

	while (dir_lst != NULL && (info->flag & FLAG_CAP_R))
	{
		sign++;
		dir = dir_lst->content;
		newpath = get_path(path, dir->d_name);
		list_directory(newpath, len, info, sign);
		dir_lst = dir_lst->next;
	}
    if (!closedir(dirp))
    	return (-1);
    return (0);
}



