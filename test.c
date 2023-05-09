#include <stdlib.h>

int main()
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		i++;
		addr = (char*)malloc(1024);
		addr[0] = 42;
		free(addr);
	}
	return (0);
}
