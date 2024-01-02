#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int p2c[2], c2p[2]; // Parent to child and child to parent pipes
    char buf[1];
    pipe(p2c);
    pipe(c2p);

    int pid = fork();
    if (pid < 0) {
        // Fork failed
        printf("fork failed\n");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        read(p2c[0], buf, 1); // Read from parent
        printf("%d: received ping\n", getpid());
        write(c2p[1], buf, 1); // Write to parent
        close(p2c[0]);
        close(c2p[1]);
    } else {
        // Parent process
        write(p2c[1], "p", 1); // Send to child
        read(c2p[0], buf, 1); // Read from child
        printf("%d: received pong\n", getpid());
        close(p2c[1]);
        close(c2p[0]);
        wait(0); // Wait for child to exit
    }
		exit(0);
}

