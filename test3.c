/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 14:24:51 by lwang             #+#    #+#             */
/*   Updated: 2017/04/17 14:24:54 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	DIR *dirp;
// 	struct dirent *dir;
// 	struct stat sb;

// 	while (*++av)
// 	{
// 		dirp = opendir(*av);
// 		if (dirp != NULL)
// 		{
// 			ft_printf("this is dir %s\n", *av);
// 			return (2);
// 		}
// 		if (stat(*av, &sb) == -1)
// 		{
// 			ft_printf("this is unvalid %s\n", *av);
// 			return (0);
// 		}
// 		else
// 			ft_printf("this is file %s\n", *av);
// 	}
// 	return (0);
// }


double cm_to_inches(double cm) {
	return cm / 2.54;
}

// "strchr" is part of the C string handling (i.e., no need for declaration)
// See https://en.wikipedia.org/wiki/C_string_handling#Functions

int main(void) {
	double (*func1)(double) = cm_to_inches;
	char * (*func2)(const char *, int) = strchr;
	printf("%f %s", func1(15.0), func2("Wikipedia", 'p'));
	/* prints "5.905512 pedia" */
	return 0;
}