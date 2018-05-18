/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:47:40 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/17 17:37:31 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		throw_err(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

/*int		builddirs(const char *path, char flags, t_entry *head)
{
	DIR *dir_stream;
	ch
	if (!(dir_stream = opendir(path)))
		return (-1);
	while (head->dp = readdir(dir_stream))
	{
		if (stat(head->e_label->d_name, head->e_data) < 0)
			return (-1);
		printf("Information for %s\n",);
		printf("---------------------------\n");
		printf("File Size: \t\t%d bytes\n",fileStat.st_size);
		printf("Number of Links: \t%d\n",fileStat.st_nlink);
		printf("File inode: \t\t%d\n",fileStat.st_ino);
 
		printf("File Permissions: \t");
		printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
		printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
		printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
		printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
		printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
		printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
		printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
		printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
		printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
		printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
		printf("\n\n");
		
	}*/
int		init_entry(t_entry *head)
{
		struct stat fileStat;
		if(stat(head->path, &fileStat) < 0)
			return(-1);
		printf("Information for %s\n", head->path);
		printf("---------------------------\n");
		printf("File Size: \t\t%lld bytes\n",fileStat.st_size);
		printf("Number of Links: \t%d\n",fileStat.st_nlink);
		printf("File inode: \t\t%llu\n",fileStat.st_ino);
 
		printf("File Permissions: \t");
		printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
		printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
		printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
		printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
		printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
		printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
		printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
		printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
		printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
		printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
		printf("\n\n");
	return (0);
}														/* 	dirent { ino_t d_ino //file serial number
															 char d_name[] //name of entry
															}*/
int main(int ac, char **av)
{
    char flags;
	DIR *target_dir;
	t_entry head;

	flags = 0;
    if((flags = check_args(av, &head.path, ac)) < 0)
        throw_err("INCORRECT ARGUMENT FORMAT");
	init_entry(&head);
}

