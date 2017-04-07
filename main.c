/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:08:44 by lwang             #+#    #+#             */
/*   Updated: 2017/04/06 17:49:15 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>

int main(int ac, char **av)
{
	DIR *dirp = opendir(".");

	struct dirent *dir;
	while (dir = readdir(dirp))
	{
		printf("%s\n", dir->d_name);
	}
	// if (dirp == NULL)
	// 	return (0);
	// int len = strlen(name);
	// while ((dp = readdir(dirp)) != NULL) 
	// {
	//    if (dp->d_namlen == len && strcmp(dp->d_name, name) == 0) 
	//    {
 //           (void)closedir(dirp);
 //           return (FOUND);
 //       }
	// }
 //    (void)closedir(dirp);
 //    // return (NOT_FOUND);
	return (0);
}

