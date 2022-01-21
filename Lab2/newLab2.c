#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <sys/dir.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int find(const char *path, char file[100], int *flag);
double myList(const char *path);

int main (int argc, char *argv[]){ 
    if(argv[1] == NULL){
		fprintf(stderr, "Error: Usage: %s [myList <directory path | find <directory path>]\n", argv[0]);
		return 1;
	}
    if(strcmp(argv[1], "myList") == 0){
        if(argv[2] == NULL){
            fprintf(stderr, "You must enter a vaild directory!\n");
            return 0;
        }
        double cputime = myList(argv[2]);
        printf("List function time: %f sec\n", cputime);
    }
    else if(strcmp(argv[1], "find") == 0){
        if(argv[2] == NULL){
            fprintf(stderr, "You must enter a vaild directory!\n");
            return 0;
        }
        else{
            int check = 0;
            char file[100];
            fprintf(stderr, "Enter the file you would like to find:");
            if(scanf("%s", file) == 1){
                clock_t start;
                clock_t end;
                double cputime;
                start = clock();
                find(argv[2], file, &check);
                end = clock();
                cputime = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Find function time: %f sec\n", cputime);
            }
            else{
                fprintf(stderr, "Failed to read in file\n");
            }
            if(check == 0){
                fprintf(stderr, "The file does not exist\n");
            }
        }
    }
    else{
        fprintf(stderr, "Error: Usage: %s [myList <directory path> | find <directory path>]\n", argv[0]);
    }
    return 0;
}

int find(const char *path, char file[100], int *flag){
    struct dirent *direct;
    DIR *dir;
    dir = opendir (path);
    if (dir == NULL) {
        fprintf (stderr, "Cannot open directory '%s'\n", path);
        return 0;
    }
    while((direct = readdir(dir)) != NULL){
        if(strcmp(direct->d_name, ".") == 0 || strcmp(direct->d_name, "..") == 0){
            continue;
        }
        if(direct->d_type == 4){ 
            char newPath[200];
            strcpy(newPath, path);
            strcat(newPath, "/");
            strcat(newPath, direct->d_name);
            const char *new = newPath;
            find(new, file, flag);
        }
        else if(strcmp(direct->d_name, file) == 0){
            fprintf(stderr, "Found the file!!\n");
            char winner[100];
            strcpy(winner, path);
            strcat(winner, "/");
            strcat(winner, direct->d_name);
            fprintf(stderr, "The path is: %s\n", winner);
            *flag = 1;
        }  
    }
    return 1;
}

double myList(const char *path){
    clock_t start;
    clock_t end;
    double cputime;
    start = clock();
    struct stat status;
    struct dirent *direct;
    DIR *dir;
    dir = opendir (path);
    struct passwd* pwd;
    struct group *grp;
    if (dir == NULL) {
        fprintf (stderr, "Cannot open directory '%s'\n", path);
        return 1;
    }
    if(stat(path, &status) == 0){
        while((direct = readdir(dir)) != NULL){
            stat(direct->d_name, &status);

            printf( (direct->d_type == 4) ? "d" : "-"); 
            printf( (status.st_mode & S_IRUSR) ? "r" : "-");
            printf( (status.st_mode & S_IWUSR) ? "w" : "-");
            printf( (status.st_mode & S_IXUSR) ? "x" : "-"); 
            printf( (status.st_mode & S_IRGRP) ? "r" : "-");
            printf( (status.st_mode & S_IWGRP) ? "w" : "-");
            printf( (status.st_mode & S_IXGRP) ? "x" : "-"); 
            printf( (status.st_mode & S_IROTH) ? "r" : "-");
            printf( (status.st_mode & S_IWOTH) ? "w" : "-");
            printf( (status.st_mode & S_IXOTH) ? "x" : "-"); 

            pwd = getpwuid(status.st_uid);
            grp = getgrgid(status.st_gid);

            printf(" %ld ", status.st_nlink); 
            printf("%s ", pwd->pw_name); 
            printf("%s  ", grp->gr_name); 
            printf(" %ld ", status.st_size);	
            printf("%s  ", ctime(&status.st_mtime)); 
            printf(" %s\n", direct->d_name);	
        }
    }
    else{
        fprintf(stderr, "Unable to load\n");
    }
    end = clock();
    cputime = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cputime;
}


