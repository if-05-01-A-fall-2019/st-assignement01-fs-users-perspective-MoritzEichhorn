// Eichhorn Moritz

#include <sys/stat.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    if(argc != 2) {
        printf("Please enter exactly one argument!\n");
        return 0;
    }
    printf("------------------- %s -------------------\n", argv[1]);
    struct stat attributes;

    int ret = lstat(argv[1], &attributes);
    if(ret != 0) { 
        printf("Couldn't read attributes of file: %s\n", argv[1]);
        return 0;
    }
    printf("File type\t\t: ");
    switch (attributes.st_mode & S_IFMT) {
    case S_IFBLK:  
        printf("Block special file\n");
        break;
    case S_IFCHR:  
        printf("Device special file\n");        
        break;
    case S_IFDIR:  
        printf("Directory\n");               
        break;
    case S_IFLNK:  
        printf("Symbolic link\n");                 
        break;
    case S_IFSOCK: 
        printf("Socket\n");                  
        break;
    case S_IFREG:  
        printf("Regular file\n");            
        break;
    case S_IFIFO:  
        printf("FIFO\n");               
        break;
    default:       
        printf("Unknown\n");                
        break;
    }

    printf("Access privileges\t: ");
    printf( (attributes.st_mode & S_IRUSR) ? "r" : "-");
    printf( (attributes.st_mode & S_IWUSR) ? "w" : "-");
    printf( (attributes.st_mode & S_IXUSR) ? "x" : "-");
    printf( (attributes.st_mode & S_IRGRP) ? "r" : "-");
    printf( (attributes.st_mode & S_IWGRP) ? "w" : "-");
    printf( (attributes.st_mode & S_IXGRP) ? "x" : "-");
    printf( (attributes.st_mode & S_IROTH) ? "r" : "-");
    printf( (attributes.st_mode & S_IWOTH) ? "w" : "-");
    printf( (attributes.st_mode & S_IXOTH) ? "x\n" : "-\n");
    
    time_t a_time = attributes.st_atime;
    time_t m_time = attributes.st_mtime;
    time_t c_time = attributes.st_ctime;

    printf("Inode-Number\t\t: %ld\n", attributes.st_ino);
    printf("Device numbers:\t\t: dev = %ld; rdev = %ld\n", attributes.st_dev, attributes.st_rdev);
    printf("Links count\t\t: %ld\n", attributes.st_nlink);
    printf("UID\t\t\t: %d\n", attributes.st_uid);
    printf("GID\t\t\t: %d\n", attributes.st_gid);
    printf("File size\t\t: %ld\n", attributes.st_size);
    printf("Last access\t\t: %s", ctime(&a_time));
    printf("Last modification\t: %s", ctime(&m_time));
    printf("Last inode change\t: %s", ctime(&c_time));
    return 0;
}