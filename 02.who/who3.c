/*
   who2.c - read /etc/utmp and list info therein
          - suppresses empty records
          - formats time nicely
*/

#include <stdio.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include "utmplib.c"

/* #define     SHOWHOST */

void showtime(long);
void show_info(struct utmp *);

int main() {
   struct utmp *utbufp;        /* hold pointer to next rec */
   struct utmp *utmp_next();  /* return pointer to next */

   if (utmp_open(UTMP_FILE) == -1) {
      perror(UTMP_FILE);
      return 1;
   }

   while ((utbufp = utmp_next()) != (struct  utmp *)NULL)
   {
      show_info(utbufp);
   };
   utmp_close();
   return 0;
}

void show_info(struct utmp *utbufp) {
   if (utbufp->ut_type != USER_PROCESS)
      return;

   printf("%-8.8s", utbufp->ut_name);
   printf(" ");
   printf("%-8.8s", utbufp->ut_line);
   printf(" ");
   showtime(utbufp->ut_time);

   #ifdef SHOWHOST
   if (utbufp->ut_host[0] != '\0')
      printf(" (%s)", utbufp->ut_host);
   #endif
   printf("\n");
}

void showtime(long timeval) {
   char *cp;
   cp = ctime(&timeval);

   printf("%12.12s", cp+4);
}