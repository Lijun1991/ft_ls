# ft_ls
Rewrite ls program

man dirent

man opendir, readdir, closedir

what is directory entry? https://en.wikipedia.org/wiki/Inode
Unix filesystem
inode = index node, it contains file and it's metadata(owner, permissions, time of last access, etc., but no name)

man 3 opendir

opendir, readdir, closedir -- directory operations

#include <dirent.h>

DIR *
     opendir(const char *filename);

struct dirent *
     readdir(DIR *dirp);



man 2 stat  lstat

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
