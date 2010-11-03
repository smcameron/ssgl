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
#include <errno.h>

#include "ssgl.h"

static void usage()
{
	fprintf(stderr, "usage: ssgl_gameserver_example servernick gametype gameinst location\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	int rc;
	uint32_t ipaddr;
        int lobbysock;
	struct ssgl_game_server gameserver;

	if (argc < 5)
		usage();

	memset(&gameserver, 0, sizeof(gameserver));

	rc = ssgl_get_primary_host_ip_addr(&ipaddr);

	gameserver.ipaddr = ipaddr; /* htonl needed here? */
	gameserver.port = htonl(1234); /* whatever your game server's initial port is... */
#define COPYINARG(field, arg) strncpy(gameserver.field, argv[arg], sizeof(gameserver.field) - 1)
	COPYINARG(server_nickname, 1);
	COPYINARG(game_type, 2);
	COPYINARG(game_instance, 3);
	COPYINARG(location, 4);


	while (1) {
		lobbysock = ssgl_gameserver_connect_to_lobby("localhost");
		if (lobbysock < 0) {
			fprintf(stderr, "ssgl_connect_to_lobby failed: %s\n", strerror(errno));
			exit(1);
		}

		rc = ssgl_register_gameserver(lobbysock, &gameserver);
		if (rc) {
			fprintf(stderr, "ssgl_register_gameserver failed: %s\n", strerror(errno));
			break;
		}

		shutdown(lobbysock, SHUT_RDWR);
		close(lobbysock);

		ssgl_sleep(SSGL_GAME_SERVER_TIMEOUT_SECS - 10);
	}
	return 0;
}
