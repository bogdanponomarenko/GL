#include <stdio.h>
#include <dirent.h>
#include <grp.h>
#include <limits.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/sysmacros.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	DIR *mydir;
	
	struct dirent *d;
	struct stat mystat;
	struct passwd *pw;
	struct group *gr;
	
	char dirr[CHAR_MAX];
	char st_mode_ch[11]; // +1 for \0
	
	// total number of blocks allocated to files
	long int total_blocks = 0; 
	
	getcwd(dirr, CHAR_MAX); // get current working directory
	mydir = opendir(dirr);

	printf("ls fd - List Files and Directories\n");
	printf("ls a  - List Files and Directories, " 
	"including Hidden Files and Directories\n");
	printf("ls l  - List Files and Directories "
	"in Long Listing Format\n");
	printf("ls la - List Files and Directories in Long Listing Format, " 
	"including Hidden Files and Directories\n\n");
				
	while((d = readdir(mydir)) != NULL) {
		stat(d->d_name, &mystat);	
		pw = getpwuid(mystat.st_uid);		// user ID of owner
		gr = getgrgid(mystat.st_gid);		// group ID of owner
		total_blocks += mystat.st_blocks;	// number of used 1M blocks
		
		st_mode_ch[0] = (mystat.st_mode & S_IFDIR) ? 'd' : '-';	
		st_mode_ch[1] = (mystat.st_mode & S_IRUSR) ? 'r' : '-';	
		st_mode_ch[2] = (mystat.st_mode & S_IWUSR) ? 'w' : '-';
		st_mode_ch[3] = (mystat.st_mode & S_IXUSR) ? 'x' : '-';
		st_mode_ch[4] = (mystat.st_mode & S_IRGRP) ? 'r' : '-';	
		st_mode_ch[5] = (mystat.st_mode & S_IWGRP) ? 'w' : '-';
		st_mode_ch[6] = (mystat.st_mode & S_IXGRP) ? 'x' : '-';
		st_mode_ch[7] = (mystat.st_mode & S_IROTH) ? 'r' : '-';	
		st_mode_ch[8] = (mystat.st_mode & S_IWOTH) ? 'w' : '-';
		st_mode_ch[9] = (mystat.st_mode & S_IXOTH) ? 'x' : '-';
			
		if (strcmp(argv[1], "ls") == 0) {
			if ((d->d_type != DT_DIR) && (strcmp(argv[2], "fd") == 0)) {
				printf("%s  ", d->d_name);
			} else if (strcmp(argv[2], "a") == 0) {
				printf("%s  ", d->d_name);
			} else if ((strcmp(argv[2], "l") == 0) && \
			(d->d_type != DT_DIR)) {
				printf("%s\t", st_mode_ch);
				printf("%ld\t", (long) mystat.st_nlink);    
				printf("%s\t%s\t", pw->pw_name, gr->gr_name);
				printf("%lld\t", (long long) mystat.st_size);
				printf("%.24s ", ctime(&mystat.st_ctime));
				printf("%s\n", d->d_name);
			} else if (strcmp(argv[2], "la") == 0) {
				printf("%s\t", st_mode_ch);
				printf("%ld\t", (long) mystat.st_nlink);    
				printf("%s\t%s\t", pw->pw_name, gr->gr_name);
				printf("%lld\t", (long long) mystat.st_size);
				printf("%.24s ", ctime(&mystat.st_ctime));
				printf("%s\n", d->d_name);
			}
		}
	}
	closedir(mydir);
	printf("\ntotal %ld\n", total_blocks / 2);
}

