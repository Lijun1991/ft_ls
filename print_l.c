/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:48:50 by lwang             #+#    #+#             */
/*   Updated: 2017/04/19 17:48:52 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

char  *cut_second(char *s)
{
	char *dst;

	dst = ft_strnew(6);
	ft_strlcat(dst, s, 6);
	return (dst);
}

void modi_time(char *s, struct stat sb)
{
	char **str;
	time_t cur_time;

	cur_time = time(NULL);
	str = ft_strsplit(s, ' ');
	ft_printf(" %s", str[1]);
	ft_printf(" %2s", str[2]);
	if ((long)cur_time - (long)sb.st_mtime > 15768000 || (long)cur_time - (long)sb.st_mtime < -15768000)
		ft_printf(" %5d ", ft_atoi(str[4]));
	else
		ft_printf(" %s ", cut_second(str[3]));
	free(str);
	return ;
}

char	get_type(struct stat sb)
{
	char a;

	a = '\0';
	if ((sb.st_mode & S_IFMT) == S_IFIFO)
		a = 'p';
	else if ((sb.st_mode & S_IFMT) == S_IFCHR)
		a = 'c';
	else if ((sb.st_mode & S_IFMT) == S_IFDIR)
		a = 'd';
	else if ((sb.st_mode & S_IFMT) == S_IFBLK)
		a = 's';
	else if ((sb.st_mode & S_IFMT) == S_IFREG)
		a = '-';
	else if ((sb.st_mode & S_IFMT) == S_IFLNK)
		a = 'l';
	else if ((sb.st_mode & S_IFMT) == S_IFSOCK)
		a = 's';
	return (a);
}

int	max_len(long long nbr)
{
	int i;

	i = 0;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

void	print_l(struct stat sb, struct dirent *dir, t_linfo *info)//int sign, 
{
	struct passwd *s;
	struct group *t;

	s = getpwuid(sb.st_uid);
	t = getgrgid(sb.st_gid);

	ft_printf("%c", get_type(sb));
	ft_printf("%c", sb.st_mode & S_IRUSR ? 'r' : '-');
	ft_printf("%c", sb.st_mode & S_IWUSR ? 'w' : '-');
	ft_printf("%c", sb.st_mode & S_IXUSR ? (sb.st_mode & S_ISUID ? 's' : 'x') : (sb.st_mode & S_ISUID ? 'S' : '-'));

	ft_printf("%c", sb.st_mode & S_IRGRP ? 'r' : '-');
	ft_printf("%c", sb.st_mode & S_IWGRP ? 'w' : '-');
	ft_printf("%c", sb.st_mode & S_IXGRP ? (sb.st_mode & S_ISGID ? 's' : 'x') : (sb.st_mode & S_ISGID ? 'S' : '-'));

	ft_printf("%c", sb.st_mode & S_IROTH ? 'r' : '-');
	ft_printf("%c", sb.st_mode & S_IWOTH ? 'w' : '-');
	ft_printf("%c", sb.st_mode & S_IXOTH ? (sb.st_mode & S_ISVTX ? 't' : 'x') : (sb.st_mode & S_ISVTX ? 'T' : '-'));

	ft_printf("  %*ld", max_len(info->max_link), (long)sb.st_nlink);
	ft_printf(" %-*s  %-*s", info->max_on, s->pw_name, info->max_gn, t->gr_name);
	// ft_printf("hahah%d %d hahha", info->max_on, info->max_gn);
	ft_printf("  %*lld", max_len(info->max_bytes_nbr), (long long) sb.st_size);
	modi_time(ctime(&sb.st_mtime), sb);
	if (!dir && info->is_file)
	{
		if (((sb.st_mode & S_IFMT) == S_IFLNK) && (info->flag & FLAG_L))
		{
			ft_printf("%s -> %s\n", info->file_path, get_link_path(info->file_path, info->path));
		}
		else
			ft_printf("%s\n", info->file_path);
	}	
	else
	{
		print_helper(dir, sb, info->path, info);
		// if (sign == 1)
		// 	ft_printf(" %s\n", dir->d_name);
		// else
			// ft_printf(" %s\n", dir->d_name);
	}
}





