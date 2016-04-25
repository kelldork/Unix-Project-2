#include<unistd.h>
#include<stdio.h>

int main(int argc, char **argv)
{
	int c;
	int Rflag = 0;

	// check args
	if (argc < 3)
	{
		fprintf(stderr, "error: too few arguments\n");
		return(1);
	}
	if (argc > 4)
	{
		fprintf(stderr, "error: too many arguments\n");
		return(1);
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
		fprintf(stdout, "Copy directory %s to %s\n", argv[2], argv[3]);
	}
	else
	{
		fprintf(stdout, "Copy flag %s to %s\n", argv[1], argv[2]);
	}

	return 0;
}
