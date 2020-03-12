// Eichhorn Moritz

#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <time.h>
#include <string.h>

void printFileType(struct stat attributes) {
    switch (attributes.st_mode & S_IFMT) {
        case S_IFBLK:  
            printf("b");
            break;
        case S_IFCHR:  
            printf("c");        
            break;
        case S_IFDIR:  
            printf("d");               
            break;
        case S_IFLNK:  
            printf("l");                 
            break;
        case S_IFSOCK: 
            printf("s");                  
            break;
        case S_IFREG:  
            printf("-");            
            break;
        case S_IFIFO:  
            printf("f");               
            break;
        default:       
            printf("-");                
            break;
        }
}

void printAccessPrivilges(struct stat attributes) {
    printf( (attributes.st_mode & S_IRUSR) ? "r" : "-");
    printf( (attributes.st_mode & S_IWUSR) ? "w" : "-");
    printf( (attributes.st_mode & S_IXUSR) ? "x" : "-");
    printf( (attributes.st_mode & S_IRGRP) ? "r" : "-");
    printf( (attributes.st_mode & S_IWGRP) ? "w" : "-");
    printf( (attributes.st_mode & S_IXGRP) ? "x" : "-");
    printf( (attributes.st_mode & S_IROTH) ? "r" : "-");
    printf( (attributes.st_mode & S_IWOTH) ? "w" : "-");
    printf( (attributes.st_mode & S_IXOTH) ? "x " : "- ");
}

int main(int argc, char const *argv[]) {
    if(argc > 2) {
        printf("Please enter no more than one argument!\n");
        return 0;
    }
    char path[256];
    char pathCopy[256];
    strcpy(path, ".");
    if(argc == 2) {
        strcpy(path, argv[1]);
    }
    strcat(path, "/");
    DIR* dir = opendir(path);
    struct dirent* curr_element;
    struct stat attributes;
    
    while((curr_element = readdir(dir))) {
        if(curr_element->d_name[0] != '.') {
            strcpy(pathCopy, path);
            strcat(path, curr_element->d_name);
            lstat(path, &attributes);
            
            printFileType(attributes);
            printAccessPrivilges(attributes);

            printf("%5d ", attributes.st_uid);
            printf("%5d ", attributes.st_gid);
            printf("%9ld ", attributes.st_size);

            time_t timer;
            char buffer[26];
            struct tm* tm_info;
            timer = attributes.st_mtime;
            tm_info = localtime(&timer);
            strftime(buffer, 17, "%Y-%m-%d-%H-%M", tm_info);
            printf(" %s ", buffer);

            printf("%s\n", curr_element->d_name);
            strcpy(path, pathCopy);
        }
    }
    
    return 0;
}