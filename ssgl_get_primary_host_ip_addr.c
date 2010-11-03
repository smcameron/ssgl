#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "ssgl.h"

/* Found this slickness on stackoverflow. Modified somewhat, 
 * uses host's own routing table to figure which interface
 * goes out to the net, and connects to google's DNS server
 * (DGRAM socket though, so nothing transmitted) and then
 * figures out which interface the DGRAM socket is hooked
 * up to.   Weakness: hardcoded 8.8.8.8 for google dns server
 * Never actually transmits any packets.
 */
int ssgl_get_primary_host_ip_addr(uint32_t *ipaddr) 
{

	const char* kGoogleDnsIp = "8.8.8.8"; /* yeah, this could break some day... */
	uint16_t kDnsPort = 53;
	struct sockaddr_in serv;
	struct sockaddr_in name;
	socklen_t namelen;
	int sock, err;
	/* char *p; */

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
		return sock;

	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr(kGoogleDnsIp);
	serv.sin_port = htons(kDnsPort);

	err = connect(sock, (struct sockaddr *) &serv, sizeof(serv));
	if (err < 0)
		goto close_and_err;		

	namelen = sizeof(name);
	err = getsockname(sock, (struct sockaddr *) &name, &namelen);
	if (err)
		goto close_and_err;		

	/* p = (char *) inet_ntop(AF_INET, &name.sin_addr, buffer, buflen);
	if (!p)
		goto close_and_err;
	*/

	memcpy(ipaddr, &name.sin_addr, sizeof(ipaddr));

	close(sock);
	return 0;

close_and_err:
	close(sock);
	return -1;
}

