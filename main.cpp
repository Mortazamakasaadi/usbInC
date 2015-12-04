
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <iostream>

using namespace std;

/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.
 */

int open_port(void)
{
  int fd; /* File descriptor for the port */


  fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
  {
   /*
    * Could not open the port.
    */

    perror("open_port: Unable to open /dev/ttyUSB0 - ");
  }
  else
    fcntl(fd, F_SETFL, 0);

  return (fd);
}


int                  /* O - 0 =  ok, -1 =  bad */
sendAndGet(int fd)   /* I - Serial port file */
{
  char buffer[255];  /* Input buffer */
  char *bufptr;      /* Current char in buffer */
  int  nbytes;       /* Number of bytes read */
  int  tries;        /* Number of tries so far */

  for (tries = 0; tries < 3; tries ++)
  {
   /* send info */
    if (write(fd, "MAK\r", 4) < 3)
      continue;

   /* read characters into our string buffer until we get a CR or NL or any other ending send character */
    bufptr = buffer;
    while ((nbytes = read(fd, bufptr, buffer + sizeof(buffer) - bufptr - 1)) > 0)
    {
      bufptr += nbytes;
      if (bufptr[-1] == '\n' || bufptr[-1] == '\r')
        break;
    }

   /* nul terminate the string and see if we got proper response */
    *bufptr = '\0';

    if (strncmp(buffer,"MAK\r", 3) == 0){
        int i=0;
    while(buffer!='\0'){cout<<buffer; i++;}
      return (0);
  }

  return (-1);
}
}

int main(void){
int fd=open_port();
sendAndGet(fd);
close(fd);
return 0;
}



