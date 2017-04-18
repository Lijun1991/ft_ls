#include "ftls.h"

// int main(int ac, char **av)
// {
// 	DIR *dirp;
// 	struct dirent *dir;
// 	struct stat sb;


// 	dirp = opendir("./pictures"); ///pictures
// 	if (dirp == NULL)
// 	{
// 		perror("opendir");
// 		return (0);
// 	}

// 	while ((dir = readdir(dirp)))
// 	{
		
// 		if (stat(ft_strjoin("pictures/", dir->d_name), &sb) == -1)
// 		{
// 			perror("stat1");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (dir->d_name[0] != '.' && ((sb.st_mode & S_IFMT) == S_IFDIR))
// 			printf("%s\n", dir->d_name);
// 	}

// 	exit(EXIT_SUCCESS);
//     if (!closedir(dirp))
//     	return (-1);

// 	return (0);
// }
   // char *s = "ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1";
   // printf("%d\n", (int)ft_strlen(s));
// #define FLAG_A 1
// #define FLAG_R 2
// #define FLAG_CAP_R 4
// #define FLAG_T 8
// #define FLAG_L 16
// #define FLAG_ONE 32
// #define FLAG_F 64
// #define FLAG_N 128
// #define FLAG_U 256;

//flag = flag | FLAG_A
void  get_flag(char *av, int *flag)
{
   while (*++av)
   {
      if (*av == 'a')
         *flag |= FLAG_A;
      else if (*av == 'r')
         *flag |= FLAG_R;
      else if (*av == 'R')
         *flag |= FLAG_CAP_R;
      else if (*av == 't')
         *flag |= FLAG_T;
      else if (*av == 'l')
         *flag |= FLAG_L;
      else if (*av == '1')
         *flag |= FLAG_ONE;
      else if (*av == 'f')
         *flag |= FLAG_F;
      else if (*av == 'n')
         *flag |= FLAG_N;
      else if (*av == 'u')
         *flag |= FLAG_U;
      // else
      // {
      //    ft_fprintf(2, "ft_ls: illegal option -- %c\n", *av);
      //    ft_fprintf(2, "usage: ft_ls [-arRtl1fnu] [file ...]\n");
      //    exit();
      // }
   }
}

int main(int ac, char **av)
{
   int flag = 0;
   char **tmp = av;

   if (ac >= 2)
   {  
      while (*++tmp)
      {
         if (av[0][0] == '-')
            get_flag(*tmp, &flag);
         else
            break ;
      }
      while (*++)
   }
   
   // if (flag & FLAG_A)
   //    printf("a\n");
   // if (flag & FLAG_R)
   //    printf("r\n");
   // if (flag & FLAG_CAP_R)
   //    printf("R\n");
   // if (flag & FLAG_T)
   //    printf("t\n");
   // if (flag & FLAG_ONE)
   //    printf("1\n");
   return (0);
}






