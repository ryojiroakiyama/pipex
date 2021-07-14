#include <stdio.h>
#include <unistd.h>

int	main(int argc, char *argv[], char *envp[])
{
	if (*envp == NULL)
	{
		printf("*envp is NULL");
		return (0);
	}
/*
	while (*envp != NULL)
	{
		printf("envp:%s\n", *envp);
		envp++;
	}
*/
	if (execve("/bin/cat", argv + 1, envp) == -1)//no understand roll of envp
//	if (execve("", argv + 1, envp) == -1)//no understand roll of envp
//	if (execve(NULL, argv + 1, envp) == -1)
//	if (execve("./a.out", argv + 1, envp) == -1)//no understand roll of envp
//	if (execve("./tmp", argv + 1, envp) == -1)//no understand roll of envp
		printf("execve error\n");
	return (0);
}
