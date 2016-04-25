#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv)
{
	int c;
	int Rflag = 0;
	//FILE *fp;

	// check args
	if (argc < 3)
	{
		fprintf(stderr, "error: too few arguments\n");
		return 1;
	}
	if (argc > 4)
	{
		fprintf(stderr, "error: too many arguments\n");
		return 1;
	}

	if(argc == 3)
	{
		
	}
	
	while ((c = getopt (argc, argv, "R")) != -1)
	{
		switch(c)
		{
			case 'R':
				Rflag = 1;
				break;
			default:
				break;
		}
	}

	if (Rflag)
	{
		fprintf(stdout, "\nCopy directory %s to %s\n\n", argv[2], argv[3]);
	}
	else
	{
		fprintf(stdout, "\nCopy flag %s to %s\n\n", argv[1], argv[2]);
		if ( access(argv[1], F_OK) == -1 )
		{
			fprintf(stderr, "Source file does not exist\n\n");
			return 1;
		}
	}

	return 0;
}
