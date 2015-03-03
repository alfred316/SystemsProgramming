//Alfred Shaker
//Systems programming
//Assignment 1
//Who1

#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>


#define SHOWHOST/* include remote machine on output */

void showTime(long);

int main()
{
  struct utmp current_record;/* read info into here       */
  int utmpfd;/* read from this descriptor */
  int reclen = sizeof(current_record);

  if ( (utmpfd = open(UTMP_FILE, O_RDONLY)) == -1 ){
    perror( UTMP_FILE );/* UTMP_FILE is in utmp.h    */
    exit(1);
  }

  while ( read(utmpfd, &current_record, reclen) == reclen )
    show_info(&current_record);
  close(utmpfd);
  return 0;/* went ok */
}
/*
 *  show info()
 *displays contents of the utmp struct in human readable form
 **note* these sizes should not be hardwired
 */
show_info( struct utmp *utbufp )
{
  printf("%s", utbufp->ut_id); //terminal suffix
  printf(" | ");
  printf("PID : %-5.5ld", utbufp->ut_pid); //process id
  printf(" | ");
  printf("Type : %-1.1hx", utbufp->ut_type); //type of record
  printf(" | ");
  printf("logname: %-8.8s", utbufp->ut_user);/* the logname*/
  printf(" | ");/* a space*/
  printf("%-8.8s", utbufp->ut_line);/* the tty*/
  printf(" | time: ");/* a space*/
  showTime(utbufp->ut_time);/* login time*/
  printf(" | ");/* a space*/
  //printf("%s", utbufp->ut_id);
  //printf(" | ");
#ifdef SHOWHOST
  printf("host: (%s)", utbufp->ut_host);/* the host*/
#endif
  printf("\n");/* newline*/
}

void showTime (long timeval){

  char *cp;
  cp = ctime(&timeval);
  printf("%12.12s", cp+4);

}

