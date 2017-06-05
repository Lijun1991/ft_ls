#include "ftls.h"

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






