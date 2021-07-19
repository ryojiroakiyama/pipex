void	put_2d_array(char **a)
{
	if (a == NULL)
	{
		printf("array is NULL");
		return ;
	}
	while (*a != NULL)
	{
		printf("%s\n", *a);
		a++;
	}
}

char	*verify_1d_array(char *array, char **to_free1, \
							char ***to_free2, int status)
{
	if (!array)
	{
		free_1d_array(to_free1);
		free_2d_array(to_free2);
		perrexit("malloc", status);
	}
	return (array);
}

char	**verify_2d_array(char **array, int status)
{
	if (!array)
		perrexit("malloc", status);
	return (array);
}

