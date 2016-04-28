#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

int cpdir(DIR *d, char *copyPath, char *pastePath)
{
		struct dirent *buf;
		char copyPathTemp[512];
		char pastePathTemp[512];
		int flag = 0;
		FILE *copy;
		FILE *paste;
		while ((buf = readdir(d)) != NULL)
		{
			strcpy(copyPathTemp, copyPath);
			strcpy(pastePathTemp, pastePath);

			//ignore . and ..
			if (!strcmp(buf->d_name, ".") || !strcmp(buf->d_name, ".."))
			{
				continue;
			}

			// if dir, recursive call
			if(buf->d_type == DT_DIR)
			{
				fprintf(stdout, "%s directory.\n\n", buf->d_name);
				strcat (copyPath, buf->d_name);
				strcat (pastePath, buf->d_name);
				mkdir  (pastePath, S_IRWXG | S_IRWXO | S_IRWXU);
				DIR *temp = opendir(copyPath);
				strcat (copyPath, "/");
				strcat (pastePath, "/");
				cpdir  (temp, copyPath, pastePath);
				strcpy (copyPath, copyPathTemp);
				strcpy (pastePath, pastePathTemp);
				flag = 1;
			}

			if(flag)
			{
				continue;
			}

			strcat(copyPathTemp, buf->d_name);
			strcat(pastePathTemp, buf->d_name);
			int fin = open(copyPathTemp, O_RDONLY);
			if(fin < 0)
			{
				fprintf(stderr, "error\n\n");
				return 1;
			}
			int fout = open(pastePathTemp, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if(fin < 0)
			{
				fprintf(stderr, "error\n\n");
				return 1;
			}
			char line[8192];

			while(1)
			{
				ssize_t result = read(fin, &line[0], sizeof(line));
				if(!result)
				{
					break;
				}
				if(result <= 0);
				{
					fprintf(stderr, "error");
				}
				if(write(fout, &line[0], result) != result)
				{
					fprintf(stderr, "error");
				}
			}

			fclose(copy);
			fclose(paste);
			
			// if not directory
			/*
			else
			{
				fprintf(stdout, "%s not directory.\n\n", buf->d_name);
				fprintf(stdout, "\nCopy flag %s to %s\n\n", argv[1], argv[2]);

				// open copy file, check for read permission
				if (copy = fopen(argv[1], "r"))
				{
					fprintf(stdout, "Successfully opened source file for reading.\n\n");

					// open paste file, check for write permission
					if(paste = fopen(argv[2], "w+"))
					{
						// copy file over
						fprintf(stdout, "Successfully opened destination file for writing.\n\n");
						char line[1100];
						while(fgets(line, sizeof(line), copy) != 0)
						{
							fputs(line, paste);
						}

						fclose(copy);
						fclose(paste);
						return 0;
					}

					// if cannot open paste file with write permissions
					else
					{
						fprintf(stderr, "Cannot open destination file for reading.\n\n");
						fclose(copy);
						return 0;
					}
				}

				// no read permission
				else
				{
					fprintf(stderr, "No read permission on source file.\n\n");
					return 1;
				}
			}
			*/	
		}
}

int main(int argc, char **argv)
{
	int c;
	int Rflag = 0;
	FILE *copy;
	FILE *paste;
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

	// recursive copy directory
	if (Rflag)
	{
		fprintf(stdout, "\nCopy directory %s to %s\n\n", argv[2], argv[3]);

		// check if source file exists
		/*
		if ( access(argv[2], F_OK) == -1 )
		{
			fprintf(stderr, "Source file does not exist\n\n");
			return 1;
		}
		*/

		char copyPath[512];
		char pastePath[512];
		getcwd (copyPath, 511);
		strcat (copyPath, "/");
		strcpy (pastePath, copyPath);
		strcat (copyPath, argv[2]);
		strcat (pastePath, argv[3]);
		strcat (copyPath, "/");
		strcat (pastePath, "/");
		DIR *d1;
		DIR *d2;
		// open source dir
		if(d1 = opendir(argv[2]))
		{
			// open destination dir
			if(d2 = opendir(argv[3]))
			{
				int cp = cpdir(d1, copyPath, pastePath);
				if(cp)
				{
					fprintf(stderr, "cpdir failed\n\n");
					return 1;
				}
				return 0;
			}

			// if paste dir doesn't exist
			if(ENOENT)
			{
				mkdir(argv[3], S_IRWXG | S_IRWXO | S_IRWXU);
				d2 = opendir(argv[3]);
				int cp2 = cpdir(d1, copyPath, pastePath);
				if(cp2)
				{
					fprintf(stderr, "cpdir failed\n\n");
					return 1;
				}
				return 0;
			}

			// if not proper permissions
			if(EACCES)
			{
				fprintf(stderr, "Do not have proper permissions on source directory.\n\n");
				return 1;
			}
		}
		
		// error if can't open source dir
		else
		{
			fprintf(stderr, "Could not open source directory.\n\n");
			return 1;
		}
	}

	// copy file
	else
	{
		fprintf(stdout, "\nCopy flag %s to %s\n\n", argv[1], argv[2]);

		// check if source file exists
		if ( access(argv[1], F_OK) == -1 )
		{
			fprintf(stderr, "Source file does not exist.\n\n");
			return 1;
		}

		// open copy file, check for read permission
		if (copy = fopen(argv[1], "r"))
		{
			fprintf(stdout, "Successfully opened source file for reading.\n\n");

			// open paste file, check for write permission
			if(paste = fopen(argv[2], "w+"))
			{
				// copy file over
				fprintf(stdout, "Successfully opened destination file for writing.\n\n");
				char line[1100];
				while(fgets(line, sizeof(line), copy) != 0)
				{
					fputs(line, paste);
				}

				fclose(copy);
				fclose(paste);
				return 0;
			}

			// if cannot open paste file with write permissions
			else
			{
				fprintf(stderr, "Cannot open destination file for reading.\n\n");
				fclose(copy);
				return 0;
			}
		}

		// no read permission
		else
		{
			fprintf(stderr, "No read permission on source file.\n\n");
			return 1;
		}
	}

	return 0;
}
