#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
int main(int argc, char *argv[]) {
  int fd;
  int n; 
  if(argc != 3) {
    printf("Valid syntax: <executable file> <filename> <string>\n");
    return 1;
  }

  fd = open(argv[1], O_WRONLY, 600);
  if(fd == -1) {
    perror("Error opening file");
    return 1;
  }

  n = write(fd, argv[2], strlen(argv[2]));
  if (n == -1){
    perror("Error writing to file");
    close(fd);
    return 1;
  }

  close(fd);
  return 0;
}
