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

to creat a new file with set time:(year_month_date_hour_minutes_second)
touch -t 201601111111.11 bla


chmod
To make this modification you would invoke the command: chmod a-rw file1
To add the permissions above you would invoke the command: chmod a+rw file1


test.....
