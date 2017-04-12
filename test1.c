#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
// int main()
// {
//   int bufsize;

//   if ((bufsize = sysconf(_SC_GETPW_R_SIZE_MAX)) == -1)
//      abort();

//   char buf[bufsize];
//   struct passwd pwd, *result = NULL;
//   if (getpwuid_r(getuid(), &pwd, buf, bufsize, &result) != 0 || !result)
//      abort();

//   printf("%s\n", pwd.pw_dir);

//   return (0);
// }

int main()
{
  struct passwd *s;
  s = getpwuid(getuid());

  // struct group *t;
  // t = getgrgid(s->pw_gid);

  // printf("%s\n", t->gr_mem[0]); 
  printf("%s\n", s->pw_name);  // user name ls -l
  printf("%u\n", s->pw_uid);  // user id ls -ln
  printf("%u\n", s->pw_gid);  // group id ls -ln
  printf("%s\n", s->pw_dir);  //user dir
}


char  *doPath(char *name, char *path)
{
  char* cat_path;

  cat_path = ft_strjoin(path, "/");
  cat_path = ft_strjoin(cat_path, name);
  return (cat_path);
}