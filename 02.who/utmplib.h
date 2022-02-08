#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utmp.h>

int utmp_open(char *filename);
struct utmp *utmp_next();
int utmp_reload();
int utmp_close();