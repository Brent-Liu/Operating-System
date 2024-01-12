#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define READEND 0
#define WRITEEND 1

int
main(int argc, char *argv[])
{
	int ptoc[2], ctop[2];
	pipe(ptoc);
	pipe(ctop);
  char buf[64];

  if (fork()) {
    // Parent
		close(ptoc[READEND]);
		close(ctop[WRITEEND]);
		write(ptoc[WRITEEND], "ping", strlen("ping"));
		wait(0);
		read(ctop[READEND], buf, 4);
		printf("%d: received %s\n", getpid(), buf);
		close(ptoc[WRITEEND]);
		close(ctop[READEND]);
  } else {
    // Child
		close(ptoc[WRITEEND]);
		close(ctop[READEND]);
		read(ptoc[READEND], buf, 4);
		printf("%d: received %s\n", getpid(), buf);
		write(ctop[WRITEEND], "pong", strlen("pong"));
		close(ptoc[READEND]);
		close(ctop[WRITEEND]);
  }
  exit(0);
}

