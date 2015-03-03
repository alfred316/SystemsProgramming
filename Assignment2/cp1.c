/** cp1.c
 *     version 1 of cp - uses read and write with tunable buffer size
 *
 *     usage: cp1 src dest
 */
#include        <stdio.h>
#include        <unistd.h>
#include        <fcntl.h>
#include        <stdlib.h>
#include        <string.h>

#define BUFFERSIZE      4096
#define COPYMODE        0644

void oops(char *, char *);

main(int ac, char *av[])
{
  int     in_fd, out_fd, n_chars;
  char*    buff;
  int buffer;

  int flag = O_CREAT | O_WRONLY;
  if(strcmp(av[3], "sync")){
    flag = flag | O_SYNC;
  }

  if(av[4]){
    buffer = atoi(av[4]);
    buff = malloc(buffer);
  }

  /* check args */
  if ( ac < 5 ){
    fprintf( stderr, "usage: %s source destination\n", *av);
    exit(1);
  }
  /* open files*/

  if ( (in_fd=open(av[1], O_RDONLY)) == -1 )
    oops("Cannot open ", av[1]);

  if ( (out_fd=open(av[2], flag)) == -1 )
    oops( "Cannot open", av[2]);
  
  /* copy files*/

  while ( (n_chars = read(in_fd , buff, buffer)) > 0 )
    if ( write( out_fd, buff, n_chars ) != n_chars )
      oops("Write error to ", av[2]);
  if ( n_chars == -1 )
    oops("Read error from ", av[1]);

  /* close files*/

  if ( close(in_fd) == -1 || close(out_fd) == -1 )
    oops("Error closing files","");
}

void oops(char *s1, char *s2)
{
  fprintf(stderr,"Error: %s ", s1);
  perror(s2);
  exit(1);
}
