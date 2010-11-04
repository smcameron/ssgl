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
	struct ssgl_game_server gameserver;
	pthread_t lobby_thread;

	if (argc < 6)
		usage();

	/* Set up the game server structure that we will send to the lobby server. */
	memset(&gameserver, 0, sizeof(gameserver));
	gameserver.ipaddr = 0; /* lobby server will figure this out. */
	gameserver.port = htonl(1234); /* whatever your game server's initial port is... */
#define COPYINARG(field, arg) strncpy(gameserver.field, argv[arg], sizeof(gameserver.field) - 1)
	COPYINARG(server_nickname, 2);
	COPYINARG(game_type, 3);
	COPYINARG(game_instance, 4);
	COPYINARG(location, 5);

	/* create a thread to contact and update the lobby server... */
	rc = ssgl_register_gameserver(argv[1], &gameserver, &lobby_thread);
	
	do {
		/* do whatever it is that your game server does here... */
		ssgl_sleep(5);
	} while (1);
	return 0;
}
