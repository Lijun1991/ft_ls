# include <dirent.h>
# include <stdio.h>
# include "./libft/libft.h"
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/stat.h>

int main(int ac, char **av)
{
    DIR *dirp;
    struct stat sb;
    struct dirent *dir;
  // struct stat 

  // struct passwd *s;
  // s = getpwuid(getuid());

  dirp = opendir(".");
  while ((dir = readdir(dirp)))
  {
    if (stat(dir->d_name, &sb) == -1)
    {
      perror("stat2");
      return (0);
    }
    if (dir->d_name[0] != '.' && ((sb.st_mode & S_IFMT) == S_IFDIR))
    {
      ft_printf("%lo\n", sb.st_mode );
      // ft_printf("2%s\n", (sb.st_mode & S_ISGID));
      // ft_printf("3%s\n", (sb.st_mode & S_ISVTX));
      // ft_printf("4%s\n", (sb.st_mode & S_IRUSR));
      // ft_printf("5%s\n", (sb.st_mode & S_IWUSR));
      // ft_printf("6%s\n", (sb.st_mode & S_IXUSR));
      // ft_printf("hello\n");
    }
  }
  // struct group *t;
  // t = getgrgid(s->pw_gid);

  // printf("%s\n", t->gr_mem[0]); 

  // printf("%s\n", s->pw_name);  // user name ls -l
  // printf("%u\n", s->pw_uid);  // user id ls -ln
  // printf("%u\n", s->pw_gid);  // group id ls -ln
  // printf("%s\n", s->pw_dir);  //user dir
  return (0);
}

