#include "ftls.h"

char  *cut_next_line(char *s)
{
  char *tmp = s;
    while (*s)
    {
      if (*s == '\n')
        *s = '\0';
      s++;
    }
    return (tmp);
}

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
    ft_printf(" %5s", str[4]);
  else
    ft_printf(" %s", cut_second(str[3]));
  free(str);
  return ;
}



t_pre *pre_display_l(t_pre *pre)
{
    DIR *dirp;
    struct stat sb;
    struct dirent *dir;
    t_pre *tmp;

    tmp = pre;
   
    dirp = opendir(".");
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
      tmp->max_link = sb.st_nlink > tmp->max_link ? sb.st_nlink : tmp->max_link;
      tmp->max_bytes_nbr = sb.st_size > tmp->max_bytes_nbr ? sb.st_size : tmp->max_bytes_nbr;
      tmp->block_size += (long long) sb.st_blocks;
    }
  ft_printf("%lld, %ld, %lld\n", tmp->block_size, tmp->max_link,  tmp->max_bytes_nbr);
  return (tmp);
}

int main(int ac, char **av)
{
    DIR *dirp;
    struct stat sb;
    struct dirent *dir;

    struct passwd *s;
    s = getpwuid(getuid());

    struct group *t;
    t = getgrgid(s->pw_gid);

    t_pre *pre;

    pre = (t_pre*)malloc(sizeof(t_pre) * 1);
    ft_bzero(pre, sizeof(t_pre));
     
    pre = pre_display_l(pre);

    dirp = opendir(".");
    if (dirp == NULL)
    {
      perror("dir no exit");
      return (2);
    }
    while ((dir = readdir(dirp)))
    {
      if (stat(dir->d_name, &sb) == -1)
      {
          perror("stat2");
          return (0);
      }
    // if (dir->d_name[0] != '.' )//&& ((sb.st_mode & S_IFMT) == S_IFDIR)
    // {
    // ft_printf("I-node %ld", (long) sb.st_ino);
    char a;
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
    // ft_printf("total %lld\n", i);
    ft_printf("%c", a);
      ft_printf("%c", sb.st_mode & S_IFMT ? 'r' : '-');
      ft_printf("%c", sb.st_mode & S_IRUSR ? 'r' : '-');
      ft_printf("%c", sb.st_mode & S_IWUSR ? 'w' : '-');
      ft_printf("%c", sb.st_mode & S_IXUSR ? 'x' : '-');
      ft_printf("%c", sb.st_mode & S_IRGRP ? 'r' : '-');
      ft_printf("%c", sb.st_mode & S_IWGRP ? 'w' : '-');
      ft_printf("%c", sb.st_mode & S_IXGRP ? 'x' : '-');
      ft_printf("%c", sb.st_mode & S_IROTH ? 'r' : '-');
      ft_printf("%c", sb.st_mode & S_IWOTH ? 'w' : '-');
      ft_printf("%c", sb.st_mode & S_IXOTH ? 'x' : '-');

      // ft_printf(" %ld", (long)cur_time);
      // ft_printf("Mode:                     %lo (octal)", (unsigned long) sb.st_mode);
      ft_printf("  %2ld", (long) sb.st_nlink);
      ft_printf(" %s", s->pw_name);  // user name ls -l
      ft_printf("  %s", t->gr_name);
      // ft_printf("Ownership:                UID=%ld   GID=%ld", (long) sb.st_uid, (long) sb.st_gid);
      // ft_printf("Preferred I/O block size: %ld bytes", (long) sb.st_blksize);
      ft_printf("  %5lld", (long long) sb.st_size);
      
      // modi_time(cut_next_line(ctime(&sb.st_ctime)));
      modi_time(cut_next_line(ctime(&sb.st_ctime)), sb);
      // ft_printf(" %d", sb.st_mtime);
      // ft_printf("Last file access:         %s", ctime(&sb.st_atime));
      // ft_printf("Last file modification:   %s", ctime(&sb.st_mtime));
      ft_printf(" %s\n", dir->d_name);

    // }
      
  }

  return (0);
}

