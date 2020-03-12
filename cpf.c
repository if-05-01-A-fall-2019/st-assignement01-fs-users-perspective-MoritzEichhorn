// Eichhorn Moritz

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    if(argc != 3) {
        printf("Please use exactly two arguments!\n");
        return 0;
    }
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
        printf("Couldn't open file: %s\n", argv[1]);
        return 0;
    }
    char buffer[256];
    int newLen = read(fd, buffer, 256);
    if(newLen < 0) {
        printf("Couldn't read from file");
        return 0;
    }

    int new_fd = creat(argv[2], S_IRUSR | S_IWUSR);
    write(new_fd, buffer, newLen);
    return 0;
}
