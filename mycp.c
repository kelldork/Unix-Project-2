#include<unistd.h>
#include<stdio.h>

int main(int argc, char **argv)
{
	// check args
	if (argc < 3)
	{
		fprintf(stderr, "error: too few arguments"\n);
		exit(1);
	}
	if (argc > 4)
	{
		fprintf(stderr, "error: too many arguments"\n);
		exit(1);
	}

	if(argc == 3)
	{
		
	}
	
	int c;

	while ((c = getopt (argc, argv, "R")) != -1)
	{
		switch(c)
		{
			case 'R':
				cpDir();
				break;
			default:
				cpFile();
				break;
		}
	}

	return 0;
}
