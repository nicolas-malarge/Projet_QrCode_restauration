//client.c
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
// for open , O_RDONLY , O_WRONLY
// for printf
// for mkfifo
// for read , write
# define BUFFER_SIZE 512
# define S2C "S2C.tube"
# define C2S "C2S.tube"

int main () {
    char buffer[512];

    int fd_out = open(C2S, O_WRONLY);
    char *msg = "2";
    write(fd_out, msg, strlen(msg) + 1);
    close(fd_out);

    int fd_in = open(S2C, O_RDONLY);
    read(fd_in, buffer, sizeof(buffer));
    printf("Menu reçu :\n%s\n", buffer);
    close(fd_in);
    return 0;
}