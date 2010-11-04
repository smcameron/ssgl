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
	fprintf(stderr, "usage: ssgl_gameserver_example lobbyserver servernick gametype gameinst location\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	int rc;
        int lobbysock;
	struct ssgl_game_server gameserver;

	if (argc < 6)
		usage();

	memset(&gameserver, 0, sizeof(gameserver));

	gameserver.ipaddr = 0; /* lobby server will figure this out. */
	gameserver.port = htonl(1234); /* whatever your game server's initial port is... */
#define COPYINARG(field, arg) strncpy(gameserver.field, argv[arg], sizeof(gameserver.field) - 1)
	COPYINARG(server_nickname, 2);
	COPYINARG(game_type, 3);
	COPYINARG(game_instance, 4);
	COPYINARG(location, 5);

	while (1) {
		lobbysock = ssgl_gameserver_connect_to_lobby(argv[1]);
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
