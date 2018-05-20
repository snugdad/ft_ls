/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:47:40 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/19 17:35:19 by egoodale         ###   ########.fr       */
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
int		init_structs(t_entry *head)
{
	if(!(head->e_data = (struct stat *)malloc(sizeof(struct stat))))
		throw_err("Malloc Error");
	return (0);
}
int		init_entry(t_entry *head)
{
		DIR *dir;
		struct dirent	*dp;
		char buf[512];

		dir = opendir(head->path);
		init_structs(head);
		while((dp = readdir(dir)))
		{
			sprintf(buf, "%s/%s", head->path, dp->d_name);
			stat(buf, head->e_data);
			printf("%lld", head->e_data->st_size);
			printf(" %s\n", dp->d_name);
		}
		closedir(dir);
		return (0);
}														

  
 int ls_noarg(t_entry *head) 
 { 
    DIR *dir;
    struct dirent *dp;
    unsigned int count;
  
	count = 0;
    if(!head->path) 
        throw_err("\n ERROR : Could not get the working directory\n");
    dir = opendir(head->path); 
	while((dp = readdir(dir)))
        if(dp->d_name[0] != '.') 
            printf("%s\t",dp->d_name);
	printf("\n");
	closedir(dir);
    return 0; 
 }

char	get_sortkey(char flags)
{
	char sortkey;

	if(flags & r)
		sortkey |= reverse;
    if (flags & t)
		sortkey |= by_time;
	else
		sortkey |= by_name;
}

int main(int ac, char **av)
{
    char flags;
	char sort_key;
	t_entry head;

	flags = 0;
    if((flags = check_args(av, &head.path, ac)) < 0)
        throw_err("INCORRECT ARGUMENT FORMAT");
    if((sort_key = get_sortkey(flags)) < 0)
		throw_err("INVALID SORT PATTERN");
	if(!flags)
		ls_noarg(&head);
    if (flags & l)
	/*SWITCH(flags,
		CASE(flags & l,
			printf("l is on\n")),
		CASE(flags & a, 
			printf("a is on\n")),
		CASE(flags & R,
			printf("R is on\n")),
		CASE(flags & r,
			printf("r is on\n")),
		CASE(flags & at,
			printf("at is on\n")),
		DEFAULT(
			printf("no flags are on\n")));*/
}

