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
# define BUFFER_SIZE 4096
# define S2C "S2C.tube"
# define C2S "C2S.tube"

int main () {
    char buffer[BUFFER_SIZE];
    char choix[10];

    printf("1 : Menu Burger Happy\n");
    printf("2 : Menu Happy Sushi\n");
    printf("3 : Menu Pizza Happy\n");
    printf("Entrez le numero de votre choix : ");
    
    if (fgets(choix, sizeof(choix), stdin) == NULL) {
        printf("Erreur de lecture.\n");
        return 1;
    }
    choix[strcspn(choix, "\n")] = 0;

    int fd_out = open(C2S, O_WRONLY);
    //char *msg = choix;
    write(fd_out, choix, strlen(choix) + 1);
    close(fd_out);

    int fd_in = open(S2C, O_RDONLY);
    //read(fd_in, buffer, sizeof(buffer));
    ssize_t bytes_read = read(fd_in, buffer, BUFFER_SIZE - 1);
    printf("Menu reçu :\n%s\n", buffer);
    close(fd_in);


    return 0;
}
