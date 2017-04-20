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
	strlcat(dst, s, 6);
	return (dst);
}

void modi_time(char *s, struct stat sb)
{
	char **str;
	time_t cur_time;

	cur_time = time(NULL);
	str = ft_strsplit(s, ' ');
	ft_printf(" %s", str[1]);
	ft_printf(" %s", str[2]);
	if ((long)cur_time - (long)sb.st_mtime > 15768000 || (long)cur_time - (long)sb.st_mtime < -15768000)
		ft_printf(" %5d", ft_atoi(str[4]));
	else
		ft_printf(" %s", cut_second(str[3]));
	free(str);
	return ;
}

t_linfo *pre_display_l(t_linfo *info, char *path)
{
	DIR *dirp;
	struct stat sb;
	struct dirent *dir;

	dirp = opendir(path);
	if (dirp == NULL)
	{
		perror("dir no exit");
		return (NULL);
	}
	while ((dir = readdir(dirp)))
	{
		if (stat(dir->d_name, &sb) == -1)
		{
			perror("stat2");
			return (NULL);
		}
		info->max_link = sb.st_nlink > info->max_link ? sb.st_nlink : info->max_link;
		info->max_bytes_nbr = sb.st_size > info->max_bytes_nbr ? sb.st_size : info->max_bytes_nbr;
		info->block_size += (long long) sb.st_blocks;
	}
	ft_printf("total %lld\n", info->block_size);
	// if (!closedir(dirp))
 //    	return (NULL);
	return (info);
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

void	print_l(struct stat sb, struct dirent *dir, int sign, t_linfo *info)
{
	struct passwd *s;
	struct group *t;

	s = getpwuid(getuid());
	t = getgrgid(s->pw_gid);

	ft_printf("%c", get_type(sb));
	ft_printf("%c", sb.st_mode & S_IRUSR ? 'r' : '-');
	ft_printf("%c", sb.st_mode & S_IWUSR ? 'w' : '-');
	ft_printf("%c", sb.st_mode & S_IXUSR ? 'x' : '-');
	ft_printf("%c", sb.st_mode & S_IRGRP ? 'r' : '-');
	ft_printf("%c", sb.st_mode & S_IWGRP ? 'w' : '-');
	ft_printf("%c", sb.st_mode & S_IXGRP ? 'x' : '-');
	ft_printf("%c", sb.st_mode & S_IROTH ? 'r' : '-');
	ft_printf("%c", sb.st_mode & S_IWOTH ? 'w' : '-');
	ft_printf("%c", sb.st_mode & S_IXOTH ? 'x' : '-');

	ft_printf("  %*ld", max_len(info->max_link), (long)sb.st_nlink);
	ft_printf(" %s", s->pw_name);
	ft_printf("  %s", t->gr_name);
	ft_printf("  %*lld", max_len(info->max_bytes_nbr), (long long) sb.st_size);
	modi_time(ctime(&sb.st_ctime), sb);
	if (sign == 1)
		ft_printf(GREE" %s\n"CLN, dir->d_name);
	else
		ft_printf(" %s\n", dir->d_name);
}





