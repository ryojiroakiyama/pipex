#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		printf("mode:%d, return:%d\n", F_OK, access(argv[1], F_OK));
		printf("mode:%d, return:%d\n", R_OK, access(argv[1], R_OK));
		printf("mode:%d, return:%d\n", W_OK, access(argv[1], W_OK));
		printf("mode:%d, return:%d\n", X_OK, access(argv[1], X_OK));
	}
//	if (argc > 2)
//		unlink(argv[2]);

	return (0);
}