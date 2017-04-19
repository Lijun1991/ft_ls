# include <dirent.h>
# include <stdio.h>
# include "./libft/libft.h"
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <time.h>

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

int main(int ac, char **av)
{
    DIR *dirp;
    struct stat sb;
    struct dirent *dir;

    struct passwd *s;
    s = getpwuid(getuid());

    struct group *t;
    t = getgrgid(s->pw_gid);

  dirp = opendir(".");
  long long i;
  i = 0;
  while ((dir = readdir(dirp)))
  {
    if (stat(dir->d_name, &sb) == -1)
    {
      perror("stat2");
      return (0);
    }
    // if (dir->d_name[0] != '.' )//&& ((sb.st_mode & S_IFMT) == S_IFDIR)
    // {
      ft_printf("%c", sb.st_mode & S_IRUSR ? 'r' : '-');
      ft_printf("%c", sb.st_mode & S_IWUSR ? 'w' : '-');
      ft_printf("%c", sb.st_mode & S_IXUSR ? 'x' : '-');
      ft_printf("%c", sb.st_mode & S_IRGRP ? 'r' : '-');
      ft_printf("%c", sb.st_mode & S_IWGRP ? 'w' : '-');
      ft_printf("%c", sb.st_mode & S_IXGRP ? 'x' : '-');
      ft_printf("%c", sb.st_mode & S_IROTH ? 'r' : '-');
      ft_printf("%c", sb.st_mode & S_IWOTH ? 'w' : '-');
      ft_printf("%c", sb.st_mode & S_IXOTH ? 'x' : '-');
      // ft_printf("I-node number:            %ld", (long) sb.st_ino);
      // ft_printf("Mode:                     %lo (octal)", (unsigned long) sb.st_mode);
      ft_printf("  %ld", (long) sb.st_nlink);
      ft_printf(" %s", s->pw_name);  // user name ls -l
      ft_printf(" %s", t->gr_name);
      // ft_printf("Ownership:                UID=%ld   GID=%ld", (long) sb.st_uid, (long) sb.st_gid);
      // ft_printf("Preferred I/O block size: %ld bytes", (long) sb.st_blksize);
      ft_printf("  %lld", (long long) sb.st_size);
      
      //modi_fime(ft_strsplit(cut_next_line(ctime(&sb.st_ctime)), ' '));
      ft_printf(" %s", cut_next_line(ctime(&sb.st_mtime)));
      ft_printf(" %d", sb.st_mtime);
      // ft_printf("Last file access:         %s", ctime(&sb.st_atime));
      // ft_printf("Last file modification:   %s", ctime(&sb.st_mtime));
      ft_printf(" %s\n", dir->d_name);

      // ft_printf("%u", s->pw_uid);  // user id ls -ln
      // ft_printf("%u", s->pw_gid);  // group id ls -ln
      // ft_printf("%s\n", s->pw_dir);  //user dir
    // }
      i += (long long) sb.st_blocks;
  }
  ft_printf(" Blocks allocated:%lld\n", i);

  return (0);
}

