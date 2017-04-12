#include "ftls.h"

int main(int ac, char **av)
{
	DIR *dirp;
	struct dirent *dir;
	struct stat sb;


	dirp = opendir("./pictures/"); ///pictures
	if (dirp == NULL)
	{
		perror("opendir");
		return (0);
	}

	while ((dir = readdir(dirp)))
	{
		
		if (stat(ft_strjoin("pictures/", dir->d_name), &sb) == -1)
		{
			perror("stat1");
			exit(EXIT_FAILURE);
		}
		if (dir->d_name[0] != '.')
			printf("%s\n", dir->d_name);
	}

	exit(EXIT_SUCCESS);
    if (!closedir(dirp))
    	return (-1);

	return (0);
}