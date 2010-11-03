#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

#define DEFINE_SSGL_SOCKET_IO_GLOBALS
#include "ssgl_socket_io.h"

/* TODO: use select() and by this method allow timeouts so dead clients/servers
 * don't hang the other end.
 */

/* Function to read from a socket, restarting if EINTR... */
int ssgl_readsocket(int fd, void *buffer, int buflen)
{

	char *c = buffer;
	int rc, len = buflen;

	do {
		rc = recv(fd, c, len, 0);
		if (rc == 0) /* other side closed conn */
			return -1;
		if (rc == len)
			return 0;
		if (rc < 0) {
			if (errno == -EINTR)
				continue;
			else
				return rc;
		}
		len -= rc;
		c += rc;
	} while (1);
}

/* Function to write to a socket, restarting if EINTR... */
int ssgl_writesocket(int fd, void *buffer, int buflen)
{
	char *c = buffer;
	int rc, len = buflen;

	do {
		rc = send(fd, c, len, 0);
		if (rc == len)
			return 0;
		if (rc < 0) {
			if (errno == -EINTR)
				continue;
			else
				return rc;
		}
		len -= rc;
		c += rc;
	} while (1);
}

 
