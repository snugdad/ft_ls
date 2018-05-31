#include <stdio.h>
#Include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/xattr.h>

int main(int ac, char **av)
{
	ssize_t	buflen;
	ssize_t	keylen;
	ssize_t	vallen;
	char *buf;
	char *key;
	char *val;
	char *path;

	path = av[1];
	buflen = listxattr(path, NULL, 0, 0);
	if (buflen == -1)
	{
		perror("listxattr");
		exit(EXIT_FAILURE);
	}
	if (buflen == 0)
	{
		printf("%s has no attributes.\n", path);
		exit(EXIT_SUCCESS);
	}
	buf = (char *)malloc(buflen);
	if (buf == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	buflen = listxattr(path, buf, buflen, 0);
	if (buflen == -1)
	{
		perror("listxattr");
		exit(EXIT_FAILURE);
	}

	key = buf;
	while (buflen > 0)
	{
		printf("%s: ", key);
		vallen = getxattr(path, key, NULL, 0, 0, 0);
		if (vallen == -1)
			perror("getxattr");
		if (vallen > 0)
		{
			val = (char*)malloc(vallen + 1);
			if (val == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			vallen = getxattr(path, key, val, vallen, 0, 0);
			if (vallen == -1)
				perror("getxattr");
			else
			{
				val[vallen] = 0;
				printf("%s", val);
			}
		}
		else if (vallen == 0)
			printf("<no value>");
		printf("\n");
		free(val);
		keylen = strlen(key) + 1;
		buflen -= keylen;
		key += keylen;
	}
	free(buf);
	exit(EXIT_SUCCESS);
	return (0);
}
