#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int ptoc[2], ctop[2];
	pipe(ptoc);
	pipe(ctop);
  char buf[64];

  if (fork()) {
    // Parent
		close(ptoc[0]);
		close(ctop[1]);
		write(ptoc[1], "ping", strlen("ping"));
		wait(0);
		read(ctop[0], buf, 4);
		printf("%d: received %s\n", getpid(), buf);
  } else {
    // Child
		close(ptoc[1]);
		close(ctop[0]);
		read(ptoc[0], buf, 4);
		printf("%d: received %s\n", getpid(), buf);
		write(ctop[1], "pong", strlen("pong"));
  }

  exit(0);
}

