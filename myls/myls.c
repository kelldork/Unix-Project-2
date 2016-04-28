#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <pwd.h>
#include <grp.h>
#include <libgen.h>


bool l_flag = false, a_flag = false, isDirectory = false, isFile = false;

static void printLong(struct dirent* dp)
{
	struct stat buf;
	int fileDes = open(dp->d_name, O_RDONLY);
	fstat(fileDes, &buf);
	char buffer[80];

	printf( (S_ISDIR(buf.st_mode)) ? "d" : "-");
    printf( (buf.st_mode & S_IRUSR) ? "r" : "-");
    printf( (buf.st_mode & S_IWUSR) ? "w" : "-");
    printf( (buf.st_mode & S_IXUSR) ? "x" : "-");
    printf( (buf.st_mode & S_IRGRP) ? "r" : "-");
    printf( (buf.st_mode & S_IWGRP) ? "w" : "-");
    printf( (buf.st_mode & S_IXGRP) ? "x" : "-");
    printf( (buf.st_mode & S_IROTH) ? "r" : "-");
    printf( (buf.st_mode & S_IWOTH) ? "w" : "-");
    printf( (buf.st_mode & S_IXOTH) ? "x" : "-");

	printf("%3d",(int) buf.st_nlink);
	struct passwd pwd = *getpwuid(buf.st_uid);
	printf(" %10s", pwd.pw_name);
	struct group grp = *getgrgid(buf.st_gid);
	printf("%10s", grp.gr_name);
	printf("  %6lld", (long long)(int)buf.st_size);
	struct tm *time = localtime(&buf.st_atime); 
	strftime(buffer, 80, "%b %d %I:%M", time);
	printf("  %s", buffer);
	printf(" %s", dp->d_name);
	printf("\n");
	
}

static void output(struct dirent* dp)
{
	if(a_flag)
	{
		if(l_flag)
		{
			printLong(dp);
		}
		else
		{
			printf("%s\n",dp->d_name);
		}	
	}
	else if(dp->d_name[0] != '.')
	{
		if(l_flag)
		{
			printLong(dp);
		}
		else
		{
			printf("%s\n",dp->d_name);
		}				
    }
} 

int main(int argc, char** argv)
{
	int opt = 0, count = 1, arg_num = 0;

	//Check options
	while ((opt = getopt(argc, argv, "la")) != -1)
    {
        switch(opt)
        {
            case 'l': 	l_flag = true; 
					  	break;
            case 'a': 	a_flag= true; 
						break;
            default:
						break;
        }
    }

	//Check if one of the arguments is a folder or file	
	while(count < argc)
	{
		//Check if one of the arguments is a folder or file	
		DIR* dir = opendir(argv[count]);	
		if(argv[count][0] != '-' && dir)
		{
			arg_num = count;
			isDirectory = true;
			closedir(dir);
		}
		else if( access( argv[count], F_OK ) != -1 )
		{	
			arg_num = count;
			isFile = true;
		}
		count++;
	}

	int fileDes = open(argv[arg_num], O_RDWR );
	struct stat st;
    int result = stat(argv[arg_num], &st);
	if(fileDes == -1)
	{
		printf("No permission\n");
		exit(-1);
	}
	else if(!result)
	{
		printf("./myls: f: No such file or directory\n");
		exit(-1);
	}
	
	if(isDirectory == 0 && isFile == 0)
	{
		//Check if one of the arguments is a folder or file	
		DIR *dir = opendir(".");
		struct dirent *dp;

		while ((dp = readdir(dir)) != NULL) 
		{
			output(dp);
		}
	}
	else if(isDirectory)
	{
		DIR *dir = opendir(argv[arg_num]);
		struct dirent *dp;

		while ((dp = readdir(dir)) != NULL) 
		{
			output(dp);
		}
	}
	else if(isFile)
	{	
		

		bool found = false;
		struct dirent *dp;
		DIR *dir = opendir(".");
		while((dp = readdir(dir)) != NULL)
		{
			if(strcmp(dp->d_name, argv[arg_num]) == 0)
			{
				output(dp);
				found = true;
			}
		}
		
		if(!found)
		{
			char* ts1 = strdup(argv[arg_num]);
			char* dir2 = dirname(ts1);
			char* filename = basename(ts1);
			dir = opendir(dir2);
			while((dp = readdir(dir)) != NULL)
			{
				if(strcmp(dp->d_name, filename) == 0)
				{
					output(dp);
				}
			}
			
		}
	}
}
